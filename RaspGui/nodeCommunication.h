#ifndef NODECOMMUNICATION_H
#define NODECOMMUNICATION_H

#include "RF24Mesh/RF24Mesh.h"
#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>
#include <iostream>
#include <QThread>
#include <QVector>

class nodeCommunication : public QThread
{
protected:
    void run();

public:
    int nodeUpdate();
    void connectToDatabase();
    void queryDatabase();
    void updateDatabaseForOne(int nodeId);
    void prioritize();

    void generateTestData();

    struct room
    {
        int nodeId;
        QString name;
        int currTemp;
        int prefTemp;
        int servoPosition;
        int pressure;
        int fanSpeed;
        bool withThermostat;
        bool inUse;
        int difference;
        QString differenceType;
    };

    QVector<room> roomVector;

    int roomCounter;

    struct incomingData
    {
        uint16_t nodeid;
        uint16_t currentTemperature;
        uint16_t currentFanSpeed;
        uint16_t currentServoPosition;
        uint16_t currentPressure;
        uint16_t isMotionDetected;
    };

    struct outgoingData
    {
        uint16_t fanSpeed;
        uint16_t servoPosition;
    };

public slots:
    void updateDatabaseForAll();

};

#endif
