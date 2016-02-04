#include "RF24Mesh/RF24Mesh.h"  
#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>

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

void getIncomingData()
{
	while(network.available())
	{
		RF24NetworkHeader header;
		network.peek(header);

		incomingData in;
		
		switch (header.type)
		{
			case 'M': 
				network.read(neader, &in, sizeof(in));
				break;
			default:
				payload_t payload;
				network.read(header, &payload, sizeof(payload));
				break;
		}
	}
}

void sendOutgoingData()
{
	
}

int main(int argc, char** argv) 
{
	mesh.setNodeID(0);
 	mesh.begin();

	while(1)
	{
  		mesh.update();
		mesh.DHCP();
  
		getIncomingData();
		sendOutgoingData();
  	}
	return 0;
}

