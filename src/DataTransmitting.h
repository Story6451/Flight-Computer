#include <Arduino.h>
#include <vector>
#include <cstdint>

class DataTransmitting
{
private:
    const int csPin = 10;          // LoRa radio chip select
    const int resetPin = 4;       // LoRa radio reset
    const int irqPin = 2;         // Change for your board; must be a hardware interrupt pin
    /* data */
    // dummy data for testing the rest of the code
    uint32_t pressure = 10000;
    uint16_t temperature = 100;
    std::vector<int16_t> acceleration = { 2, -1, 4 };
    std::vector<uint32_t> magneticFluxDensity = { 10, 50, 20 }; // Magnetometer value * 100
    std::vector<int16_t> rotation = { 0, 1, -4 };
    std::vector<int16_t> gpsCoordinates = { 200, 100 };
    int16_t velocity = -2; // Velocity value * 100
    uint16_t altitude = 2000;
public:
    // creating the packet and adds the start byte to it
    std::vector<uint8_t> CreatePacket(uint8_t start_byte){
        const uint8_t START_BYTE = start_byte;
        std::vector<uint8_t> packet = { START_BYTE };
        return packet;
    }

    // breaks apart any 32bit data into 8bit chunks and adds it to the packet
    void Parse32Bit(std::vector<uint8_t> packet, uint32_t data){
        packet.push_back((data >> 24) & 0xFF);
        packet.push_back((data >> 16) & 0xFF);
        packet.push_back((data >> 8) & 0xFF);
        packet.push_back(data & 0xFF);
    }

    // breaks apart any 16bit data into 8bit chunks and adds it to the packet
    void Parse16Bit(std::vector<uint8_t> packet, uint16_t data){
        packet.push_back((temperature >> 8) & 0xFF);
        packet.push_back(temperature & 0xFF);
    }

    uint16_t CalculateChecksum(std::vector<uint8_t> packet){
        uint16_t checksum = 0;
        for (size_t i=1; i<packet.size(); i++){
            checksum ^= packet[i];
        }
        return checksum;
    }

    DataTransmitting(uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, std::vector<int16_t> magneticFluxDensityDividedBy100, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates, int16_t velocityDividedBy100, uint16_t altitude);
    //uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, std::vector<int16_t> magneticFluxDensity, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates, int16_t velocity/100, uint16_t altitude 
};

