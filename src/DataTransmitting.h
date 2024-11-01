#include <Arduino.h>
#include <vector>
#include <cstdint>
#define LORA		//Specify that module will be used for LoRa to LoRa communication
#include <SPI.h>
#include "LoRa-SOLDERED.h"

class DataTransmitting
{
private:
    const int csPin = 10;          // LoRa radio chip select
    const int resetPin = 4;       // LoRa radio reset
    const int irqPin = 2;         // Change for your board; must be a hardware interrupt pin

    int counter = 0;
    /* data */
public:
    DataTransmitting(){

        // (list of all data to recieve and in which format)
        //uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, uint32_t magneticFluxDensity, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates, int16_t velocity/100, uint16_t altitude 
        // dummy data for the rest of the code to work
        uint32_t pressure = 10000;
        uint16_t temperature = 100;
        std::vector<int16_t> acceleration = { 2, -1, 4 };
        uint32_t magneticFluxDensity = 100;
        std::vector<int16_t> rotation = { 0, 1, -4 };
        std::vector<int16_t> gpsCoordinates = { 200, 100 };
        int16_t velocity = -20;
        uint16_t altitude = 2000;
        
        // creating the packet and the start byte
        const uint8_t START_BYTE = 0xAA;
        std::vector<uint8_t> packet = { START_BYTE };

        // breaking apart and adding all of the data to the packet
        packet.push_back((pressure >> 24) & 0xFF);
        packet.push_back((pressure >> 16) & 0xFF);
        packet.push_back((pressure >> 8) & 0xFF);
        packet.push_back(pressure & 0xFF);

        packet.push_back((temperature >> 8) & 0xFF);
        packet.push_back(temperature & 0xFF);

        for (int16_t value : acceleration){
            packet.push_back((value >> 8) & 0xFF);
            packet.push_back(value & 0xFF);
        }

        packet.push_back((magneticFluxDensity >> 24) & 0xFF);
        packet.push_back((magneticFluxDensity >> 16) & 0xFF);
        packet.push_back((magneticFluxDensity >> 8) & 0xFF);
        packet.push_back(magneticFluxDensity & 0xFF);

        for (int16_t value : rotation){
            packet.push_back((value >> 8) & 0xFF);
            packet.push_back(value & 0xFF);
        }

        for (int16_t gpsCoordinate : gpsCoordinates){
            packet.push_back((gpsCoordinate >> 8) & 0xFF);
            packet.push_back(gpsCoordinate & 0xFF);
        }

        packet.push_back((velocity >> 8) & 0xFF);
        packet.push_back(velocity & 0xFF);

        packet.push_back((altitude >> 8) & 0xFF);
        packet.push_back(altitude & 0xFF);

        // calculating and adding the checksum to the packet
        uint8_t checksum = 0;
        for (size_t i=1; i<packet.size(); i++){
            checksum ^= packet[i];
        }
        packet.push_back(checksum);
    }
};

