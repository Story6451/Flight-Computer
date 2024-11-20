#ifndef KALMAN
#define KALMAN

//#include <config.h>
//#include <global.h>
//#include <data.h>

class EKF
{

public:
    EKF(){};
    void initkalman();
    void predict(float accel);
    void updateBaro(float altitude);
    //void updateGNSS();

    float getKalmanPosition();
    float getKalmanVelocity();
    float getKalmanGain();



private:
    unsigned long currentTime = 0;
    unsigned long prevTime = 0;
    float delT = 0.0f;

    bool isFirstStep = true;
};

#endif /* KALMAN */
