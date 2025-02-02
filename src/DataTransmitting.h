#include <Arduino.h>
#include <vector>
#include <cstdint>

class DataTransmitting
{
private:
    const uint8_t CS_PIN = 37;          // LoRa radio chip select
    const uint8_t RESET_PIN = 41;       // LoRa radio reset
    const uint8_t IRQ_PIN = 2;         // Change for your board; must be a hardware interrupt pin
    const uint64_t FREQUENCY = 433E6;

    uint16_t sendingInterval = 2000;    //change this based on your error micro controller setup
    uint64_t lastTimeSent = 0;
    
public:
    // Initialising the LoRa
    void Begin();

    // creating the packet and adds the start byte to it
    std::vector<uint8_t> CreatePacket(uint8_t start_byte);

    //calculates the checksum using the values of the data sent
    uint32_t CalculateChecksum(std::vector<double> data);

    //sends the packet
    void SendPacket(uint8_t start_byte, std::vector<String> dataName, std::vector<double> data);

    //runs through a tranmission loop
    void Transmit(std::vector<String> dataName, std::vector<double> data);

    //reads and returns data from the LoRa
    String ReadLoRa();

    //runs through the recieving routine
    String DataTransmitting::onReceive(int packetSize);

    DataTransmitting();
};