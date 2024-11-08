#include <DataReading.h>
#include <LIS3MDL.h>
#include <LSM6.h>
#include <LPS.h>

LPS lps;
LIS3MDL mag;
LSM6 imu;


DataReading::DataReading()
{
  if (!ps.init())
  {
    Serial.println("Failed to autodetect pressure sensor!");
    while (1);
  }
  ps.enableDefault();

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

  AltitudeCalibration();

  Serial.println("Calibration complete");
    
}

void DataReading::AltitudeCalibration()
{
  float altitudeSum = 0;

  for (altIter = 0; altIter < ITER_NO; altIter++)
  {
    pressure = ps.readPressureMillibars();
    altitude = ps.pressureToAltitudeMeters(pressure);
    altitudeSum += altitude;
  }

  altitudeOffset = altitudeSum / ITER_NO;
}

void DataReading::ReadAccelerometer()
{
  AccelXValue = imu.a.x;
  AccelYValue = imu.a.y;
  AccelZValue = imu.a.z;
}
void DataReading::ReadMagnetometer()
{
  mag.read();
  MagnetometerXValue = mag.m.x;
  MagnetometerYValue = mag.m.y;
  MagnetometerZValue = mag.m.z;
  // Output raw x, y, z values for magnetometer
  Serial.println("MAGNETOMETER READINGS");
  Serial.print("Magnetometer: X=");
  Serial.print(MagnetometerXValue);
  Serial.print(" Y=");
  Serial.print(MagnetometerYValue);
  Serial.print(" Z=");
  Serial.println(MagnetometerZValue);
}

void DataReading::CalculateHeading()
{
  MagnetometerPitch = atan(AccelXValue / sqrt(pow(AccelYValue,2)+pow(AccelZValue,2)));
  MagnetometerRoll = atan(-AccelYValue / AccelZValue);
  MagnetometerXCalculated = (MagnetometerXValue * cos(MagnetometerPitch)) + (MagnetometerZValue * sin(MagnetometerPitch));
  MagnetometerYCalculated = ((MagnetometerXValue * sin(MagnetometerPitch) * sin(MagnetometerRoll)) + (MagnetometerYValue * cos(MagnetometerRoll)) - (MagnetometerZValue * sin(MagnetometerRoll) * cos(MagnetometerPitch)));
  UncalibratedHeading = atan(MagnetometerYCalculated / MagnetometerXCalculated);
  Serial.print("Uncalibrated Heading:");
  Serial.println(UncalibratedHeading);
}

void DataReading::ReadBarometer()
{
  temperature = lps.readTemperatureC();
  pressure = lps.readPressureMillibars();
  altitude = lps.pressureToAltitudeMeters(pressure);
}
    