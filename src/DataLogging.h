#include <Arduino.h>

class DataLogging
{
private:
    /* data */
    const uint8_t mChipSelect = 10;
    uint64_t mLastTime = 0;
    uint16_t mLogDelay = 1000;
    uint8_t mState ;
    float mPressure ; 
    float mAltitude ; 
    float mTemperature ;
    float mAltitudeOffset ;
    float mMagnetometerXValue ;
    float mMagnetometerYValue ;
    float mMagnetometerZValue ;
    float mAccelXValue ;
    float mAccelYValue ;
    float mAccelZValue ;
    float mMagnetometerPitch ;
    float mMagnetometerRoll ;
    float mMagnetometerXCalculated ;
    float mMagnetometerYCalculated ;
    float mUncalibratedHeading ;
    
public:
    DataLogging(/* args */);
    void Begin();
    void LogData();
};

