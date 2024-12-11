#include <Arduino.h>

class EKF
{
private:
    uint64_t mCurrentTime = 0;
    uint64_t mPrevTime = 0;
    float mDelT = 0.0f;

    bool mIsFirstStep = true;

public:
    EKF(){};
    void Initkalman();
    void Predict(float accel);
    void UpdateBaro(float altitude);
    //void updateGNSS();
    float GetKalmanPosition();
    float GetKalmanVelocity();
    float GetKalmanGain();
};
