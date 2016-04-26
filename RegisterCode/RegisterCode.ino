#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include "DHT.h"
#include <PWMServo.h>

//note: pins 9, 11, 12, 13 are used by the RF Communicator
int radioCEPin = 10;
int radioCSNPin = 8;
int tempSensorPin = 5;
int fanControlPin = 6;
int motionSensorPin = 7;
int pressureSensorPin = A4;
int servoPin = 9;
int fanPowerPin = 3;

//mux pins A, B, and C are all outputs from the micro
//mux output pin is an input to the micro
int muxAPin = 1;
int muxBPin = 2;
int muxCPin = 3;
int muxOutputPin = 4;

RF24 radio(radioCEPin, radioCSNPin);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

typedef struct
{
	uint16_t nodeid;
	uint16_t currentTemperature;
	uint16_t currentFanSpeed;
	uint16_t currentServoPosition;
	uint16_t currentPressure;
	uint16_t isMotionDetected;
} outgoingData;

typedef struct
{
	uint16_t fanSpeed;
	uint16_t servoPosition;
} incomingData;

DHT tempSensor(tempSensorPin, DHT11);

PWMServo myservo;

outgoingData out;

//This method will set the unique identifier
//for the register, based on DIP switches
//on the device itself.  The input will be
//in binary format.
int updateNodeID()
{
	int nodeID = 0;

	pinMode(muxAPin, OUTPUT);
	pinMode(muxBPin, OUTPUT);
	pinMode(muxCPin, OUTPUT);
	pinMode(muxOutputPin, INPUT);
  
	digitalWrite(muxCPin, LOW); digitalWrite(muxBPin, LOW); digitalWrite(muxAPin, LOW);
	nodeID |= digitalRead(muxOutputPin) << 0;

	digitalWrite(muxCPin, LOW); digitalWrite(muxBPin, LOW); digitalWrite(muxAPin, HIGH);
	nodeID |= digitalRead(muxOutputPin) << 1;

	digitalWrite(muxCPin, LOW); digitalWrite(muxBPin, HIGH); digitalWrite(muxAPin, LOW);
	nodeID |= digitalRead(muxOutputPin) << 2;

	digitalWrite(muxCPin, LOW); digitalWrite(muxBPin, HIGH); digitalWrite(muxAPin, HIGH);
	nodeID |= digitalRead(muxOutputPin) << 3;

	digitalWrite(muxCPin, HIGH); digitalWrite(muxBPin, LOW); digitalWrite(muxAPin, LOW);
	nodeID |= digitalRead(muxOutputPin) << 4;

	digitalWrite(muxCPin, HIGH); digitalWrite(muxBPin, LOW); digitalWrite(muxAPin, HIGH);
	nodeID |= digitalRead(muxOutputPin) << 5;

	digitalWrite(muxCPin, HIGH); digitalWrite(muxBPin, HIGH); digitalWrite(muxAPin, LOW);
	nodeID |= digitalRead(muxOutputPin) << 6;

	digitalWrite(muxCPin, HIGH); digitalWrite(muxBPin, HIGH); digitalWrite(muxAPin, HIGH);
	nodeID |= digitalRead(muxOutputPin) << 7;

	out.nodeid = nodeID;	

	pinMode(muxOutputPin, OUTPUT);

	digitalWrite(muxAPin, LOW);
	digitalWrite(muxBPin, LOW);
	digitalWrite(muxCPin, LOW);
	digitalWrite(muxOutputPin, LOW);

	return nodeID;
}

//this method returns the current farenheight temperature from the sensor;
void updateCurrentTemperature()
{
	out.currentTemperature = (int) tempSensor.readTemperature(true);
}

void updateCurrentPressure()
{
	out.currentPressure = analogRead(A4);
}

void setFanSpeed(int val)
{
	analogWrite(fanControlPin, val);
}

void updateMotionDetected()
{
	out.isMotionDetected = digitalRead(motionSensorPin);
}

void setup() 
{
	delay(2000);

	pinMode(motionSensorPin, INPUT);
	pinMode(fanControlPin, OUTPUT);

	myservo.attach(servoPin);

	mesh.setNodeID(updateNodeID());

	mesh.begin();

	tempSensor.begin();

  myservo.write(90);
  out.currentServoPosition = 90;
}

void loop()
{
  delay(2000);
  
	if (out.currentPressure == 0 || out.currentFanSpeed == 0)
		digitalWrite(fanPowerPin, LOW);
	else
		digitalWrite(fanPowerPin, HIGH);

	updateCurrentTemperature();
	updateCurrentPressure();	
	updateMotionDetected();
	mesh.update();

	mesh.write(&out, 'M', sizeof(out));

	while (network.available())
	{
		RF24NetworkHeader header;
		network.peek(header);

		switch (header.type)
		{
			//if there is incoming data
			case 'N':
        		incomingData in;
				// get it
				network.read(header, &in, sizeof(in));
			
				//if the servo position needs to change
				if (in.servoPosition != out.currentServoPosition)
				{
					// update it in the outgoing data
				  	out.currentServoPosition = in.servoPosition;
					//and write it to the servo
				  	myservo.write(out.currentServoPosition);
				}

				// if the fan speed needs to change
				if (in.fanSpeed != out.currentFanSpeed)
				{
					// update it in the outgoing data
				  	out.currentFanSpeed = in.fanSpeed;

					// and write it to the fan
					setFanSpeed(in.fanSpeed);
				}
				break;
			default:
				break;
		}
	}
}
