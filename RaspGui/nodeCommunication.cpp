#include <iostream>
#include <QDebug>
#include "nodeCommunication.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>

using namespace std;

RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_8MHZ);
RF24Network network(radio);
RF24Mesh mesh(radio,network);

void nodeCommunication::run()
{
    qDebug() << "changes built.";
    connectToDatabase();
    nodeUpdate();
}

void initializeSystemRoom()
{

}

int nodeCommunication::nodeUpdate()
{
    mesh.setNodeID(0);
    mesh.begin();

    int vectorSize = 0;
    bool exists = false;
    QString nameStr = "Room ";
    QString roomStr = "";
    roomCounter = 0;

    room *systemRoom = new room();
    systemRoom->name = "System";
    systemRoom->prefTemp = 65;
    roomVector.push_back(*systemRoom);
    roomCounter++;

    //for debugging---:
    //generateTestData();

    while (1)
    {
        mesh.update();
        mesh.DHCP();
        while(network.available())
        {
            RF24NetworkHeader header;
            network.peek(header);

            incomingData in;

            switch(header.type)
            {
                case 'M':
                    network.read(header, &in, sizeof(in));
                    break;
                default:
                    break;
            }

            vectorSize = roomVector.size() - 1; //need to subtract one for system node
            qDebug() << in.nodeid;

            if (vectorSize != 0)
            {
                exists = false;
                for (int i=0; i < vectorSize + 1; i++)
                {
                    if (roomVector[i].nodeId == in.nodeid)
                    {
                        exists = true;

                        qDebug() << "update existing. ID = " << in.nodeid;

                        roomVector[i].currTemp = in.currentTemperature;
                        roomVector[i].fanSpeed = in.currentFanSpeed;
                        roomVector[i].servoPosition = in.currentServoPosition;
                        roomVector[i].pressure = in.currentPressure;
                        roomVector[i].inUse = in.isMotionDetected;
                    }
                }
                if (!exists)
                {

                    qDebug() << "adding new. ID = " << in.nodeid;

                    room *r = new room();
                    roomStr = QString::number(roomCounter);
                    r->name = nameStr + roomStr;
                    roomCounter++;
                    r->nodeId = in.nodeid;
                    r->currTemp = in.currentTemperature;
                    r->fanSpeed = in.currentFanSpeed;
                    r->servoPosition = in.currentServoPosition;
                    r->pressure = in.currentPressure;
                    r->inUse = in.isMotionDetected;
                    r->withThermostat = false;
                    r->prefTemp = 65;
                    roomVector.push_back(*r);
                }
            }
            else
            {

                qDebug() << "first node found. adding new. ID = " << in.nodeid;

                room *r = new room();
                roomStr = QString::number(roomCounter);
                r->name = nameStr + roomStr;
                roomCounter++;
                r->nodeId = in.nodeid;
                r->currTemp = in.currentTemperature;
                r->fanSpeed = in.currentFanSpeed;
                r->servoPosition = in.currentServoPosition;
                r->pressure = in.currentPressure;
                r->inUse = in.isMotionDetected;
                r->withThermostat = false;
                r->prefTemp = 65;
                roomVector.push_back(*r);
            }

            //use algorithm to adjust system when system is on
            if (in.currentPressure != 0) //when there is pressure, the system is on
            {
                //prioritize the rooms that need to be adjusted
                prioritize();
            }

            qDebug() << in.isMotionDetected;

            //create new record each time the motion sensor detects the room is in use
            if (in.isMotionDetected == true)
            {
                updateDatabaseForOne(in.nodeid);
            }
        }
    }
    return 0;
}

void nodeCommunication::connectToDatabase()
{
    //need to create a database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/pi/dataCollection.db");

    //open the database
    bool ok = db.open();
    //verify the DB is open

    if (ok)
        qDebug() << "dataCollection.db is open";
    else
        qDebug() << "error opening dataCollection.db";

    return;
}

void nodeCommunication::updateDatabaseForAll()
{
    QSqlQuery insertQuery;
    QString insertStr = "";
    for (int i=1; i < roomVector.size(); i++)
    {
        insertStr.clear();
        insertStr = QString("INSERT INTO nodeData VALUES (%1, %2, %3, %4, %5, %6, %7, %8, date('now'), time('now'))")
            .arg(roomVector[i].nodeId).arg(roomVector[i].currTemp).arg(roomVector[i].prefTemp)
            .arg(roomVector[i].fanSpeed).arg(roomVector[i].servoPosition)
            .arg(roomVector[i].pressure).arg(roomVector[i].inUse).arg(roomVector[i].withThermostat);
        insertQuery.prepare(insertStr);
        qDebug() << insertStr;
        qDebug() << insertQuery.exec();
    }
    return;
}

void nodeCommunication::updateDatabaseForOne(int nodeId)
{
    QSqlQuery insertQuery;
    QString insertStr = "";
    for (int i=1; i < roomVector.size(); i++)
    {
        if (roomVector[i].nodeId == nodeId)
        {
            insertStr = QString("INSERT INTO nodeData VALUES (%1, %2, %3, %4, %5, %6, %7, %8, date('now'), time('now'))")
                    .arg(nodeId).arg(roomVector[i].currTemp).arg(roomVector[i].prefTemp)
                    .arg(roomVector[i].fanSpeed).arg(roomVector[i].servoPosition)
                    .arg(roomVector[i].pressure).arg(1).arg(roomVector[i].withThermostat);
        }
    }
    insertQuery.prepare(insertStr);
    qDebug() << insertStr;
    qDebug() << insertQuery.exec();
    return;
}

void nodeCommunication::prioritize()
{
    //first, calculate and set the differences for each room
    int curr, pref;
    for (int i=1; i<roomVector.size();i++)
    {
        curr = roomVector[i].currTemp;
        pref = roomVector[i].prefTemp;
        if (pref > curr)
        { //room needs to be heated
            roomVector[i].difference = pref - curr;
            roomVector[i].differenceType = "positive";
        }
        else if (pref < curr)
        { //room needs to be cooled
            roomVector[i].difference = curr - pref;
            roomVector[i].differenceType = "negative";
        }
        else
        { //room is at preferred temp
            roomVector[i].difference = 0;
            roomVector[i].differenceType = "equal";
        }
    }

    //next, use the differences and the thermostat boolean to determine priorities


    return;
}

void nodeCommunication::queryDatabase()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM nodeData");
    qDebug() << query.exec();

    while (query.next()){
        int currNodeIdOfRecord = query.value(0).toInt();
        qDebug() << currNodeIdOfRecord;
    }

    return;
}

//for debugging---:
void nodeCommunication::generateTestData()
{
    room *r = new room();
    r->name = "Room 1";
    r->nodeId = 1;
    r->currTemp = 62;
    r->fanSpeed = 10;
    r->servoPosition = 15;
    r->pressure = 3;
    r->withThermostat = false;
    r->prefTemp = 65;
    roomVector.push_back(*r);
    room *k = new room();
    k->name = "Room 2";
    k->nodeId = 2;
    k->currTemp = 63;
    k->fanSpeed = 0;
    k->servoPosition = 0;
    k->pressure = 13;
    k->withThermostat = false;
    k->prefTemp = 65;
    roomVector.push_back(*k);
    room *l = new room();
    l->name = "Room 3";
    l->nodeId = 3;
    l->currTemp = 67;
    l->fanSpeed = 20;
    l->servoPosition = 35;
    l->pressure = 0;
    l->withThermostat = false;
    l->prefTemp = 65;
    roomVector.push_back(*l);
    roomCounter += 3;
    return;
}
