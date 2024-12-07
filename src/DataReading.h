#include <Arduino.h>

class DataReading
{
private:
    const float ACCEL_SENSITIVITY = 0.061; // in mg/LSB, assuming ±2g full-scale range
    const uint32_t ITER_NO = 100;

    const uint32_t GPS_BAUD = 9600;

    //uint32_t altIter;
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
    float mGPSAltitude = 0.0;
    float mGPSVelocity = 0.0;
    float mLatitude = 0.0;
    float mLongitude = 0.0;
    uint32_t mNumberOfSatellites = 0;


public:
    DataReading(/* args */); 
    void Begin();
    void AltitudeCalibration();//this doesnt work, it crashes, fix
    void ReadAccelerometer();
    void ReadGPSStream();
    void GPSStreamToData();
    void ReadMagnetometer();
    void ReadBarometer();
    void CalculateHeading();
    float ReturnLatitude();
    float ReturnLongitude();
    uint32_t ReturnSatellitesConnected();
    float ReturnGPSAltitude();
    float ReturnGPSVelocity();
    float ReturnAccelerometerX();
    float ReturnAccelerometerY();
    float ReturnAccelerometerZ();
    float ReturnMagnetometerX();
    float ReturnMagnetometerY();
    float ReturnMagnetometerZ();
    float ReturnAltitude();
    float ReturnPressure();
    float ReturnTemperature();
};

