#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>
#include "DHT.h"
#include <SFE_BMP180.h>
#include <Wire.h>
#include <Servo.h>

RF24 radio(9, 10);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

typedef struct
{
	int nodeid;
	int currentTemperature;
	double currentPressure;
	int currentFanSpeed;
	int currentServoPosition;
} outgoingData;

typedef struct
{
	int fanSpeed;
	int servoPosition;
} incomingData;

DHT tempSensor(7, DHT11);

SFE_BMP180 pressure;

Servo myservo;

outgoingData *out = new outgoingData;

//This method will set the unique identifier
//for the register, based on DIP switches
//on the device itself.  The input will be
//in binary format.
int getNodeID()
{
	int nodeID;
	pinMode(2, INPUT);
	pinMode(3, INPUT);
	pinMode(4, INPUT);
	pinMode(5, INPUT);

	int state = digitalRead(2);
	nodeID += state * 8;
	state = digitalRead(3);
	nodeID += state * 4;
	state = digitalRead(4);
	nodeID += state * 2;
	state = digitalRead(5);
	nodeID += state * 1;
	return nodeID;
}

//this method returns the current farenheight temperature from the sensor;
void getCurrentTemperature()
{
	out->currentTemperature = (int) dht.readTemperature(true);
}

void getCurrentPressure()
{
	char status;
	double T, P, p0, a;

	status = pressure.startTemperature();
	if (status != 0)
	{
		delay(status);
		status = pressure.getTemperature(T);
		if (status != 0)
		{
			status = pressure.startPressure(3);
			if (status != 0)
			{
				delay(status);
				status = pressure.getPressure(P, T);
				if (status != 0)
				{
					out->currentPressure = P;
				}
			}
		}
	}
}

void setup() 
{
  	Serial.begin(115200);
	myservo.attach(8);
	mesh.setNodeID(getNodeID());
	mesh.begin();
	tempSensor.begin();
	pressure.begin();
}

void loop()
{
	mesh.update();
	getCurrentTemperature();
	getCurrentPressure();	
}
