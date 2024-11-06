#include <Arduino.h>


class DataTransmitting
{
private:
    const int csPin = 10;          // LoRa radio chip select
    const int resetPin = 4;       // LoRa radio reset
    const int irqPin = 2;         // Change for your board; must be a hardware interrupt pin
    /* data */
public:
    DataTransmitting();
    //uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, uint32_t magneticFluxDensity, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates, int16_t velocity/100, uint16_t altitude 
};

