/*
   EKF (Extended Kalman Filter) for altitude estimation
*/

#include "kalman.h"
#include <BasicLinearAlgebra.h>

using namespace BLA;

// Process Noise Uncertainty Matrix Q
BLA::Matrix<2, 2> Q = {0.075, 0,
                     0, 0.075};
//BLA::Matrix<2, 2> Q;

// BLA::Matrix<2, 2> Q = {pow(data.delta_t, 4) * 0.0175, pow(data.delta_t, 3) * 0.035f,
//                        pow(data.delta_t, 3) * 0.035f, data.delta_t *data.delta_t * 0.07f};

// Measurement Uncertainty Matrix R for the Barometer
BLA::Matrix<1, 1> R_Baro = {pow(0.07,2)}; //Standard Deivation = 0.15m

// System State Vector X
// Position
// Velocit
BLA::Matrix<2, 1> X = {0,
                       0};

// Estimate Uncertainty P
BLA::Matrix<2, 2> P;

// Identity Matrix I
BLA::Matrix<2, 2> I = {1, 0,
                       0, 1};

// Observation Matrix H
BLA::Matrix<1, 2> H_Baro = {1, 0};

// State Transition Matrix F
BLA::Matrix<2, 2> F;

// Output Vector
BLA::Matrix<1, 1> M_Baro;
// Kalman Gain
BLA::Matrix<2, 1> K_Baro;

// Control Matrix / input transition matrix G / B
BLA::Matrix<2, 1> G;
// Input Variable
BLA::Matrix<1, 1> U;

void EKF::initkalman()
{
    X = {0,
         0};

    P = {0, 0,
         0, 0};
}
void EKF::predict(float accel)
{
    currentTime = micros();
    delT = (currentTime - prevTime) / 1000000.0f;
    prevTime = currentTime;

    if (!isFirstStep)
    {
        // Dynamic model of the system pos = pos_0 + v_0 * delT + (accel*delT^2)/2
        //                             vel = v_0 + accel*delT
        F = {
            1, delT,
            0, 1};

        G = {0.5 * pow(delT,2),
             delT};

        U = {accel};

        //Q = {G * ~G * pow(0.1,2)}; //Standard Deivation = 0.1m

        X = F * X + G * U;
        P = F * P * ~F + Q;
    }
    isFirstStep = false;
}

void EKF::updateBaro(float altitude)
{
    M_Baro = {altitude};
    //L = H_Baro * P * ~H_Baro + R_Baro;
    K_Baro = P * ~H_Baro * Inverse((H_Baro * P * ~H_Baro + R_Baro));

    // X =X +K(M-HX)
    X = X + K_Baro * (M_Baro - H_Baro * X);
    // P = (I - KF)*P
    P = (I - K_Baro * H_Baro) * P * (~(I - K_Baro * H_Baro)) + K_Baro * R_Baro * ~K_Baro;

    altitude = X(0, 0);
}

// void EKF::updateGNSS(){}

float EKF::getKalmanPosition()
{
    return X(0, 0);
}

float EKF::getKalmanVelocity()
{
    return X(1, 0);
}

float EKF::getKalmanGain()
{
    return K_Baro(1, 0);
}