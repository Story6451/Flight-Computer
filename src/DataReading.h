#include <Arduino.h>
#include <LPS.h>

class DataReading
{
private:
    const uint32_t ITER_NO = 100;
    uint32_t altIter;
    float mPressure = 0.0; 
    float mGroundPressure = 0.0;
    float mAltitude = 0.0; 
    float mTemperature = 0.0;
    float mAltitudeOffset = 0.0;
    float mMagnetometerXValue = 0.0;
    float mMagnetometerYValue = 0.0;
    float mMagnetometerZValue = 0.0;
    float mAccelXValue = 0.0;
    float mAccelYValue = 0.0;
    float mAccelZValue = 0.0;
    float mMagnetometerPitch = 0.0;
    float mMagnetometerRoll = 0.0;
    float mMagnetometerXCalculated = 0.0;
    float mMagnetometerYCalculated = 0.0;
    float mUncalibratedHeading = 0.0;

    static const float ACCEL_SENSITIVITY = 0.061; // in mg/LSB, assuming ±2g full-scale range
public:
    DataReading(/* args */); 
    void Begin();
    void AltitudeCalibration();//this doesnt work, it crashes, fix
    void ReadAccelerometer();
    float ReturnAccelerometerX();
    float ReturnAccelerometerY();
    float ReturnAccelerometerZ();
    float ReturnMagnetometerX();
    float ReturnMagnetometerY();
    float ReturnMagnetometerZ();
    float ReturnAltitude();
    float ReturnPressure();
    float ReturnTemperature();
    void ReadMagnetometer();
    void ReadBarometer();
    void CalculateHeading();
};

