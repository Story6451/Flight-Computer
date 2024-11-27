#include <Arduino.h>

class EKF
{
private:
    uint64_t currentTime = 0;
    uint64_t prevTime = 0;
    float delT = 0.0f;

    bool isFirstStep = true;

public:
    EKF(){};
    void initkalman();
    void predict(float accel);
    void updateBaro(float altitude);
    //void updateGNSS();
    float getKalmanPosition();
    float getKalmanVelocity();
    float getKalmanGain();
};
