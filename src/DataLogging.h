#include <Arduino.h>

class DataLogging
{
private:
    /* data */
    const int chipSelect = 10;
    
public:
    DataLogging(/* args */);
    void Begin();
    void LogData();
};

