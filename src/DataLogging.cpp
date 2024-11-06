#include <DataLogging.h>
#include <SD.h>

DataLogging::DataLogging()
{
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (true);
}

void DataLogging::LogData()
{
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if (dataFile) {
        for(;;){
            int State = 0;
            
            Serial.println("STATE,TITLE1(UNIT1),TITLE2(UNIT2),TITLE3(UNIT3)");
            String dataString = "";
            dataString += String(State);
            dataString += ",";

            for(int analogPin = 0; analogPin < 3; analogPin++){
                int sensor = analogRead(analogPin);
                dataString += String(sensor);
                if(analogpin == 1 )
                if (analogPin < 2) {
                    dataString += ",";
                }


            }
        }
    }
}