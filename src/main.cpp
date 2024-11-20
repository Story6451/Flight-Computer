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
  Wire.begin();

  //dataLogger.Begin();
  dataReader.Begin();
  //dataReader.AltitudeCalibration();
  // put your setup code here, to run once:
  //dataTransmitter.InitialiseLoRa();

  //ekf.initkalman();
}

void loop() 
{
  //Serial.println("test");
  // put your main code here, to run repeatedly:

  //Accelerometer
  dataReader.ReadAccelerometer();
  Serial.print("Accel X: ");
  Serial.println(dataReader.ReturnAccelerometerX());

  Serial.print("Accel Y: ");
  Serial.println(dataReader.ReturnAccelerometerY());

  Serial.print("Accel Z: ");
  Serial.println(dataReader.ReturnAccelerometerZ());

  //Magnetometer
  dataReader.ReadMagnetometer();
  Serial.print("Magnetic Field Strength X: ");
  Serial.println(dataReader.ReturnMagnetometerX());

  Serial.print("Magnetic Field Strength Y: ");
  Serial.println(dataReader.ReturnMagnetometerY());

  Serial.print("Magnetic Field Strength Z: ");
  Serial.println(dataReader.ReturnMagnetometerZ());

  Serial.println();
  delay(100);
}
