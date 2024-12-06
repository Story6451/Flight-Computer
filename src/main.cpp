#include <Arduino.h>
#include <Wire.h>
#include <DataLogging.h>
#include <DataReading.h>
#include <DataTransmitting.h>
#include <kalman.h>

DataLogging dataLogger;
DataReading dataReader;
DataTransmitting dataTransmitter;

EKF ekf;

void setup() 
{
  Serial.begin(9600);
  Wire.begin();

  //dataLogger.Begin();
  dataReader.Begin();
  dataTransmitter.Begin();
  ekf.initkalman();
}

void loop() 
{
  /*
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

  //Baro
  dataReader.ReadBarometer();

  Serial.print("Baro Altitude: ");
  Serial.println(dataReader.ReturnAltitude());

  Serial.print("Pressure: ");
  Serial.println(dataReader.ReturnPressure());

  Serial.print("Temperature: ");
  Serial.println(dataReader.ReturnTemperature());

  float accel = -dataReader.ReturnAccelerometerX();
  ekf.predict(accel);

  ekf.updateBaro(dataReader.ReturnAltitude());

  Serial.print("Kalman Position: ");
  Serial.println(ekf.getKalmanPosition());

  Serial.println();
  */
  Serial.println("M");
  dataTransmitter.Transmit();
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
