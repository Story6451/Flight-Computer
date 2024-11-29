#include "Recieving.h"
#define LORA		//Specify that module will be used for LoRa to LoRa communication
#include <SPI.h>
#include "LoRa-SOLDERED.h"

void Reciever::Begin(int csPin, int resetPin, int irqPin){
    Serial.begin(9600);  //Initialize serial communication with PC
    while (!Serial);

    Serial.println("LoRa Receiver");
  
    // Override the default CS, reset, and IRQ pins (optional)
    LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

    if (!LoRa.begin(433E6)) // Initialize LoRa at 433 MHz
    {
        Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void Reciever::Recieve(){
    // Try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize)
    {
        // Received a packet
        //Serial.print("Received packet '");

        // Read packet
        while (LoRa.available())
	    {
        data[dataPos] = (char)LoRa.read();
        dataPos += 1; 
        }
        dataPos = 0;
        // uint16_t dataChecksum = (data[mExpectedPacketSize - 2] >> 8) + data[mExpectedPacketSize - 1]; 
        // uint16_t checkSum = 0;
        // for (int8_t i=0; i<(mExpectedPacketSize - 2); i++){
        //     checkSum ^= data[i];
        // }
        Serial.write(data, packetSize);
        //Serial.println(" ");
        // if (dataChecksum == checkSum){
        //     for (uint8_t i=0; i<mExpectedPacketSize; i++){
        //         Serial.print(data[i]);
        //     }
        //     Serial.println(" ");
        // }
        

        // Print RSSI of packet
        //Serial.print("' with RSSI ");
        //Serial.println(LoRa.packetRssi());
  }
}