#include <Arduino.h>
<<<<<<< HEAD
#include <LPS.h>
=======
>>>>>>> 361a33b705f11f4376cb86d935df70aad5e24ffd

class DataReading
{
private:
    /* data */
<<<<<<< HEAD
    LPS ps;
    const int ITER_NO = 1000;
    int altIter;
    float pressure = 0.0, altitude = 0.0, temperature = 0.0, altitudeOffset = 0.0;
public:
    DataReading(/* args */); 
    void altitudeCalibration();
=======
    /*Magnetometer reading in gauss 1T = 1E4 GAUSS*/
    double MagnetometerXValue;
    double MagnetometerYValue;
    double MagnetometerZValue;
public:
    DataReading(/* args */);
    void ReadMagnetometer();
>>>>>>> 361a33b705f11f4376cb86d935df70aad5e24ffd
};

