#include <Arduino.h>
#include <LPS.h>

class DataReading
{
private:
    /* data */
    LPS ps;
    const int ITER_NO = 1000;
    int altIter;
    float pressure = 0.0, altitude = 0.0, temperature = 0.0, altitudeOffset = 0.0;
public:
    DataReading(/* args */); 
    void AltitudeCalibration();
    void PrintAltitude();
    void ReadMagnetometer();
};

