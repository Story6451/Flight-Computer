#include <DataTransmitting.h>
//#include <vector>
//#include <cstdint>
#define LORA		//Specify that module will be used for LoRa to LoRa communication
//#include <SPI.h>
#include "LoRa-SOLDERED.h"


void onReceive(int packetSize)
{
  if (packetSize)
  {
    while(LoRa.available()){
      Serial.print((char)LoRa.read());
    }
    Serial.println(" ");
  }
}
void DataTransmitting::Begin()
{
    Serial.println("Initialising Lora");
    LoRa.setPins(CS_PIN, RESET_PIN, IRQ_PIN);// set CS, reset, IRQ pin
    LoRa.begin(433E6);// Initialize LoRa at 433 MHz

}

void DataTransmitting::LogData(uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, std::vector<uint32_t> magneticFluxDensity, std::vector<int16_t> rotation, std::vector<int16_t> GpsCoordinates, int16_t velocity, uint16_t altitude){
    mPressure = pressure;
    mTemperature = temperature;
    mAcceleration = acceleration;
    for (int i=0; i<magneticFluxDensity.size(); i++){
        mMagneticFluxDensityTimes100[i] = magneticFluxDensity[i]*100;
    }
    mRotation = rotation;
    mGpsCoordinates = GpsCoordinates;
    mVelocityDividedBy100 = velocity/100;
    mAltitude = altitude;
}

bool isSent = false;

void DataTransmitting::Transmit()
{
    std::vector<uint8_t> packet = CreatePacket(0xAA);

    if (millis() - lastTimeSent > sendingInterval)
    {
        String message = "Sent Packet";   // Send a message
        LoRa.beginPacket();
        LoRa.print("Spoon");
        LoRa.endPacket();
        Serial.println("Sending " + message);
        lastTimeSent = millis();            // Timestamp the message
    }

  // Parse for a packet, and call onReceive with the result:
  onReceive(LoRa.parsePacket());
// (list of all data to recieve and in which format)
    //uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, 
    //std::vector<int16_t> magneticFluxDensity, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates,
    //int16_t velocity/100, uint16_t altitude 
     
    // creating the packet and the start byte
    // if ((millis() - lastTimeSent) > sendingInterval){
    //     lastTimeSent = millis();
    
    //     // breaking apart and adding all of the data to the packet
    //     Parse32Bit(packet, mPressure);
    //     Parse16Bit(packet, mTemperature); 
    //     // breaking apart and adding all of the data to the packet
    //     Parse32Bit(packet, mPressure);
    //     Parse16Bit(packet, mTemperature); 

    //     for (int16_t value : mAcceleration){
    //         Parse16Bit(packet, value);
    //     }
    //     for (int16_t value : mMagneticFluxDensityTimes100){
    //         Parse32Bit(packet, value);
    //     }
    //     for (int16_t value : mAcceleration){
    //         Parse16Bit(packet, value);
    //     }
    //     for (int16_t value : mMagneticFluxDensityTimes100){
    //         Parse32Bit(packet, value);
    //     }

    //     for (int16_t value : mRotation){
    //         Parse16Bit(packet, value);
    //     }
    //     for (int16_t value : mRotation){
    //         Parse16Bit(packet, value);
    //     }

    //     for (int16_t gpsCoordinate : mGpsCoordinates){
    //         Parse16Bit(packet, gpsCoordinate);
    //     }
    //     for (int16_t gpsCoordinate : mGpsCoordinates){
    //         Parse16Bit(packet, gpsCoordinate);
    //     }

    //     Parse16Bit(packet, mVelocityDividedBy100);
    //     Parse16Bit(packet, mAltitude);
    //     Parse16Bit(packet, mVelocityDividedBy100);
    //     Parse16Bit(packet, mAltitude);

    //     // calculating and adding the checksum to the packet
    //     uint16_t checksum = CalculateChecksum(packet);
    //     packet.push_back(checksum);
    //     packet.push_back(0xBB);
    //     // calculating and adding the checksum to the packet
    //     uint16_t checksum = CalculateChecksum(packet);
    //     packet.push_back(checksum);
    //     packet.push_back(0xBB);

}

std::vector<uint8_t> DataTransmitting::CreatePacket(uint8_t start_byte){
    const uint8_t START_BYTE = start_byte;
    std::vector<uint8_t> packet = { START_BYTE };
    return packet;
}

void DataTransmitting::Parse32Bit(std::vector<uint8_t>& packet, uint32_t data){
    packet.push_back((data >> 24) & 0xFF);
    packet.push_back((data >> 16) & 0xFF);
    packet.push_back((data >> 8) & 0xFF);
    packet.push_back(data & 0xFF);
}

void DataTransmitting::Parse16Bit(std::vector<uint8_t>& packet, uint16_t data){
    packet.push_back((data >> 8) & 0xFF);
    packet.push_back(data & 0xFF);
}

uint16_t DataTransmitting::CalculateChecksum(std::vector<uint8_t>& packet){
    uint16_t checksum = 0;
    for (size_t i=1; i<packet.size(); i++){
        checksum ^= packet[i];
    }
    return checksum;
}

DataTransmitting::DataTransmitting()
    //uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, std::vector<int16_t> magneticFluxDensityDividedBy100, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates, int16_t velocityDividedBy100, uint16_t altitude)
{
    
}
