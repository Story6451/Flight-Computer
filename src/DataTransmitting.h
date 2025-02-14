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

    uint16_t sendingInterval = 500;    //change this based on your error micro controller setup
    uint64_t lastTimeSent = 0;
    bool sending = false;

    String message = "";
    
public:
    // Initialising the LoRa
    void Begin(void (*onrecieve)(int));

    // creating the packet and adds the start byte to it
    std::vector<uint8_t> CreatePacket(uint8_t start_byte);

    //calculates the checksum using the values of the data sent
    uint32_t CalculateChecksum(std::vector<double> data);

    //sends the packet
    void SendPacket(uint8_t start_byte, std::vector<int8_t> dataName, std::vector<double> data);

    //runs through a tranmission loop
    void Transmit(std::vector<int8_t> dataName, std::vector<double> data);

    void testFunc2(int y);

    //reads and returns data from the LoRa
    String ReadLoRa();

    //runs through the recieving routine
    void OnRecieve(int packetSize);

    DataTransmitting();
};