#include <Arduino.h>
#include <Wire.h>
#include <DataLogging.h>
#include <DataReading.h>
#include <DataTransmitting.h>
#include <kalman.h>
#include <vector>
#include <cstdint>
#define LORA		//Specify that module will be used for LoRa to LoRa communication
#include "LoRa-SOLDERED.h"

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
String message = "";

void OnRecive(int packetSize)
{
  message = "";
  if (packetSize != 0)
  { 
    while(LoRa.available())
    {
        //Serial.print((char)LoRa.read());
        message += (char)LoRa.read();
    }
  }
}

const uint8_t CS_PIN = 37;          // LoRa radio chip select
const uint8_t RESET_PIN = 41;       // LoRa radio reset
const uint8_t IRQ_PIN = 2;         // Change for your board; must be a hardware interrupt pin
const uint64_t FREQUENCY = 433E6;

void setup() 
{
  Serial.begin(9600);
  //Wire.begin();
  //dataLogger.Begin();
  //dataReader.Begin();
  dataTransmitter.Begin();
  //ekf.initkalman();
  LoRa.setPins(CS_PIN, RESET_PIN, IRQ_PIN);// set CS, reset, IRQ pin
  LoRa.begin(FREQUENCY);// Initialize LoRa at 433 MHz
  LoRa.onReceive(OnRecive);
  
  //attachInterrupt(digitalPinToInterrupt(2), OnRecive, RISING);
}


void loop() 
{
  std::vector<int8_t> dataNameToSend;
  std::vector<double> dataToSend;
  
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
  
  Serial.println(message);
}
