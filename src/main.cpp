#include <Arduino.h>
#include <Wire.h>
#include <DataLogging.h>
#include <DataReading.h>
#include <DataTransmitting.h>

DataLogging dataLogger;
DataReading dataReader;
//DataTransmitting dataTransmitter;

void setup() 
{
  Serial.begin(9600);

  dataLogger.Begin();
  dataReader.Begin();
  //dataReader.AltitudeCalibration();
  // put your setup code here, to run once:
  //dataTransmitter.InitialiseLoRa();
}

void loop() 
{

  Serial.println("test");
  // put your main code here, to run repeatedly:
}
