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
Calibration values; the default values of +/-32767 for each axis
lead to an assumed magnetometer bias of 0. Use the Calibrate example
program to determine appropriate values for your particular unit.
*/
//LIS3MDL::vector<int16_t> m_min = {-32767, -32767, -32767};
//LIS3MDL::vector<int16_t> m_max = {+32767, +32767, +32767};

void setup() {



}

void loop() {


}