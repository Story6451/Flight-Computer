#include <Arduino.h>

class DataReading
{
private:
    /* data */
    /*Magnetometer reading in gauss 1T = 1E4 GAUSS*/
    double MagnetometerXValue;
    double MagnetometerYValue;
    double MagnetometerZValue;
public:
    DataReading(/* args */);
    void ReadMagnetometer();
};

