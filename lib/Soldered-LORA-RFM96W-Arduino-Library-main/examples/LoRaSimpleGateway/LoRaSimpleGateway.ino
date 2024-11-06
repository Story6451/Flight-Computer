/**
 **************************************************
 *
 * @file        LoRaSimpleGateway.ino
 * @brief       This code uses InvertIQ function to create a simple Gateway/Node logic.
 * 
 *              Gateway - Sends messages with enableInvertIQ()
 *                      - Receives messages with disableInvertIQ()
 *
 *              Node    - Sends messages with disableInvertIQ()
 *                      - Receives messages with enableInvertIQ()
 *
 *              With this arrangement a Gateway never receive messages from another Gateway
 *              and a Node never receive message from another Node.
 *              Only Gateway to Node and vice versa.
 *
 *              This code receives messages and sends a message every second.
 *
 *              InvertIQ function basically invert the LoRa I and Q signals.
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
#include <SPI.h>              // Include libraries
#include "LoRa-SOLDERED.h"

const int csPin = 10;          // LoRa radio chip select
const int resetPin = 4;       // LoRa radio reset
const int irqPin = 2;         // Change for your board; must be a hardware interrupt pin

const long frequency = 868E6;  // LoRa Frequency

void setup()
{
  Serial.begin(9600);   //Initialize serial communication with PC
  while (!Serial);

    // Override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(frequency))
  {
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // If failed, do nothing
  }

  Serial.println("LoRa init succeeded.");
  Serial.println();
  Serial.println("LoRa Simple Gateway");
  Serial.println("Only receive messages from nodes");
  Serial.println("Tx: invertIQ enable");
  Serial.println("Rx: invertIQ disable");
  Serial.println();

  LoRa.onReceive(onReceive);
  LoRa.onTxDone(onTxDone);
  LoRa_rxMode();   //Set LoRa to receive mode
}

void loop()
{
  if (runEvery(5000)) // Repeat every 5000 millis
  { 

    String message = "HeLoRa World! ";
    message += "I'm a Gateway! ";
    message += millis();

    LoRa_sendMessage(message); // Send a message

    Serial.println("Send Message!");
  }
}

void LoRa_rxMode()
{
  LoRa.disableInvertIQ();               // Normal mode
  LoRa.receive();                       // Set receive mode
}

void LoRa_txMode()
{
  LoRa.idle();                          // Set standby mode
  LoRa.enableInvertIQ();                // Active invert I and Q signals
}

void LoRa_sendMessage(String message)
{
  LoRa_txMode();   //Set LoRa to transmitt mode                        // Set tx mode
  LoRa.beginPacket();                   // Start packet
  LoRa.print(message);                  // Add payload
  LoRa.endPacket(true);                 // Finish packet and send it
}

void onReceive(int packetSize)	//Callback on receive data
{
  String message = "";

  while (LoRa.available())	//Read from incoming buffer
  {
    message += (char)LoRa.read();
  }

  Serial.print("Gateway Receive: ");
  Serial.println(message);
}

void onTxDone()	//Callback on transmission done
{
  Serial.println("TxDone");
  LoRa_rxMode();   //Set LoRa to receive mode 
}

boolean runEvery(unsigned long interval) //If interval milliseconds has past from last run, run again
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}
