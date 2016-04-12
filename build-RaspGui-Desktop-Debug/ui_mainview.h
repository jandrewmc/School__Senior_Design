/********************************************************************************
** Form generated from reading UI file 'mainview.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVIEW_H
#define UI_MAINVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainView
{
public:
    QWidget *centralWidget;
    QFrame *mainFrame;
    QWidget *editRoom;
    QLabel *lblName;
    QLabel *lblCurrTemp;
    QLabel *currTemp;
    QLabel *lblPrefTemp;
    QSpinBox *editTemp;
    QPushButton *btnUpdate;
    QCheckBox *cbThermostat;
    QLabel *lblThermostat;
    QComboBox *editName;
    QTableWidget *summaryTbl;
    QLabel *lblHeat;
    QCheckBox *cbHeat;
    QLabel *lblSummary;
    QListWidget *roomList;
    QPushButton *btnExit;

    void setupUi(QMainWindow *MainView)
    {
        if (MainView->objectName().isEmpty())
            MainView->setObjectName(QString::fromUtf8("MainView"));
        MainView->resize(800, 530);
        MainView->setMinimumSize(QSize(800, 530));
        MainView->setMaximumSize(QSize(800, 530));
        MainView->setStyleSheet(QString::fromUtf8("#MainView {\n"
"	background: #27313E;\n"
"}\n"
"\n"
"#centralWidget {\n"
"	background: #27313E;\n"
"}\n"
"\n"
"#mainFrame {\n"
"	border: 7px solid #DD4A38;\n"
"	border-radius: 20px;\n"
"	background: #27313E;\n"
"}\n"
"\n"
"#roomList {\n"
"	border: 7px solid #DD4A38;\n"
"	border-radius: 20px;\n"
"	background: #27313E;\n"
"}\n"
"\n"
"#lblName, #lblCurrTemp, #lblPrefTemp, #currTemp,\n"
" #lblThermostat, #lblHeat, #lblSummary {\n"
"	color: white;\n"
"	font: 18pt \"DejaVu Sans\";\n"
"}\n"
"\n"
"#editName {\n"
"	color: 27313E;\n"
"	font: 16pt \"DejaVu Sans\";\n"
"	border: 1px solid white;\n"
"	border-radius: 2px;\n"
"}\n"
"\n"
"#editName::drop-down {\n"
"	width: 35px;\n"
"}\n"
"\n"
"#editTemp {\n"
"	color: 27313E;\n"
"	font: 18pt \"DejaVu Sans\";\n"
"	border: 1px solid white;\n"
"	border-radius: 2px;\n"
"}\n"
"\n"
"#editTemp::up-button, #editTemp::down-button {\n"
"	min-width: 25px;\n"
"	min-height: 25px;\n"
"}\n"
"\n"
"#cbThermostat, #cbHeat {\n"
"	margin-right: 0px !important;\n"
"}\n"
"\n"
"#cbThermostat::indicat"
                        "or, #cbHeat::indicator {\n"
"	width: 25px;\n"
"	height: 25px;\n"
"}\n"
"\n"
"#cbThermostat::hover, #cbHeat::hover {\n"
"	background: #27313E;\n"
"}\n"
"\n"
"#btnUpdate, #btnAdd {\n"
"	font: 18pt \"DejaVu Sans\";\n"
"	padding-left: 10px;\n"
"	padding-top: 45px;\n"
"	padding-bottom: 45px;\n"
"	border: 6px solid #27313E;\n"
"	border-radius: 15px;\n"
"	background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4A5D75, stop: 1 #354354);\n"
"	width: 100px;\n"
"	color: white;\n"
"}\n"
"\n"
"#btnUpdate:!enabled, #btnAdd:!enabled {\n"
"	color: #354354;\n"
"}\n"
"\n"
"#btnUpdate:pressed, #btnAdd:pressed {\n"
"	background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4A5D75, stop: 1 green);\n"
"}\n"
"\n"
"QScrollBar::vertical {\n"
"	border: 3px solid #354354;\n"
"	border-radius: 5px;\n"
"    background:white;\n"
"    width: 30px;\n"
"    margin: 5px 0px 0px 0px;\n"
"	max-height: 375px;\n"
"}\n"
"QScrollBar::handle:vertical {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"    stop: 0  #DD4A3"
                        "8, stop: 0.5 #DD4A38,  stop:1 #DD4A38);\n"
"    min-height: 0px;\n"
"	max-height: 375px;\n"
"}\n"
"QScrollBar::add-line:vertical {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"    stop: 0  #DD4A38, stop: 0.5 #DD4A38,  stop:1 #DD4A38);\n"
"    height: 0px;\n"
"    subcontrol-position: bottom;\n"
"    subcontrol-origin: margin;\n"
"}\n"
"QScrollBar::sub-line:vertical {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,\n"
"    stop: 0  #DD4A38, stop: 0.5 #DD4A38,  stop:1 #DD4A38);\n"
"    height: 0px;\n"
"    subcontrol-position: top;\n"
"    subcontrol-origin: margin;\n"
"}"));
        centralWidget = new QWidget(MainView);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMaximumSize(QSize(800, 530));
        mainFrame = new QFrame(centralWidget);
        mainFrame->setObjectName(QString::fromUtf8("mainFrame"));
        mainFrame->setGeometry(QRect(30, 30, 490, 420));
        mainFrame->setMaximumSize(QSize(490, 420));
        mainFrame->setFrameShape(QFrame::StyledPanel);
        mainFrame->setFrameShadow(QFrame::Raised);
        editRoom = new QWidget(mainFrame);
        editRoom->setObjectName(QString::fromUtf8("editRoom"));
        editRoom->setGeometry(QRect(10, 10, 470, 400));
        lblName = new QLabel(editRoom);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setGeometry(QRect(30, 50, 81, 35));
        lblName->setStyleSheet(QString::fromUtf8(""));
        lblCurrTemp = new QLabel(editRoom);
        lblCurrTemp->setObjectName(QString::fromUtf8("lblCurrTemp"));
        lblCurrTemp->setGeometry(QRect(30, 190, 281, 41));
        lblCurrTemp->setStyleSheet(QString::fromUtf8(""));
        currTemp = new QLabel(editRoom);
        currTemp->setObjectName(QString::fromUtf8("currTemp"));
        currTemp->setGeometry(QRect(330, 190, 61, 41));
        currTemp->setStyleSheet(QString::fromUtf8(""));
        lblPrefTemp = new QLabel(editRoom);
        lblPrefTemp->setObjectName(QString::fromUtf8("lblPrefTemp"));
        lblPrefTemp->setGeometry(QRect(30, 250, 291, 51));
        editTemp = new QSpinBox(editRoom);
        editTemp->setObjectName(QString::fromUtf8("editTemp"));
        editTemp->setGeometry(QRect(330, 250, 71, 51));
        btnUpdate = new QPushButton(editRoom);
        btnUpdate->setObjectName(QString::fromUtf8("btnUpdate"));
        btnUpdate->setEnabled(true);
        btnUpdate->setGeometry(QRect(115, 320, 241, 60));
        cbThermostat = new QCheckBox(editRoom);
        cbThermostat->setObjectName(QString::fromUtf8("cbThermostat"));
        cbThermostat->setGeometry(QRect(330, 120, 35, 41));
        lblThermostat = new QLabel(editRoom);
        lblThermostat->setObjectName(QString::fromUtf8("lblThermostat"));
        lblThermostat->setGeometry(QRect(30, 120, 291, 41));
        editName = new QComboBox(editRoom);
        editName->setObjectName(QString::fromUtf8("editName"));
        editName->setGeometry(QRect(130, 50, 281, 35));
        summaryTbl = new QTableWidget(editRoom);
        summaryTbl->setObjectName(QString::fromUtf8("summaryTbl"));
        summaryTbl->setGeometry(QRect(30, 60, 401, 141));
        lblHeat = new QLabel(editRoom);
        lblHeat->setObjectName(QString::fromUtf8("lblHeat"));
        lblHeat->setGeometry(QRect(30, 210, 291, 41));
        cbHeat = new QCheckBox(editRoom);
        cbHeat->setObjectName(QString::fromUtf8("cbHeat"));
        cbHeat->setGeometry(QRect(250, 210, 41, 41));
        lblSummary = new QLabel(editRoom);
        lblSummary->setObjectName(QString::fromUtf8("lblSummary"));
        lblSummary->setGeometry(QRect(30, 10, 281, 51));
        lblName->raise();
        lblCurrTemp->raise();
        currTemp->raise();
        lblPrefTemp->raise();
        editTemp->raise();
        btnUpdate->raise();
        cbThermostat->raise();
        lblThermostat->raise();
        editName->raise();
        lblHeat->raise();
        cbHeat->raise();
        lblSummary->raise();
        summaryTbl->raise();
        roomList = new QListWidget(centralWidget);
        roomList->setObjectName(QString::fromUtf8("roomList"));
        roomList->setGeometry(QRect(551, 30, 219, 421));
        roomList->setMaximumSize(QSize(219, 16777215));
        roomList->setStyleSheet(QString::fromUtf8("#roomList {\n"
"	padding: 5px;\n"
"	color: white;\n"
"	font-size: 20px;\n"
"}\n"
"\n"
"#roomList::item {\n"
"	padding-left: 15px;\n"
"	padding-top: 45px;\n"
"	padding-bottom: 45px;\n"
"	border: 6px solid #27313E;\n"
"	border-radius: 15px;\n"
"	background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4A5D75, stop: 1 #354354);\n"
"	width: 100px;\n"
"	color: white;\n"
"	font: 12pt \"DejaVu Sans\";\n"
"}\n"
"\n"
"#roomList::item::selected {\n"
"	background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4A5D75, stop: 1 #BA3E34);\n"
"	color: white;\n"
"}"));
        roomList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        btnExit = new QPushButton(centralWidget);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        btnExit->setGeometry(QRect(30, 480, 93, 28));
        MainView->setCentralWidget(centralWidget);

        retranslateUi(MainView);
        QObject::connect(btnExit, SIGNAL(clicked()), MainView, SLOT(close()));

        QMetaObject::connectSlotsByName(MainView);
    } // setupUi

    void retranslateUi(QMainWindow *MainView)
    {
        MainView->setWindowTitle(QApplication::translate("MainView", "MainView", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("MainView", "Name: ", 0, QApplication::UnicodeUTF8));
        lblCurrTemp->setText(QApplication::translate("MainView", "Current Temperature: ", 0, QApplication::UnicodeUTF8));
        currTemp->setText(QApplication::translate("MainView", "0", 0, QApplication::UnicodeUTF8));
        lblPrefTemp->setText(QApplication::translate("MainView", "Preferred Temperature: ", 0, QApplication::UnicodeUTF8));
        btnUpdate->setText(QApplication::translate("MainView", "Update Room", 0, QApplication::UnicodeUTF8));
        cbThermostat->setText(QString());
        lblThermostat->setText(QApplication::translate("MainView", "Room with Thermostat:", 0, QApplication::UnicodeUTF8));
        lblHeat->setText(QApplication::translate("MainView", "Heating/Cooling:", 0, QApplication::UnicodeUTF8));
        cbHeat->setText(QString());
        lblSummary->setText(QApplication::translate("MainView", "System Summary", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("MainView", "Debug Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainView: public Ui_MainView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H
