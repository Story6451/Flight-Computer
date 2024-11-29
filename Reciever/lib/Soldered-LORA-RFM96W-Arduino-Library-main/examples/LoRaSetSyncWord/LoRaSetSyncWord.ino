/**
 **************************************************
 *
 * @file        LoRaSetSyncWord.ino
 * @brief       Sends a message every half second, and polls continually
 *              for new incoming messages. Sets the LoRa radio's Sync Word.
 *
 *              Spreading factor is basically the radio's network ID. Radios with different
 *              Sync Words will not receive each other's transmissions. This is one way you
 *              can filter out radios you want to ignore, without making an addressing scheme.
 *              
 *
 *
 *
 * @authors    	Tom Igoe
 *
 * Modified by: Soldered for use with www.soldered.com/333157 , www.soldered.com/333158
 *
 ***************************************************/

///                 Arduino      RFM95/96/97/98
///                 GND----------GND   (ground in)
///                 3V3----------3.3V  (3.3V in)
///             pin D4-----------RESET  (RESET)
/// interrupt 0 pin D2-----------DIO0  (interrupt request out)
///          SS pin D10----------NSS   (CS chip select in)
///         SCK pin D13----------SCK   (SPI clock in)
///        MOSI pin D11----------MOSI  (SPI Data in)
///        MISO pin D12----------MISO  (SPI Data out)
/// This is pinout for Dasduino Core, if you are using other MCU, use SPI pins
///and Interrupt pin 0, if Dasduino ConnectPlus is used
/// (or any other ESP32 board) use pins(SS=27, RST=2, DIO0=32, MISO=33, MOSI=25,SCK=26)

#define LORA		//Specify that module will be used for LoRa to LoRa communication
#include <SPI.h>              // include libraries
#include "LoRa-SOLDERED.h"

const int csPin = 10;          // LoRa radio chip select
const int resetPin = 4;       // LoRa radio reset
const int irqPin = 2;         // Change for your board; must be a hardware interrupt pin

byte msgCount = 0;            // Count of outgoing messages
int interval = 2000;          // Interval between sends
long lastSendTime = 0;        // Time of last packet send

void setup()
{
  Serial.begin(9600);   //Initialize serial communication with PC
  while (!Serial);
  
  Serial.println("LoRa Duplex - Set sync word");

  // Override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(868E6))
  {             // Initialize ratio at 868 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // If failed, do nothing
  }

  LoRa.setSyncWord(0xF3);           // Ranges from 0-0xFF, default 0x34, see API docs
  Serial.println("LoRa init succeeded.");
}

void loop()
{
  if (millis() - lastSendTime > interval)
  {
    String message = "HeLoRa World! ";   // Send a message
    message += msgCount;
    sendMessage(message);
    Serial.println("Sending " + message);
    lastSendTime = millis();            // Timestamp the message
    interval = random(2000) + 1000;    // 2-3 seconds
    msgCount++;
  }

  // Parse for a packet, and call onReceive with the result:
  onReceive(LoRa.parsePacket());
}

void sendMessage(String outgoing)
{
  LoRa.beginPacket();                   // Start packet
  LoRa.print(outgoing);                 // Add payload
  LoRa.endPacket();                     // Finish packet and send it
  msgCount++;                           // Increment message ID
}

void onReceive(int packetSize)
{
  if (packetSize == 0) return;          // If there's no packet, return

  // read packet header bytes:
  String incoming = "";
 
  while (LoRa.available()) //Read from incoming buffer
  {
    incoming += (char)LoRa.read();
  }
 
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
}
