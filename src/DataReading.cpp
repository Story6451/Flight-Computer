#include <DataReading.h>


DataReading::DataReading()
{
  if (!ps.init())
  {
    Serial.println("Failed to autodetect pressure sensor!");
    while (1);
  }

  ps.enableDefault();

  altitudeCalibration();

  Serial.println("Calibration complete");
    
}

void DataReading::altitudeCalibration()
{
    float altitudeSum = 0;

  for (altIter = 0; altIter < ITER_NO; altIter++){
    pressure = ps.readPressureMillibars();
    altitude = ps.pressureToAltitudeMeters(pressure);
    altitudeSum += altitude;
  }

  altitudeOffset = altitudeSum / ITER_NO;
}