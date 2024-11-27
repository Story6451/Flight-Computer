
#include <DataLogging.h>
#include <SD.h>

#include "DataReading.cpp"

int milli = 0;

DataLogging::DataLogging()
{
  Serial.print("Initializing SD card...");

  if (!SD.begin(mChipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (true);
  }
}
void DataLogging::LogData(){ 

  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  dataFile.println("State,pressure,altitude,temperature,altitudeOffset,MagnetometerXValue,MagnetometerYValue,MagnetometerZValue,AccelXValue,AccelYValue,AccelZValue,MagnetometerPitch,MagnetometerRoll,MagnetometerXCalculated,MagnetometerYCalculated,UncalibratedHeading");



  if (dataFile) {

    Serial.println();

    if((millis() - mLastTime) > mLogDelay) 
    {

      dataFile.print(String(mState));
      dataFile.print(",");
      dataFile.print(String(mPressure));
      dataFile.print(",");
      dataFile.print(String(mAltitude));
      dataFile.print(",");
      dataFile.print(String(mTemperature));
      dataFile.print(",");
      dataFile.print(String(mAltitudeOffset));
      dataFile.print(",");
      dataFile.print(String(mMagnetometerXValue));
      dataFile.print(",");
      dataFile.print(String(mMagnetometerYValue));
      dataFile.print(",");
      dataFile.print(String(mMagnetometerZValue));
      dataFile.print(",");
      dataFile.print(String(mAccelXValue));
      dataFile.print(",");
      dataFile.print(String(mAccelYValue));
      dataFile.print(",");
      dataFile.print(String(mAccelZValue));
      dataFile.print(",");
      dataFile.print(String(mMagnetometerPitch));
      dataFile.print(",");
      dataFile.print(String(mMagnetometerRoll));
      dataFile.print(",");
      dataFile.print(String(mMagnetometerXCalculated));
      dataFile.print(",");
      dataFile.print(String(mMagnetometerYCalculated));
      dataFile.print(",");
      dataFile.println(String(mUncalibratedHeading));

      mLastTime = millis();      

    }
    else{
      dataFile.close();
    }
            
  }
  else{
    Serial.println("Error in opening the file");
  }
}