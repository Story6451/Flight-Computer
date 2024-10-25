#include <DataReading.h>
#include <LIS3MDL.h>
#include <LSM6.h>

LIS3MDL mag;
LSM6 imu;

DataReading::DataReading()
{
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
}

void DataReading::ReadMagnetometer()
{
    mag.read();
    MagnetometerXValue = mag.m.x;
    MagnetometerYValue = mag.m.y;
    MagnetometerXValue = mag.m.z;

    // Output raw x, y, z values for magnetometer
    Serial.println("MAGNETOMETER READINGS");
    Serial.print("Magnetometer: X=");
    Serial.print(MagnetometerXValue);
    Serial.print(" Y=");
    Serial.print(MagnetometerYValue);
    Serial.print(" Z=");
    Serial.println(MagnetometerXValue);
}


/*

atan(y/x) if x > 0
π/2 if x = 0 and y > 0
−π/2 if x = 0 and y < 0
atan(y/x) + π if x < 0 and y ≥ 0
atan(y/x) − π if x < 0 and y < 0


*/
