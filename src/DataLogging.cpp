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

        Serial.println("STATE,TITLE1(UNIT1),TITLE2(UNIT2),TITLE3(UNIT3)");

        for(;;){
            int State = 0;
            float value1 = 1.0;
            float value2 = 2.0;
            float value3 = 3.0;
            
            String dataString = "";

            for(int analogPin = 0; analogPin < 3; analogPin++){
                int sensor = analogRead(analogPin);
                String dataString = "";
    
                if(analogPin == 1 ){
                    if (sensor > value1){
                        State = 1;
                        dataString += String(State);
                dataString += ",";
                    }
                    else if (sensor > value2){
                        State = 2;
                        dataString += String(State);
                        dataString += ",";
                    }
                    else if (sensor > value3){
                        State = 3;
                        dataString += String(State);
                        dataString += ",";
                    }
                    else{
                        dataString += String(State);
                        dataString += ",";
                        continue;
                    }
                }

                dataString += String(sensor);

                if (analogPin < 2) {
                    dataString += ",";
                }
            }
            Serial.println(dataString);
        }
    }
    else{
        Serial.println("Error in opening file");
    }
}