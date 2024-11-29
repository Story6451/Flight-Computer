#include <Arduino.h>
#define LORA		//Specify that module will be used for LoRa to LoRa communication
#include <SPI.h>
#include "LoRa-SOLDERED.h"

class Reciever{
private:
    const int csPin = 4;          // LoRa radio chip select
    const int resetPin = 2;       // LoRa radio reset
    const int irqPin = 3;         // Change for your board; must be a hardware interrupt pin

    uint8_t mExpectedPacketSize = 5;
    uint8_t data[34];
    uint8_t dataPos = 0;
public:
    void Begin(int csPin, int resetPin, int irqPin);
    void Recieve();
};