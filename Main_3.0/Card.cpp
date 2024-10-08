#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "Card.h"
#include "BMP.h"
#include "GPS.h"
#include "IMU.h"

#define TEST

const unsigned int CHIPSELECT = 10;
const char FILENAME[9] = "aa00.txt";
const char GPS_SAVE_FILE[10] = "GPS01.txt";

const arduino::String SEP = "=";
arduino::String CardTime(const unsigned long CONVERTER);   // < pre-caal the function

void Card_Init(void) {

  #ifdef TEST    // < Test statement  <<<
    Serial.begin(9600);
    Serial.println("BEGIN" + SEP + CardTime(1000));
  #endif
  
  SD.begin(CHIPSELECT);
  File dataFile = SD.open(FILENAME, FILE_WRITE);       // < Start sequenc
  if (dataFile) {
    dataFile.println("BEGIN" +SEP + CardTime(1000));     // < Writeing the start sequence
    dataFile.close();
  }
}

void Card_Run(void) {

  File dataFile = SD.open(FILENAME, FILE_WRITE);  // < Start sequenc
  if (dataFile) {
    dataFile.println("Star" + SEP + String(CardTime(1000)) ); // S
    //dataFile.println("Cycl" + SEP + String(SwTimer_Cycle) );  // C
    //dataFile.println("Miss" + SEP + String(missionState) );   // M
    dataFile.println("Temp" + SEP + String(BMP_GetData()[0]) );    // T
    dataFile.println("Pres" + SEP + String(BMP_GetData()[1]) );    // P
    dataFile.println("Aalt" + SEP + String(BMP_GetData()[2]) );    // A

    dataFile.println("XAcc" + SEP + String(IMU_GetData()[0]) );    // XA
    dataFile.println("YAcc" + SEP + String(IMU_GetData()[1]) );    // YA
    dataFile.println("ZAcc" + SEP + String(IMU_GetData()[2]) );    // ZA
    dataFile.println("XGry" + SEP + String(IMU_GetData()[3]) );    // XG
    dataFile.println("YGry" + SEP + String(IMU_GetData()[4]) );    // YG
    dataFile.println("ZGry" + SEP + String(IMU_GetData()[5]) );    // ZG
    dataFile.println("Imut" + SEP + String(IMU_GetData()[6]) );    // I

    dataFile.println("GPS0" + SEP + String(GPS_GetData()[0]) );
    dataFile.println("GPS1" + SEP + String(GPS_GetData()[1]) );
    dataFile.println("GPS2" + SEP + String(GPS_GetData()[2]) );
    dataFile.println("GPS3" + SEP + String(GPS_GetData()[3]) );
    dataFile.println("GPS4" + SEP + String(GPS_GetData()[4]) );
    dataFile.println("GPS5" + SEP + String(GPS_GetData()[5]) );
    dataFile.println("GPS6" + SEP + String(GPS_GetData()[6]) );

    dataFile.println("Ends" + SEP + String(CardTime(1000)) ); // E
    dataFile.close(); 
  }

  // MADE BY IMRE
  /*File GPSFile = SD.open(GPS_SAVE_FILE, FILE_WRITE);  // < Start sequenc
  if (GPSFile) {
    GPSFile.println(String(Whole_GPS));
    GPSFile.close();
  }*/

  #ifdef TEST // < Test statement 
    Serial.println("Star" + SEP + String(CardTime(1000)) ); // S
    //Serial.println("Cycl" + SEP + String(SwTimer_Cycle) );  // C
    //Serial.println("Miss" + SEP + String(missionState) );   // M
    Serial.println("Temp" + SEP + String(BMP_GetData()[0]) );    // T
    Serial.println("Pres" + SEP + String(BMP_GetData()[1]) );    // P
    Serial.println("Aalt" + SEP + String(BMP_GetData()[2]) );    // A

    Serial.println("XAcc" + SEP + String(IMU_GetData()[0]) );    // XA
    Serial.println("YAcc" + SEP + String(IMU_GetData()[1]) );    // YA
    Serial.println("ZAcc" + SEP + String(IMU_GetData()[2]) );    // ZA
    Serial.println("XGry" + SEP + String(IMU_GetData()[3]) );    // XG
    Serial.println("YGry" + SEP + String(IMU_GetData()[4]) );    // YG
    Serial.println("ZGry" + SEP + String(IMU_GetData()[5]) );    // ZG
    Serial.println("Imut" + SEP + String(IMU_GetData()[6]) );    // I

    //Serial.println(String(Whole_GPS));

    Serial.println("GPS0" + SEP + String(GPS_GetData()[0]) );
    Serial.println("GPS1" + SEP + String(GPS_GetData()[1]) );
    Serial.println("GPS2" + SEP + String(GPS_GetData()[2]) );
    Serial.println("GPS3" + SEP + String(GPS_GetData()[3]) );
    Serial.println("GPS4" + SEP + String(GPS_GetData()[4]) );
    Serial.println("GPS5" + SEP + String(GPS_GetData()[5]) );
    Serial.println("GPS6" + SEP + String(GPS_GetData()[6]) );

    Serial.println("Ends" + SEP + String(CardTime(1000)) ); // E
  #endif
}

  arduino::String CardTime(const unsigned long CONVERTER) {     // Give the time signo to the message (in seconds)
  float Time = millis();
  Time /= CONVERTER;
  return String(Time);
}

#undef TEST   // <<<
