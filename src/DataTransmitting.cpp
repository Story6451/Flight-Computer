#include <DataTransmitting.h>
//#include <vector>
//#include <cstdint>
#define LORA		//Specify that module will be used for LoRa to LoRa communication
//#include <SPI.h>
#include "LoRa-SOLDERED.h"


String DataTransmitting::onReceive(int packetSize)
{
    String message = "";
    if (packetSize)
    {
        
        while(LoRa.available())
        {
            message += (char)LoRa.read();
        }
        
    }
    return message;
}
void DataTransmitting::Begin()
{
    Serial.println("Initialising Lora");
    LoRa.setPins(CS_PIN, RESET_PIN, IRQ_PIN);// set CS, reset, IRQ pin
    LoRa.begin(FREQUENCY);// Initialize LoRa at 433 MHz

}

// void DataTransmitting::LogData(uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, std::vector<uint32_t> magneticFluxDensity, std::vector<int16_t> rotation, std::vector<int16_t> GpsCoordinates, int16_t velocity, uint16_t altitude){
//     mPressure = pressure;
//     mTemperature = temperature;
//     mAcceleration = acceleration;
//     for (int i=0; i<magneticFluxDensity.size(); i++){
//         mMagneticFluxDensityTimes100[i] = magneticFluxDensity[i]*100;
//     }
//     mRotation = rotation;
//     mGpsCoordinates = GpsCoordinates;
//     mVelocityDividedBy100 = velocity/100;
//     mAltitude = altitude;
// }

void DataTransmitting::Transmit(std::vector<String> dataName, std::vector<double> data)
{
    
    if ((millis() - lastTimeSent) > sendingInterval)
    {
    
        SendPacket(0xAA, dataName, data);
        
        lastTimeSent = millis();
    }
}

String DataTransmitting::ReadLoRa()
{
    return onReceive(LoRa.parsePacket());
}

void DataTransmitting::SendPacket(uint8_t start_byte, std::vector<String> dataName, std::vector<double> data)
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

    uint32_t checksum = CalculateChecksum(data);
    Serial.print(start_byte);
    Serial.print(",");
    Serial.print(data.size());
    Serial.print(",");

    LoRa.beginPacket();
    LoRa.print(start_byte);
    LoRa.print(",");
    LoRa.print(data.size());
    LoRa.print(",");
    for (uint8_t i = 0; i < data.size(); i++)
    {
        Serial.print(dataName[i]);
        Serial.print(",");
        Serial.print(data[i]);
        Serial.print(",");
        LoRa.print(dataName[i]);
        LoRa.print(",");
        LoRa.print(data[i]);
        LoRa.print(",");
    }
    LoRa.print("CKS,");
    LoRa.print(checksum);
    LoRa.print(",");
    LoRa.endPacket();

    Serial.print("CKS,");
    Serial.print(checksum); Serial.println(",");
}

// std::vector<uint8_t> DataTransmitting::CreatePacket(uint8_t start_byte){
//     const uint8_t START_BYTE = start_byte;
//     std::vector<uint8_t> packet = { START_BYTE };
//     return packet;
// }

// void DataTransmitting::Parse32Bit(std::vector<uint8_t>& packet, uint32_t data){
//     packet.push_back((data >> 24) & 0xFF);
//     packet.push_back((data >> 16) & 0xFF);
//     packet.push_back((data >> 8) & 0xFF);
//     packet.push_back(data & 0xFF);
// }

// void DataTransmitting::Parse16Bit(std::vector<uint8_t>& packet, uint16_t data){
//     packet.push_back((data >> 8) & 0xFF);
//     packet.push_back(data & 0xFF);
// }

uint32_t DataTransmitting::CalculateChecksum(std::vector<double> data){
    uint32_t checksum = 0;
    for (uint8_t i=0; i<data.size(); i++){
        checksum += (uint32_t)(abs(data[i]*100));
        // Serial.println(data[i]);
    }
    return checksum;
}

DataTransmitting::DataTransmitting()
    //uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, std::vector<int16_t> magneticFluxDensityDividedBy100, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates, int16_t velocityDividedBy100, uint16_t altitude)
{
    
}
