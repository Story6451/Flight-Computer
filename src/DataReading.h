#include <Arduino.h>
#include <LPS.h>

class DataReading
{
private:
    const uint32_t ITER_NO = 1000;
    uint32_t altIter;
    float pressure = 0.0; 
    float altitude = 0.0; 
    float temperature = 0.0;
    float altitudeOffset = 0.0;
    float MagnetometerXValue = 0.0;
    float MagnetometerYValue = 0.0;
    float MagnetometerZValue = 0.0;
    float AccelXValue = 0.0;
    float AccelYValue = 0.0;
    float AccelZValue = 0.0;
    float MagnetometerPitch = 0.0;
    float MagnetometerRoll = 0.0;
    float MagnetometerXCalculated = 0.0;
    float MagnetometerYCalculated = 0.0;
    float UncalibratedHeading = 0.0;
public:
    DataReading(/* args */); 
    void Begin();
    void AltitudeCalibration();//this doesnt work, it crashes, fix
    void ReadAccelerometer();
    void ReadMagnetometer();
    void ReadBarometer();
    void CalculateHeight();
    void CalculateHeading();
};

