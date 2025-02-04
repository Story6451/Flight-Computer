#include <DataTransmitting.h>
#define LORA		//Specify that module will be used for LoRa to LoRa communication
#include "LoRa-SOLDERED.h"


void DataTransmitting::OnReceive(int packetSize)
{
    //String message = "";
    if (packetSize != 0)
    {
        
        while(LoRa.available())
        {
            //Serial.print((char)LoRa.read());
            message += (char)LoRa.read();
        }
        
    }
    
}
void DataTransmitting::Begin()
{
    Serial.println("Initialising Lora");
    LoRa.setPins(CS_PIN, RESET_PIN, IRQ_PIN);// set CS, reset, IRQ pin
    LoRa.begin(FREQUENCY);// Initialize LoRa at 433 MHz
}

void DataTransmitting::Transmit(std::vector<String> dataName, std::vector<double> data)
{
    
    if ((millis() - lastTimeSent) > sendingInterval)
    {
        //Serial.println(millis() - lastTimeSent);
        SendPacket(0xAA, dataName, data);
        
        lastTimeSent = millis();
    }
}

String DataTransmitting::ReadLoRa()
{
    return message;//OnReceive(LoRa.parsePacket());
}

void DataTransmitting::SendPacket(uint8_t start_byte, std::vector<String> dataName, std::vector<double> data)
{
    if (dataName.size() != data.size())
    {
        dataName.clear();
        data.clear();
        dataName.push_back("error");
        data.push_back(0);        
    }

    uint32_t checksum = CalculateChecksum(data);

    //start lora packet 
    LoRa.beginPacket();
    LoRa.print(start_byte);
    LoRa.print(",");
    LoRa.print(data.size());
    LoRa.print(",");
    for (uint8_t i = 0; i < data.size(); i++)
    {
        LoRa.print(dataName[i]);
        LoRa.print(",");
        LoRa.print(data[i]);
        LoRa.print(",");
    }
    LoRa.print("CKS,");
    LoRa.print(checksum);
    LoRa.print(",");
    LoRa.endPacket();
    //end lora packet
    //only info relavent to the lora transmission should go between the start and end of the packet to ensure that its as fast as possible
    // Serial.print(start_byte);
    // Serial.print(",");
    // Serial.print(data.size());
    // Serial.print(",");
    // for (uint8_t i = 0; i < data.size(); i++)
    // {
    //     Serial.print(dataName[i]);
    //     Serial.print(",");
    //     Serial.print(data[i]);
    //     Serial.print(",");
    // }
    //Serial.print("CKS,");
    //Serial.print(checksum); Serial.println(",");
}
uint32_t DataTransmitting::CalculateChecksum(std::vector<double> data){
    uint32_t checksum = 0;
    for (uint8_t i=0; i<data.size(); i++){
        checksum += (uint32_t)(abs(data[i]*100));
        
    }
    return checksum;
}

DataTransmitting::DataTransmitting()
{
    
}
