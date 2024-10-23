/**
 **************************************************
 *
 * @file        send-class-A-OTAA.ino
 * @brief       Example for sending data via OTAA to TTN using the LoRa Breakout by Soldered
 *
 *              To successfully run the sketch:
 *              -Follow the instructions below to set up TTN
 *              -Connect the breakout to your Dasduino board (SPI, D0, D1, D2 and D5 pins)
 *              -Connect a LoRa antenna to the breakout
 *              -Open the serial monitor at 4800 baud!
 *
 *              LoRa breakout board 5V: solde.red/333157
 *              LoRa breakout board 3V3: solde.red/333158
 *
 *              NOTE: The library is set up for EU LoRa frequencies
 *
 * @authors     Originally by Ivan Moreno, Eduardo Contreras
 *              Modified by Robert Soric @ soldered.com
 *
 ***************************************************/

/**
 * How to set up TheThingsNetwork with LoRa:
 * 0. Make sure you have a LoRa gateway nearby you can connect to (check ttnmapper.org)
 * 1. Go to TheThingsNetwork.org, make an account and go to your console, select your region
 * 2. Create an application, and register an end device
 * 3. Enter the device specifics manually, select the according frequency plan for your region
 * 4. For LoRaWAN version use 1.0.2.
 * 4. Click "Show advanced activation LoRaWAN class and cluster settings" and select ABP
 * 5. Create the device and copy and paste the generated codes below
 * 6. Connect your Dasduino board to the breakout (Hardware SPI pins and D0, D1, D2 and D5)
 *    NOTE: For Dasduino ConnecPlus (ESP32) use VSPI pins
 * 7. Upload the sketch and open serial monitor at 4800 baud and TTN 'Live Data' console!
 */

#define LORAWAN            // Specify that the module will be used for LoRaWAN network
#include "LoRa-SOLDERED.h" // Include required library

// User set pins are changed here
const sRFM_pins RFM_pins = {
    .CS = 53,
    .RST = 30,
    .DIO0 = 24,
    .DIO1 = 25,
    .DIO2 = 26,
    .DIO5 = 27,
};

// ABP credentials, get these from TTN
const char *devAddr = "00000000";
const char *nwkSKey = "00000000000000000000000000000000";
const char *appSKey = "00000000000000000000000000000000";

// Time constants and variables
#define MESSAGE_INTERVAL_MS 10000 // 10 s interval between messages
unsigned long previousMillis = 0; // Will store last time a message was sent
unsigned int counter = 0;         // Message counter

// Other variables
char messageToSend[50];    // String to send via LoRa
char recievedMessage[255]; // Received string via LoRa
byte recvStatus = 0;

// Setup code, runs only once
void setup()
{
    Serial.begin(4800); // Initialize serial communication
    // At a lower baud rate, to not interfiere with LoRa

    // Initialize the LoRa breakout
    if (!lora.init())
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

    // Set LoRaWAN Class to A
    lora.setDeviceClass(CLASS_A);

    // Set the Data Rate, in LoRa also known as Spreading Factor
    // For more technical info about Spreading Factors, see: thethingsnetwork.org/docs/lorawan/spreading-factors
    // The Spreading Factor is also determined by your region
    // Make sure to set it correctly or else data transfer won't work!
    lora.setDataRate(SF12BW125);

    // Set the correct channel for EU_868
    lora.setChannel(CHRX2);

    // Apply the LoRa credentials that were defined before
    lora.setNwkSKey(nwkSKey);
    lora.setAppSKey(appSKey);
    lora.setDevAddr(devAddr);

    // NOTE: Data sometimes takes a couple minutes to start recieving on TTN
}

// This part of the code runs repeteadly
void loop()
{
    // Check if we're due to send a message
    if (millis() - previousMillis > MESSAGE_INTERVAL_MS)
    {
        // Remember the time
        previousMillis = millis();

        // Format the string to send and save it to messageToSend
        // This can contain any data you want to send
        sprintf(messageToSend, "Counter-%d", counter);

        // First, print it to Serial
        Serial.print("Sending to TTN: ");
        Serial.println(messageToSend);

        // Then, send via LoRa to TTN!
        // Arguments are: data to be sent, length of the data in bytes, confirm (yes or no) and the message port
        lora.sendUplink(messageToSend, strlen(messageToSend), 0, 1);

        // Increment the counter
        counter++;
    }

    // If we have recieved data, print it out to Serial
    // For OTAA, this part is required if you just want to send data as well
    recvStatus = lora.readData(recievedMessage);
    if (recvStatus)
        Serial.println(recievedMessage);

    lora.update(); // Check if LoRa has received anything
}