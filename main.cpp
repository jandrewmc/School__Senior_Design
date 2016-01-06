 
 
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

RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_8MHZ);  
RF24Network network(radio);
RF24Mesh mesh(radio,network);

int main(int argc, char** argv) 
{
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
    
			//need to receive an array containing the data that we need
			uint32_t dat=0;
			network.read(header,&dat,sizeof(dat)); 
			printf("Rcv %u from 0%o\n",dat,header.from_node);

			//calculate what needs to be sent to this node

			//send to this node
  		}
		delay(2);
  	}
	return 0;
}

