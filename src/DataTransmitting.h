#include <Arduino.h>
#include <vector>
#include <cstdint>

class DataTransmitting
{
private:
    const uint8_t CS_PIN = 37;          // LoRa radio chip select
    const uint8_t RESET_PIN = 41;       // LoRa radio reset
    const uint8_t IRQ_PIN = 2;         // Change for your board; must be a hardware interrupt pin
    /* data */
    // dummy data for testing the rest of the code
    uint32_t mPressure = 10000;
    uint16_t mTemperature = 100;
    std::vector<int16_t> mAcceleration = { 2, -1, 4 };
    std::vector<uint32_t> mMagneticFluxDensityTimes100 = { 10, 50, 20 }; // Magnetometer value * 100
    std::vector<int16_t> mRotation = { 0, 1, -4 };
    std::vector<int16_t> mGpsCoordinates = { 200, 100 };
    int16_t mVelocityDividedBy100 = -2; // Velocity value * 100
    uint16_t mAltitude = 2000;

    uint16_t sendingInterval = 500;
    uint32_t lastTimeSent = 0;
    int mExpectedDataSize = 34;
    char data[34] = {};
    uint8_t dataPos = 0;
public:
    // Initialising the LoRa
    void Begin();

    // Allowing logging of Data
    void LogData(uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, std::vector<uint32_t> magneticFluxDensity, std::vector<int16_t> rotation, std::vector<int16_t> GpsCoordinates, int16_t velocity, uint16_t altitude);

    // creating the packet and adds the start byte to it
    std::vector<uint8_t> CreatePacket(uint8_t start_byte);

    // breaks apart any 32bit data into 8bit chunks and adds it to the packet
    void Parse32Bit(std::vector<uint8_t>& packet, uint32_t data);

    // breaks apart any 16bit data into 8bit chunks and adds it to the packet
    void Parse16Bit(std::vector<uint8_t>& packet, uint16_t data);

    uint16_t CalculateChecksum(std::vector<uint8_t>& packet);

    void Transmit();

    DataTransmitting();
        //uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, std::vector<int16_t> magneticFluxDensityDividedBy100, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates, int16_t velocityDividedBy100, uint16_t altitude);
    //uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, std::vector<int16_t> magneticFluxDensity, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates, int16_t velocity/100, uint16_t altitude 
};

//uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, std::vector<int16_t> magneticFluxDensityDividedBy100, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates, int16_t velocityDividedBy100, uint16_t altitude)
//uint32_t pressure, uint16_t temperature, std::vector<int16_t> acceleration, std::vector<int16_t> magneticFluxDensityDividedBy100, std::vector<int16_t> rotation, std::vector<int16_t> gpsCoordinates, int16_t velocityDividedBy100, uint16_t altitude);