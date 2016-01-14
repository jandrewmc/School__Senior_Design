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

DHT dht(7, DHT11);

SFE_BMP180 pressure;

Servo myservo;

uint32_t displayTimer = 0;

struct payload_t {
  unsigned long ms;
  unsigned long counter;
};

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
float getCurrentTemperature()
{
	return dht.readTemperature(true);
}

double getPressure()
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
					return (P);
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
	dht.begin();
	pressure.begin();

}



void loop() {

  mesh.update();

  // Send to the master node every second
  if (millis() - displayTimer >= 1000) {
    displayTimer = millis();

    // Send an 'M' type message containing the current millis()
    if (!mesh.write(&displayTimer, 'M', sizeof(displayTimer))) {

      // If a write fails, check connectivity to the mesh network
      if ( ! mesh.checkConnection() ) {
        //refresh the network address
        Serial.println("Renewing Address");
        mesh.renewAddress();
      } else {
        Serial.println("Send fail, Test OK");
      }
    } else {
      Serial.print("Send OK: "); Serial.println(displayTimer);
    }
  }

  while (network.available()) {
    RF24NetworkHeader header;
    payload_t payload;
    network.read(header, &payload, sizeof(payload));
    Serial.print("Received packet #");
    Serial.print(payload.counter);
    Serial.print(" at ");
    Serial.println(payload.ms);
  }
}






