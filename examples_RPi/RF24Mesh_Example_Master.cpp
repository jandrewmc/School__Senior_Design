 
 
 /** RF24Mesh_Example_Master.ino by TMRh20
  * 
  * Note: This sketch only functions on -Arduino Due-
  *
  * This example sketch shows how to manually configure a node via RF24Mesh as a master node, which
  * will receive all data from sensor nodes.
  *
  * The nodes can change physical or logical position in the network, and reconnect through different
  * routing nodes as required. The master node manages the address assignments for the individual nodes
  * in a manner similar to DHCP.
  *
  */
  
#include "RF24Mesh/RF24Mesh.h"  
#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>
#include <iostream>

RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_8MHZ);  
RF24Network network(radio);
RF24Mesh mesh(radio,network);

typedef struct
{
	int16_t nodeid;
	int16_t currentTemperature;
	int16_t currentFanSpeed;
	int16_t currentServoPosition;
	float currentPressure;
}incomingData;

typedef struct
{
	int16_t nodeid;
	int16_t fanSpeed;
	int16_t servoPosition;
}outgoingData;

typedef struct
{
	unsigned long ms;
	unsigned long counter;
}payload_t;

int main(int argc, char** argv) {
  mesh.setNodeID(0);
  mesh.begin();

while(1)
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
     	case 'M': network.read(header,&in,sizeof(in)); 
				printf("%u, %u, %u, %u, %f\n", in.nodeid, in.currentTemperature, in.currentFanSpeed, in.currentServoPosition, in.currentPressure);
                break;
		default:
				payload_t payload;
				network.read(header, &payload, sizeof(payload));
	}
  }
  delay(2000);

	outgoingData out;
	out.nodeid = 9;
	out.fanSpeed = 200;
	out.servoPosition = 10;
	mesh.write(&out, 'N', sizeof(out), out.nodeid);

	delay(2000);

	outgoingData out2;
	out2.nodeid = 9;
	out2.fanSpeed = 100;
	out2.servoPosition = 170;
	mesh.write(&out2, 'N', sizeof(out2), out2.nodeid);
}
return 0;
}

      
      
      
