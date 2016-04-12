#include "mainview.h"
#include "ui_mainview.h"
#include "nodeCommunication.h"
#include <QDebug>
#include <QTimer>
#include <QLineEdit>

nodeCommunication *t;

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    ui->lblName->setVisible(false);
    ui->editName->setVisible(false);
    ui->lblCurrTemp->setVisible(false);
    ui->currTemp->setVisible(false);
    ui->lblPrefTemp->setVisible(false);
    ui->editTemp->setVisible(false);
    ui->btnUpdate->setVisible(false);
    ui->lblThermostat->setVisible(false);
    ui->cbThermostat->setVisible(false);
    ui->lblHeat->setVisible(false);
    ui->cbHeat->setVisible(false);
    ui->editTemp->setRange(50,99);
    ui->lblSummary->setVisible(false);
    addNames();

    //prepare summary table
    ui->summaryTbl->setColumnCount(3);
    ui->summaryTbl->verticalHeader()->setVisible(false);
    ui->summaryTbl->setSelectionMode(QTableWidget::NoSelection);
    ui->summaryTbl->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->summaryTbl->setHorizontalHeaderLabels(QStringList() << "Room Name" << "Current Temp." << "Preferred Temp.");
    ui->summaryTbl->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->summaryTbl->setVisible(false);

    heatOn = false;

    t = new nodeCommunication();
    t->start();
    roomsDisplayed = 0;
    connect(ui->roomList, SIGNAL(itemSelectionChanged()), this, SLOT(roomChange()));
    connect(ui->btnUpdate, SIGNAL(clicked()), this, SLOT(updateStruct()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(updateRooms()));
    timer->start(10000);

    QTimer *dbTimer = new QTimer();
    connect(dbTimer, SIGNAL(timeout()), SLOT(updateDB()));
    dbTimer->start(1800000);//1,800,000ms in a half hour - database should update each timeout

    connect(ui->editTemp, SIGNAL(valueChanged(int)), SLOT(spinValueChange()), Qt::QueuedConnection);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::generateRooms()
{
    //for debugging---:
    qDebug() << "generating initial rooms...";

    //get current size of vector
    int vectorSize = t->roomVector.size();

    for (int i=0;i<vectorSize;i++){
        ui->roomList->addItem(t->roomVector[i].name);
        if (i!=0)
            ui->editName->addItem(t->roomVector[i].name);
        roomsDisplayed++;
    }
}

void MainView::roomChange()
{
    int currRow = ui->roomList->currentRow();
    if (currRow == 0)
    {
        ui->lblName->setVisible(false);
        ui->editName->setVisible(false);
        ui->lblCurrTemp->setVisible(false);
        ui->currTemp->setVisible(false);
        ui->lblThermostat->setVisible(false);
        ui->cbThermostat->setVisible(false);
        ui->lblPrefTemp->setVisible(true);
        ui->editTemp->setVisible(true);
        ui->btnUpdate->setVisible(true);
        ui->btnUpdate->setText("Update System");
        ui->lblHeat->setVisible(true);
        ui->cbHeat->setVisible(true);
        ui->lblSummary->setVisible(true);

        if (heatOn)
            ui->cbHeat->setChecked(1);
        else
            ui->cbHeat->setChecked(0);

        //display the summary table and set the number of rows it needs to display data for all current rooms
        ui->summaryTbl->setVisible(true);
        ui->summaryTbl->setRowCount(t->roomVector.size() - 1);

        //fill the table
        int j=0;
        for (int i=1; i < t->roomVector.size(); i++)
        {
            ui->summaryTbl->setItem(j, 0, new QTableWidgetItem(t->roomVector[i].name));
            ui->summaryTbl->setItem(j, 1, new QTableWidgetItem(QString::number(t->roomVector[i].currTemp)));
            ui->summaryTbl->setItem(j, 2, new QTableWidgetItem(QString::number(t->roomVector[i].prefTemp)));
            j++;
        }

        //show the system's preferred temp
        ui->editTemp->setValue(t->roomVector[currRow].prefTemp);
    }
    else
    {
        ui->lblName->setVisible(true);
        ui->editName->setVisible(true);
        ui->lblCurrTemp->setVisible(true);
        ui->currTemp->setVisible(true);
        ui->lblPrefTemp->setVisible(true);
        ui->editTemp->setVisible(true);
        ui->btnUpdate->setVisible(true);
        ui->lblThermostat->setVisible(true);
        ui->cbThermostat->setVisible(true);
        ui->btnUpdate->setText("Update Room");
        ui->summaryTbl->setVisible(false);
        ui->lblHeat->setVisible(false);
        ui->cbHeat->setVisible(false);
        ui->lblSummary->setVisible(false);

        //set the fields to display the proper data for the newly selected room

        ui->editName->setCurrentIndex(ui->editName->findText(t->roomVector[currRow].name));
        ui->currTemp->setText(QString::number(t->roomVector[currRow].currTemp));
        ui->editTemp->setValue(t->roomVector[currRow].prefTemp);
        ui->cbThermostat->setChecked(t->roomVector[currRow].withThermostat);
    }
}

void MainView::updateStruct()
{
    int currRow = ui->roomList->currentRow();
    if (currRow == 0)
    {
        //ui->summaryList2->clear();
        //this is a "system" update - need to update preference on all nodes
        for (int i=0; i < t->roomVector.size(); i++)
        {
            t->roomVector[i].prefTemp = ui->editTemp->value();
        }
        for (int j=0; j < t->roomVector.size() - 1; j++)
        {
            ui->summaryTbl->setItem(j, 2, new QTableWidgetItem(QString::number(ui->editTemp->value())));
        }
        if (ui->cbHeat->isChecked())
            heatOn = true;
        else
            heatOn = false;
    }
    else
    {
        //update the struct's information for this nodeid
        t->roomVector[currRow].name = ui->editName->currentText();
        t->roomVector[currRow].prefTemp = ui->editTemp->value();
        t->roomVector[currRow].withThermostat = ui->cbThermostat->isChecked();

        //update name of room on list item
        ui->roomList->currentItem()->setText(ui->editName->currentText());
    }
}

//method to automatically add newly "found" rooms
//(found via the pings from the nodes)
void MainView::updateRooms()
{
    qDebug() << "checking for newly found nodes...";
    if (t->roomCounter > roomsDisplayed)
    {
        //if a new node has been detected from the pings since we last checked the values,
        //need to add that node as a new room in the list
        int vectorSize = t->roomVector.size(); //get current vector size
        for (int i=roomsDisplayed;i<vectorSize;i++){
            ui->roomList->addItem(t->roomVector[i].name);
            ui->editName->addItem(t->roomVector[i].name);
            roomsDisplayed++;
            qDebug() << "new node added to list in GUI";
        }
    }
    return;
}

void MainView::updateDB()
{
    t->updateDatabaseForAll();
    return;
}

void MainView::clearNames()
{
    bool hasData = true;
    while(hasData)
    {
        if (ui->editName->count() != 0)
        {
            ui->editName->removeItem(ui->editName->currentIndex());
        }
        else
            hasData = false;
    }
    return;
}

void MainView::addNames()
{
    ui->editName->addItem("Bedroom");
    ui->editName->addItem("Bedroom 2");
    ui->editName->addItem("Bathroom");
    ui->editName->addItem("Bathroom 2");
    ui->editName->addItem("Kitchen");
    ui->editName->addItem("Living Room");
    return;
}

void MainView::spinValueChange()
{
    ui->editTemp->findChild<QLineEdit*>()->deselect();
    ui->editTemp->findChild<QLineEdit*>()->setReadOnly(true);
    return;
}
