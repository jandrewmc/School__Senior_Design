#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include "DHT.h"
#include <SFE_BMP180.h>
#include <Wire.h>
#include <PWMServo.h>

RF24 radio(8, 10);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

typedef struct
{
	int16_t nodeid;
	int16_t currentTemperature;
	int16_t currentFanSpeed;
	int16_t currentServoPosition;
	float currentPressure;
} outgoingData;

typedef struct
{
	int16_t nodeid;
	int16_t fanSpeed;
	int16_t servoPosition;
} incomingData;

struct payload_t
{
	unsigned long ms;
	unsigned long counter;
};

DHT tempSensor(7, DHT11);

SFE_BMP180 pressure;

PWMServo myservo;

outgoingData out;

//This method will set the unique identifier
//for the register, based on DIP switches
//on the device itself.  The input will be
//in binary format.
int getNodeID()
{
	int nodeID;

	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(3, INPUT);
	int state = 0;
  
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, HIGH);
	state = digitalRead(3);
	nodeID += state * 8;
	digitalWrite(4, HIGH);
	digitalWrite(5, LOW);
	digitalWrite(6, HIGH);
	state = digitalRead(3);
	nodeID += state * 4;
	digitalWrite(4, LOW);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	state = digitalRead(3);
	nodeID += state * 2;
	digitalWrite(4, HIGH);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	state = digitalRead(3);
	nodeID += state;

	out.nodeid = nodeID;
 
	return nodeID;
}

//this method returns the current farenheight temperature from the sensor;
void getCurrentTemperature()
{
	out.currentTemperature = (int) tempSensor.readTemperature(true);
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
					out.currentPressure = P;
				}
			}
		}
	}
}

void setup() 
{
	delay(2000);
	myservo.attach(SERVO_PIN_A);
	mesh.setNodeID(getNodeID());
	mesh.begin();
	tempSensor.begin();
	pressure.begin();
}

void loop()
{
	getCurrentTemperature();
	getCurrentPressure();	

	mesh.update();

	mesh.write(&out, 'M', sizeof(out));
	while (network.available())
	{
		RF24NetworkHeader header;
		network.peek(header);

		switch (header.type)
		{
			case 'N':
        		incomingData in;
				network.read(header, &in, sizeof(in));
				if (in.servoPosition != out.currentServoPosition)
				{
				  out.currentServoPosition = in.servoPosition;
				  myservo.write(out.currentServoPosition);
				}
				if (in.fanSpeed != out.currentFanSpeed)
				{
				  out.currentFanSpeed = in.fanSpeed;
				}
				break;
			default:
				payload_t payload;
				network.read(header, &payload, sizeof(payload));
				break;
		}
	}
	delay(2000);
}
