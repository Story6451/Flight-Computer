#include <DataTransmitting.h>
#include <vector>
#include <cstdint>
#define LORA		//Specify that module will be used for LoRa to LoRa communication
#include <SPI.h>
#include "LoRa-SOLDERED.h"

DataTransmitting::DataTransmitting()
{
    LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

    // (list of all data to recieve and in which format)
    //uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, 
    //uint32_t magneticFluxDensity, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates,
    //int16_t velocity/100, uint16_t altitude 
     
    // creating the packet and the start byte
    std::vector<uint8_t> packet = CreatePacket(0xAA);

    // breaking apart and adding all of the data to the packet
    Parse32Bit(packet, pressure);
    Parse16Bit(packet, temperature); 

    for (int16_t value : acceleration){
        Parse16Bit(packet, value);
    }
    for (int16_t value : magneticFluxDensity){
        Parse32Bit(packet, value);
    }

    for (int16_t value : rotation){
        Parse16Bit(packet, value);
    }

    for (int16_t gpsCoordinate : gpsCoordinates){
        Parse16Bit(packet, gpsCoordinate);
    }

    Parse16Bit(packet, velocity);
    Parse16Bit(packet, altitude);

    // calculating and adding the checksum to the packet
    uint16_t checksum = 0;
    for (size_t i=1; i<packet.size(); i++){
        checksum ^= packet[i];
    }
    packet.push_back(checksum);

    // for UI tests
    for (uint8_t value : packet){
        Serial.println(value);
    }

    // write to LoRa
    // Send packet
    LoRa.beginPacket(); //Begin sending
    for (uint8_t value : packet){
        LoRa.print(value);
    }
    LoRa.endPacket(); //End sending
};