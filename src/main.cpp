#include <Arduino.h>
#include <Wire.h>
#include <DataLogging.h>
#include <DataReading.h>
#include <DataTransmitting.h>
#include <kalman.h>

DataLogging dataLogger;
DataReading dataReader;
//DataTransmitting dataTransmitter;

EKF ekf;

void setup() 
{
  Serial.begin(9600);

  dataLogger.Begin();
  dataReader.Begin();
  //dataReader.AltitudeCalibration();
  // put your setup code here, to run once:
  //dataTransmitter.InitialiseLoRa();

  ekf.initkalman();
}

void loop() 
{
  Serial.println("test");
  // put your main code here, to run repeatedly:
  Serial.print(dataReader.ReadAccelerometer());
}
