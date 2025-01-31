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
        Serial.println(" ");
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

void DataTransmitting::Transmit(std::vector<String>& dataName, std::vector<double>& data)
{
    
    if ((millis() - lastTimeSent) > sendingInterval)
    {
    
        SendPacket(0xAA, dataName, data);
        
        lastTimeSent = millis();
    }

    // Parse for a packet, and call onReceive with the result:
    onReceive(LoRa.parsePacket());
}

void DataTransmitting::SendPacket(uint8_t start_byte, std::vector<String>& dataName, std::vector<double>& data)
{
    if (dataName.size() < data.size())
    {
        
        for (uint8_t i = 0; i < data.size() - i; i++)
        {
            dataName.push_back("null");
        }
        
    }
    if (data.size() < dataName.size())
    {
        for (uint8_t i = 0; i < dataName.size() - i; i++)
        {
            dataName.push_back(0);
        }
        
    }

    uint16_t checksum = CalculateChecksum(data);
    LoRa.beginPacket();
    LoRa.print(start_byte);
    LoRa.print("-");
    LoRa.print(data.size());
    
    Serial.print("Sending Packet: ");
    for (uint8_t i = 0; i < data.size(); i++)
    {
        Serial.print(dataName[i]);
        Serial.print("-");
        Serial.print(data[i]);
        Serial.print("-");
        LoRa.print(dataName[i]);
        LoRa.print("-");
        LoRa.print(data[i]);
        LoRa.print("-");
    }
    LoRa.print(checksum);
    LoRa.print("-");
    LoRa.endPacket();
    Serial.print(" Checksum: "); Serial.println(checksum);
}
// (list of all data to recieve and in which format)
    //uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, 
    //std::vector<int16_t> magneticFluxDensity, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates,
    //int16_t velocity/100, uint16_t altitude 

// void DataTransmitting::SendSmallPacket(uint8_t start_byte, std::vector<String>& dataName, std::vector<uint16_t>& data)
// {
//     std::vector<uint8_t> packet = CreatePacket(start_byte);
//     packet.push_back(0x02);
//     for (uint8_t i = 0; i < 6; i++)
//     {
//         Parse16Bit(packet, data[i]);
//     }
    

//     // // breaking apart and adding all of the data to the packet
//     // Parse32Bit(packet, mPressure);
//     // Parse16Bit(packet, mTemperature); 
//     // // breaking apart and adding all of the data to the packet
//     // /*
//     // Parse32Bit(packet, mPressure);
//     // Parse16Bit(packet, mTemperature); 
//     // */

//     // for (int16_t value : mAcceleration){
//     //     Parse16Bit(packet, value);
//     // }
//     // for (int16_t value : mMagneticFluxDensityTimes100){
//     //     Parse32Bit(packet, value);
//     // }

//     // for (int16_t value : mRotation){
//     //     Parse16Bit(packet, value);
//     // }

//     // for (int16_t gpsCoordinate : mGpsCoordinates){
//     //     Parse16Bit(packet, gpsCoordinate);
//     // }

//     // Parse16Bit(packet, mVelocityDividedBy100);
//     // Parse16Bit(packet, mAltitude);
//     // /*
//     // Parse16Bit(packet, mVelocityDividedBy100);
//     // Parse16Bit(packet, mAltitude);
//     // */

//     // // calculating and adding the checksum to the packet
    
//     uint16_t checksum = CalculateChecksum(packet);
//     Parse16Bit(packet, checksum);
//     //packet.push_back(checksum);
//     packet.push_back(0xBB);
//     LoRa.beginPacket();
    
//     Serial.print("Sending Packet: ");
//     for (uint8_t i = 0; i < 6; i++)
//     {
//         Serial.print(dataName[i]);
//         Serial.print("-");
//         Serial.print(packet[i]);
//         Serial.print("-");
//         LoRa.print(dataName[i]);
//         LoRa.print("-");
//         LoRa.print(data[i]);
//         LoRa.print("-");
//     }
    
//     // for (uint8_t value : packet)
//     // {
//     //     //Serial.print(value);
//     //     LoRa.print(value);
//     //     LoRa.print("-");
//     // }
//     Serial.print(" Checksum: "); Serial.println(checksum);
//     LoRa.endPacket();
// }

// void DataTransmitting::SendLargePacket(uint8_t start_byte, std::vector<String>& dataName, std::vector<uint32_t>& data)
// {
//     std::vector<uint8_t> packet = CreatePacket(start_byte);
//     packet.push_back(0x04);
//     for (uint8_t i = 0; i < 6; i++)
//     {
//         Parse32Bit(packet, data[i]);
//     }

//     // calculating and adding the checksum to the packet
    
//     uint16_t checksum = CalculateChecksum(packet);
//     Parse16Bit(packet, checksum);
//     //packet.push_back(checksum);
//     packet.push_back(0xBB);
//     LoRa.beginPacket();
    
//     Serial.print("Sending Packet: ");
//     for (uint8_t i = 0; i < 6; i++)
//     {
//         Serial.print(dataName[i]);
//         Serial.print("-");
//         Serial.print(packet[i]);
//         Serial.print("-");
//         LoRa.print(dataName[i]);
//         LoRa.print("-");
//         LoRa.print(packet[i]);
//         LoRa.print("-");
//     }
    
//     Serial.print(" Checksum: "); Serial.println(checksum);
//     LoRa.endPacket();
// }

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

uint16_t DataTransmitting::CalculateChecksum(std::vector<double>& data){
    uint16_t checksum = 0;
    for (uint8_t i=0; i<data.size(); i++){
        checksum += data[i];
    }
    return checksum;
}

DataTransmitting::DataTransmitting()
    //uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, std::vector<int16_t> magneticFluxDensityDividedBy100, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates, int16_t velocityDividedBy100, uint16_t altitude)
{
    
}
