#include <Arduino.h>
#include <DataLogging.h>
#include <DataReading.h>
#include <DataTransmitting.h>

DataLogging dataLogger;
DataReading dataReader;
DataTransmitting dataTransmitter;

void setup() 
{
  Serial.begin(9600);
  dataReader.AltitudeCalibration();
  // put your setup code here, to run once:
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
