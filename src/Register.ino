#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const uint64_t xmtPipe = 0xAABBCCDDEELL;
const uint64_t rcvPipe = 0x1122334455LL;

RF24 radio(CE_PIN, CSN_PIN);

// This is the packet of data that will be
// transmitted.  
// 0: Temperature
// 1: Fan Speed
// 2: Servo Location
// 3: Pressure

int dataPacketXMT[4];
int dataPacketRCV[4];

void startReceiving();
void startTransmitting();

void setup()
{
	// Initialize the serial port
	// I think maybe there is a 
	// library that we are using
	// that requires this.  For
	// now, we are including it
	// for diagnostic/debugging
	// purposes.
	Serial.begin(9600);
	delay(1000);
	Serial.println("Start the radio");
	radio.begin();
	radio.setChannel(1);
}

void loop()
{
	startReceiving();
	delay(1000);
	startTransmitting();
	delay(1000);
}

void startReceiving()
{
	radio.openReadingPipe(1, rcvPipe);
	radio.startListening();
	if (radio.available())
	{
		radio.read(dataPacketRCV, sizeof(dataPacketRCV));

		for (int i = 0; i < sizeof(dataPacketRCV); i++)
		{
			Serial.println(dataPacketRCV[i]);	
		}
	}
	else 
	{
		Serial.println("No radio available");
	}
	radio.stopListening();
}

void startTransmitting()
{
	Serial.println("Transmit");
	radio.openWritingPipe(rcvPipe);

	dataPacketXMT[0] = 100;
	dataPacketXMT[1] = 200;
	dataPacketXMT[2] = 300;
	dataPacketXMT[3] = 400;

	radio.write(dataPacketXMT, sizeof(dataPacketXMT));
}

