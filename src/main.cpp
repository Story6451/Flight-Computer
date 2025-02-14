#include <Arduino.h>
#include <Wire.h>
#include <DataLogging.h>
#include <DataReading.h>
#include <DataTransmitting.h>
#include <kalman.h>
#include <vector>
#include <cstdint>
//#define LORA		//Specify that module will be used for LoRa to LoRa communication
//#include "LoRa-SOLDERED.h"

DataLogging dataLogger;
DataReading dataReader;
DataTransmitting dataTransmitter;

enum DataKeys{
  Accel_X,
  Accel_Y,
  Accel_Z,
  Magnetometer_X,
  Magnetometer_Y,
  Magnetometer_Z,
  CheckSum,
};

EKF ekf;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Setting Up");
  //Wire.begin();
  //dataLogger.Begin();
  //dataReader.Begin();
  std::function<void(int)> onrecieve = bind(&DataTransmitting::OnRecieve, &dataTransmitter, std::placeholders::_1);
  auto fonrecieve = onrecieve.target<void(*)(int)>();
  void (*phonrecieve)(int) = *fonrecieve;
  dataTransmitter.Begin(phonrecieve);
  //ekf.initkalman();
  //attachInterrupt(digitalPinToInterrupt(2), OnRecive, RISING);
}


void loop() 
{
  std::vector<int8_t> dataNameToSend;
  std::vector<double> dataToSend;
  
  Serial.println("Looping");
  //Accelerometer
  dataReader.ReadAccelerometer();
  dataReader.ReadMagnetometer();
  float aX = dataReader.ReturnAccelerometerX();
  float aY = dataReader.ReturnAccelerometerY();
  float aZ = dataReader.ReturnAccelerometerZ();
  float mX = dataReader.ReturnMagnetometerX();
  float mY = dataReader.ReturnMagnetometerY();
  float mZ = dataReader.ReturnMagnetometerZ();
  
  dataNameToSend.push_back(DataKeys::Accel_X);
  dataToSend.push_back(aX);

  dataNameToSend.push_back(DataKeys::Accel_Y);
  dataToSend.push_back(aY);

  dataNameToSend.push_back(DataKeys::Accel_Z);
  dataToSend.push_back(aZ);

  dataNameToSend.push_back(DataKeys::Magnetometer_X);
  dataToSend.push_back(mX);

  dataNameToSend.push_back(DataKeys::Magnetometer_Y);
  dataToSend.push_back(mY);

  dataNameToSend.push_back(DataKeys::Magnetometer_Z);
  dataToSend.push_back(mZ);
  //Serial.println(aX);
  dataTransmitter.Transmit(dataNameToSend, dataToSend);
  // Serial.print("Accel X: ");
  // Serial.println(dataReader.ReturnAccelerometerX());

  // Serial.print("Accel Y: ");
  // Serial.println(dataReader.ReturnAccelerometerY());

  // Serial.print("Accel Z: ");
  // Serial.println(dataReader.ReturnAccelerometerZ());
  //dataTransmitter.Transmit(dataNameToSend, dataToSend);
  // Serial.print("Magnetic Field Strength X: ");
  // Serial.println(dataReader.ReturnMagnetometerX());

  // Serial.print("Magnetic Field Strength Y: ");
  // Serial.println(dataReader.ReturnMagnetometerY());

  // Serial.print("Magnetic Field Strength Z: ");
  // Serial.println(dataReader.ReturnMagnetometerZ());

  // //Baro
  // dataReader.ReadBarometer();

  // Serial.print("Baro Altitude: ");
  // Serial.println(dataReader.ReturnAltitude());

  // Serial.print("Pressure: ");
  // Serial.println(dataReader.ReturnPressure());

  // Serial.print("Temperature: ");
  // Serial.println(dataReader.ReturnTemperature());

  // float accel = -dataReader.ReturnAccelerometerX();
  // ekf.predict(accel);

  // ekf.updateBaro(dataReader.ReturnAltitude());

  // Serial.print("Kalman Position: ");
  // Serial.println(ekf.getKalmanPosition());

  // Serial.println();
  
  //Serial.println("test");
  //delay(100);
  /*
  dataReader.ReadGPSStream();
  dataReader.GPSStreamToData();

  Serial.print("Latitude: "); Serial.print(dataReader.ReturnLatitude()); Serial.print(" ");
  Serial.print("Longitude: "); Serial.print(dataReader.ReturnLongitude()); Serial.print(" ");
  Serial.print("Altitude: "); Serial.print(dataReader.ReturnAltitude()); Serial.print(" ");
  Serial.print("Velocity: "); Serial.print(dataReader.ReturnGPSVelocity()); Serial.print(" ");
  Serial.print("Number of Satellites: "); Serial.print(dataReader.ReturnSatellitesConnected()); Serial.println(" ");

  */
}
