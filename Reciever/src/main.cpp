#include "Recieving.h"
#define LORA		//Specify that module will be used for LoRa to LoRa communication
#include <SPI.h>
#include "LoRa-SOLDERED.h"

const int csPin = 4;          // LoRa radio chip select
const int resetPin = 2;       // LoRa radio reset
const int irqPin = 3;         // Change for your board; must be a hardware interrupt pin

Reciever myReciever;

void setup()
{
  myReciever.Begin(csPin, resetPin, irqPin);
}

void loop()
{
  /*int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    // Received a packet
    Serial.print("Received packet '");

    // Read packet
    while (LoRa.available())
	{
      Serial.print((char)LoRa.read()); 
    }

    // Print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
  */
  myReciever.Recieve();
}