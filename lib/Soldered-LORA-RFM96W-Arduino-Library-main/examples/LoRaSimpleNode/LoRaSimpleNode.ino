/**
 **************************************************
 *
 * @file        LoRaSimpleNode.ino
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

/**
 **************************************************
 *
 * @file        LoRaSimpleNode.ino
 * @brief       This code uses InvertIQ function to create a simple Gateway/Node logic.
 * 
 *              With this arrangement a Gateway never receive messages from another Gateway
 *              and a Node never receive message from another Node.
 *              Only Gateway to Node and vice versa.
 *
 *              To successfully run the sketch:
 *              -Connect the breakout to your Dasduino board (SPI, D0)
 *              -Connect a LoRa antenna to the breakout
 *              -Open the serial monitor at 4800 baud!
 *
 *              LoRa breakout board 5V: solde.red/333157
 *              LoRa breakout board 3V3: solde.red/333158
 *
 *
 * @authors     Originally by Tom Igoe
 *              Modified by Robert Soric @ soldered.com
 *
 ***************************************************/

/**
 * Pinout:
 * LoRa breakout board              Dasduino Core / Connect / ConnectPlus
 * GND----------------------------->GND
 * VCC----------------------------->VCC
 * OE------------------------------>VCC
 * MISO---------------------------->12/IO12/IO12
 * MOSI---------------------------->11/IO13/IO13
 * SCK----------------------------->13/IO14/IO14
 * CS------------------------------>10/IO15/IO15
 * RESET--------------------------->Set by user
 * DIO0---------------------------->Set by user, must be a hardware interrupt pin
 *
 * Set the pins below as well
 */

const int csPin = 10;
const int resetPin = 4;
const int irqPin = 2;

#define LORA // Specify that module will be used for LoRa to LoRa communication
#include "LoRa-SOLDERED.h"
#include <SPI.h> // include libraries

const long frequency = 868E6; // LoRa Frequency

// Setup code, runs only once
void setup()
{
    Serial.begin(9600); // Initialize serial communication
    // At a lower baud rate, to not interfiere with LoRa

    // Override the default CS, reset, and IRQ pins
    LoRa.setPins(csPin, resetPin, irqPin);

    if (!LoRa.begin(frequency)) // Initialize LoRa with custom frequency
    {
        // The breakout was not detected, inform the user and go to infinite loop
        Serial.println("LoRa Breakout not detected!");
        Serial.println("Check connections!");
        while (true)
        {
            delay(100);
        }
    }

    Serial.println("LoRa breakout initialized successfully!");
    Serial.println();
    Serial.println("LoRa Simple Node");
    Serial.println("Only receive messages from gateways");
    Serial.println("Tx: invertIQ disable");
    Serial.println("Rx: invertIQ enable");
    Serial.println();

    LoRa.onReceive(onReceive); // Set callback on receive data
    LoRa.onTxDone(onTxDone);   // Set callback on transmission done
    LoRa_rxMode();             // Set LoRa to receive mode
}

void loop()
{
    if (runEvery(1000)) // Repeat every 1000 millis
    {

        String message = "HeLoRa World! ";
        message += "I'm a Node! ";
        message += millis();

        LoRa_sendMessage(message); // Send a message

        Serial.println("Send Message!");
    }
}

void LoRa_rxMode()
{
    LoRa.enableInvertIQ(); // Active invert I and Q signals
    LoRa.receive();        // Set receive mode
}

void LoRa_txMode()
{
    LoRa.idle();            // Set standby mode
    LoRa.disableInvertIQ(); // Normal mode
}

void LoRa_sendMessage(String message)
{
    LoRa_txMode();        // Set LoRa to transmitt mode                        // Set tx mode
    LoRa.beginPacket();   // Start packet
    LoRa.print(message);  // Add payload
    LoRa.endPacket(true); // Finish packet and send it
}

void onReceive(int packetSize) // Callback on receive data
{
    String message = "";

    while (LoRa.available()) // Read from incoming buffer
    {
        message += (char)LoRa.read();
    }

    Serial.print("Node Receive: ");
    Serial.println(message);
}

void onTxDone() // Callback on transmission done
{
    Serial.println("TxDone");
    LoRa_rxMode(); // Set LoRa to receive mode
}

boolean runEvery(unsigned long interval) // If interval milliseconds has past from last run, run again
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
