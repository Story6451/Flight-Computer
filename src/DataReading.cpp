#include <DataReading.h>
#include <LIS3MDL.h>
#include <LSM6.h>
#include <LPS.h>

LPS baro;
LIS3MDL mag;
LSM6 imu;


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

  //AltitudeCalibration();

  Serial.println("Calibration complete");
}

void DataReading::AltitudeCalibration()
{
  float altitudeSum = 0;

  for (int i = 0; i < ITER_NO; i++)
  {
    pressure = baro.readPressureMillibars();
    altitude = baro.pressureToAltitudeMeters(pressure);
    altitudeSum += altitude;
  }

  altitudeOffset = altitudeSum / ITER_NO;
}

void DataReading::ReadAccelerometer() 
{
    imu.read();
    AccelXValue = imu.a.x;
    AccelYValue = imu.a.y;
    AccelZValue = imu.a.z;
}

float DataReading::ReturnAccelerometerX()
{
  return AccelXValue;
}
float DataReading::ReturnAccelerometerY()
{
  return AccelYValue;
}
float DataReading::ReturnAccelerometerZ()
{
  return AccelZValue;
}

void DataReading::ReadMagnetometer() {
    mag.read();
    MagnetometerXValue = mag.m.x;
    MagnetometerYValue = mag.m.y;
    MagnetometerZValue = mag.m.z;

    Serial.println("MAGNETOMETER READINGS");
    Serial.print("Magnetometer: X=");
    Serial.print(MagnetometerXValue);
    Serial.print(" Y=");
    Serial.print(MagnetometerYValue);
    Serial.print(" Z=");
    Serial.println(MagnetometerZValue);
}

void DataReading::ReadBarometer()
{
  pressure = baro.readPressureMillibars();
  temperature = baro.readTemperatureC();
}

void DataReading::CalculateHeight()
{

}

void DataReading::CalculateHeading() 
{
  float normAcc = sqrt(AccelXValue * AccelXValue + AccelYValue * AccelYValue + AccelZValue * AccelZValue);
  AccelXValue /= normAcc;
  AccelYValue /= normAcc;
  AccelZValue /= normAcc;

  MagnetometerPitch = asin(-AccelXValue);
  MagnetometerRoll = asin(AccelYValue / cos(MagnetometerPitch));

  MagnetometerXCalculated = (MagnetometerXValue * cos(MagnetometerPitch)) + (MagnetometerZValue * sin(MagnetometerPitch));
  MagnetometerYCalculated = (MagnetometerXValue * sin(MagnetometerRoll) * sin(MagnetometerPitch)) + (MagnetometerYValue * cos(MagnetometerRoll)) - (MagnetometerZValue * sin(MagnetometerRoll) * cos(MagnetometerPitch));

  UncalibratedHeading = atan2(MagnetometerYCalculated, MagnetometerXCalculated);

  UncalibratedHeading = UncalibratedHeading * 180 / M_PI;
  if (UncalibratedHeading < 0) 
  {
      UncalibratedHeading += 360;
  }

  Serial.print("Uncalibrated Heading:");
  Serial.println(UncalibratedHeading);
}