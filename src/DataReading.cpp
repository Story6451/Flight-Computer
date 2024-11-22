#include <DataReading.h>
#include <LIS3MDL.h>
#include <LSM6.h>
#include <LPS.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

//this is a one off exception do not follow the proceeding two lines by example else ILL HUNT YOU
const uint8_t RX_PIN = 4;
const uint8_t TX_PIN = 3;

LPS baro;
LIS3MDL mag;
LSM6 imu;
TinyGPSPlus gps;
SoftwareSerial ss(RX_PIN, TX_PIN);

DataReading::DataReading()
{  
}

void DataReading::Begin()
{
  if (!baro.init())
  {
    Serial.println("Failed to autodetect pressure sensor!");
  }
  baro.enableDefault();

  if (!mag.init()) 
  {
    Serial.println("Failed to detect and initialize LIS3MDL magnetometer!");
    
  }
  mag.enableDefault();

  if (!imu.init()) 
  {
      Serial.println("Failed to detect and initialize LSM6 IMU!");
      
  }
  imu.enableDefault();

  /*
  gps setup code goes here
  */
  ss.begin(GPS_BAUD);
  
  AltitudeCalibration();

  Serial.println("Calibration complete");
}

void DataReading::AltitudeCalibration()
{
 float pressureSum = 0;
 for (int i = 0; i < ITER_NO; i++)
 {
  pressureSum += baro.readPressureMillibars();
 }

 mGroundPressure = pressureSum / ITER_NO;
}

void DataReading::ReadAccelerometer() 
{
    imu.read();
    mAccelXValue = imu.a.x * ACCEL_SENSITIVITY * 9.81 / 1000.0;
    mAccelYValue = imu.a.y * ACCEL_SENSITIVITY * 9.81 / 1000.0;
    mAccelZValue = imu.a.z * ACCEL_SENSITIVITY * 9.81 / 1000.0;
}

void DataReading::ReadGPSStream()
{
  while (ss.available() > 0)
  {

    if (gps.encode(ss.read()))
    {
      
    }
  }
}

//encapsulating the data
float DataReading::ReturnAccelerometerX()
{
  return mAccelXValue;
}
float DataReading::ReturnAccelerometerY()
{
  return mAccelYValue;
}
float DataReading::ReturnAccelerometerZ()
{
  return mAccelZValue;
}
float DataReading::ReturnMagnetometerX()
{
  return mMagnetometerXValue;
}
float DataReading::ReturnMagnetometerY()
{
  return mMagnetometerYValue;
}
float DataReading::ReturnMagnetometerZ()
{
  return mMagnetometerZValue;
}

void DataReading::ReadMagnetometer() {
    mag.read();
    mMagnetometerXValue = mag.m.x;
    mMagnetometerYValue = mag.m.y;
    mMagnetometerZValue = mag.m.z;
}

void DataReading::ReadBarometer()
{
  mPressure = baro.readPressureMillibars();
  mTemperature = baro.readTemperatureC();
  mAltitude = baro.pressureToAltitudeMeters(mPressure, mGroundPressure);
}

float DataReading::ReturnAltitude()
{
  return mAltitude;
}
float DataReading::ReturnPressure()
{
  return mPressure;
}
float DataReading::ReturnTemperature()
{
  return mTemperature;
}
void DataReading::CalculateHeading() 
{
  float normAcc = sqrt(mAccelXValue * mAccelXValue + mAccelYValue * mAccelYValue + mAccelZValue * mAccelZValue);
  mAccelXValue /= normAcc;
  mAccelYValue /= normAcc;
  mAccelZValue /= normAcc;

  mMagnetometerPitch = asin(-mAccelXValue);
  mMagnetometerRoll = asin(mAccelYValue / cos(mMagnetometerPitch));

  mMagnetometerXCalculated = (mMagnetometerXValue * cos(mMagnetometerPitch)) + (mMagnetometerZValue * sin(mMagnetometerPitch));
  mMagnetometerYCalculated = (mMagnetometerXValue * sin(mMagnetometerRoll) * sin(mMagnetometerPitch)) + (mMagnetometerYValue * cos(mMagnetometerRoll)) - (mMagnetometerZValue * sin(mMagnetometerRoll) * cos(mMagnetometerPitch));

  mUncalibratedHeading = atan2(mMagnetometerYCalculated, mMagnetometerXCalculated);

  mUncalibratedHeading = mUncalibratedHeading * 180 / M_PI;
  if (mUncalibratedHeading < 0) 
  {
      mUncalibratedHeading += 360;
  }
}