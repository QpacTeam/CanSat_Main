#include <Arduino.h>
#include <cstdio>   // < WTF <<<
#include <SD.h>
#include <SPI.h>
#include "globals.h"
#include "Card.h"

/* === Test Statement === */
#define TEST true   // TODO remove once

#define CHIPSELECT 10
#define FILE "aa00.txt"   // < Itt lehet gond   <<<

static const arduino::String SEP = "=";

static arduino::String CardTime(const unsigned long CONVERTER);   // < pre-caal the function

void Card_Init(void) {

  if (TEST) {  // remove <<<
    Serial.begin(9600);
    Serial.println("BEGIN" +SEP + CardTime(1000));    // < Test statement  <<<
  }
  SD.begin(CHIPSELECT);
  File dataFile = SD.open(FILE, FILE_WRITE);       // < Start sequenc
  if (dataFile) {
    dataFile.println("BEGIN" +SEP + CardTime(1000));     // < Writeing the start sequence
    dataFile.close();
  }
}

void Card_Run(void) {

  File dataFile = SD.open(FILE, FILE_WRITE);  // < Start sequenc
  if (dataFile) {
    dataFile.println("Star" + SEP + String(CardTime(1000)) ); // S
    dataFile.println("Cycl" + SEP + String(SwTimer_Cycle) );  // C
    dataFile.println("Miss" + SEP + String(missionState) );   // M
    dataFile.println("Temp" + SEP + String(BMP_Data[0]) );    // T
    dataFile.println("Pres" + SEP + String(BMP_Data[1]) );    // P
    dataFile.println("Aalt" + SEP + String(BMP_Data[2]) );    // A

    dataFile.println("XAcc" + SEP + String(IMU_Data[0]) );    // XA
    dataFile.println("YAcc" + SEP + String(IMU_Data[1]) );    // YA
    dataFile.println("ZAcc" + SEP + String(IMU_Data[2]) );    // ZA
    dataFile.println("XGry" + SEP + String(IMU_Data[3]) );    // XG
    dataFile.println("YGry" + SEP + String(IMU_Data[4]) );    // YG
    dataFile.println("ZGry" + SEP + String(IMU_Data[5]) );    // ZG
    dataFile.println("Imut" + SEP + String(IMU_Data[6]) );    // I

    dataFile.println("GPS0" + SEP + String(GPS_Data[0]) );
    dataFile.println("GPS1" + SEP + String(GPS_Data[1]) );
    dataFile.println("GPS2" + SEP + String(GPS_Data[2]) );
    dataFile.println("GPS3" + SEP + String(GPS_Data[3]) );
    dataFile.println("GPS4" + SEP + String(GPS_Data[4]) );
    dataFile.println("GPS5" + SEP + String(GPS_Data[5]) );
    dataFile.println("GPS6" + SEP + String(GPS_Data[6]) );

    dataFile.println("Ends" + SEP + String(CardTime(1000)) ); // E
    dataFile.close(); 
  }

  // MADE BY IMRE
  File GPSFile = SD.open("GPS00", FILE_WRITE);  // < Start sequenc
  if (GPSFile) {
    GPSFile.println(String(Whole_GPS));  // <<<
    GPSFile.close();
  }

  if (TEST) {     // Test statement <<<
    Serial.println("Star" + SEP + String(CardTime(1000)) ); // S
    Serial.println("Cycl" + SEP + String(SwTimer_Cycle) );  // C
    Serial.println("Miss" + SEP + String(missionState) );   // M
    Serial.println("Temp" + SEP + String(BMP_Data[0]) );    // T
    Serial.println("Pres" + SEP + String(BMP_Data[1]) );    // P
    Serial.println("Aalt" + SEP + String(BMP_Data[2]) );    // A

    Serial.println("XAcc" + SEP + String(IMU_Data[0]) );    // XA
    Serial.println("YAcc" + SEP + String(IMU_Data[1]) );    // YA
    Serial.println("ZAcc" + SEP + String(IMU_Data[2]) );    // ZA
    Serial.println("XGry" + SEP + String(IMU_Data[3]) );    // XG
    Serial.println("YGry" + SEP + String(IMU_Data[4]) );    // YG
    Serial.println("ZGry" + SEP + String(IMU_Data[5]) );    // ZG
    Serial.println("Imut" + SEP + String(IMU_Data[6]) );    // I

    Serial.println(String(Whole_GPS));

    Serial.println("GPS0" + SEP + String(GPS_Data[0]) );
    Serial.println("GPS1" + SEP + String(GPS_Data[1]) );
    Serial.println("GPS2" + SEP + String(GPS_Data[2]) );
    Serial.println("GPS3" + SEP + String(GPS_Data[3]) );
    Serial.println("GPS4" + SEP + String(GPS_Data[4]) );
    Serial.println("GPS5" + SEP + String(GPS_Data[5]) );
    Serial.println("GPS6" + SEP + String(GPS_Data[6]) );

    Serial.println("Ends" + SEP + String(CardTime(1000)) ); // E 
  }
}

static arduino::String CardTime(const unsigned long CONVERTER) {     // Give the time signo to the message (in seconds)
  float Time = millis();
  Time /= CONVERTER;
  return String(Time);
}

#undef TEST   // <<<

#undef CHIPSELECT
#undef FILE
