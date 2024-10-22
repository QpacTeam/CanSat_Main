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

float CardTime(unsigned long CONVERTER);   // < pre-call the function

void Card_Init(void) {
  #ifdef TEST    // < Test statement  <<<
    Serial.begin(9600);
    Serial.println("BEGIN" + SEP + CardTime(1000));
  #endif
  
  SD.begin(CHIPSELECT);
  File dataFile = SD.open(FILENAME, FILE_WRITE);       // < Start sequence
  if (dataFile) {
    dataFile.println("BEGIN" +SEP + CardTime(1000));     // < Writing the start sequence
    dataFile.close();
  }
}

void Card_Run(void) {
  double *pBMP_Data = BMP_GetData();
  float *pIMU_Data = IMU_GetData(); 
  double *pGPS_Data = GPS_GetData();

  File dataFile = SD.open(FILENAME, FILE_WRITE);  // < Start sequence
  
  if (dataFile) {
    dataFile.println("Star" + SEP + String(CardTime(1000)) ); // S
    //dataFile.println("Cycl" + SEP + String(SwTimer_Cycle) );  // C
    //dataFile.println("Miss" + SEP + String(missionState) );   // M
    dataFile.println("Temp" + SEP + String(pBMP_Data[0]) );    // T
    dataFile.println("Pres" + SEP + String(pBMP_Data[1]) );    // P
    dataFile.println("Aalt" + SEP + String(pBMP_Data[2]) );    // A

    dataFile.println("XAcc" + SEP + String(pIMU_Data[0]) );    // XA
    dataFile.println("YAcc" + SEP + String(pIMU_Data[1]) );    // YA
    dataFile.println("ZAcc" + SEP + String(pIMU_Data[2]) );    // ZA
    dataFile.println("XGry" + SEP + String(pIMU_Data[3]) );    // XG
    dataFile.println("YGry" + SEP + String(pIMU_Data[4]) );    // YG
    dataFile.println("ZGry" + SEP + String(pIMU_Data[5]) );    // ZG
    dataFile.println("Imut" + SEP + String(pIMU_Data[6]) );    // I

    dataFile.println("GPS0" + SEP + String(pGPS_Data[0]) );
    dataFile.println("GPS1" + SEP + String(pGPS_Data[1]) );
    dataFile.println("GPS2" + SEP + String(pGPS_Data[2]) );
    dataFile.println("GPS3" + SEP + String(pGPS_Data[3]) );
    dataFile.println("GPS4" + SEP + String(pGPS_Data[4]) );
    dataFile.println("GPS5" + SEP + String(pGPS_Data[5]) );
    dataFile.println("GPS6" + SEP + String(pGPS_Data[6]) );

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
    Serial.println("Temp" + SEP + String(pBMP_Data[0]) );    // T
    Serial.println("Pres" + SEP + String(pBMP_Data[1]) );    // P
    Serial.println("Aalt" + SEP + String(pBMP_Data[2]) );    // A

    Serial.println("XAcc" + SEP + String(pIMU_Data[0]) );    // XA
    Serial.println("YAcc" + SEP + String(pIMU_Data[1]) );    // YA
    Serial.println("ZAcc" + SEP + String(pIMU_Data[2]) );    // ZA
    Serial.println("XGry" + SEP + String(pIMU_Data[3]) );    // XG
    Serial.println("YGry" + SEP + String(pIMU_Data[4]) );    // YG
    Serial.println("ZGry" + SEP + String(pIMU_Data[5]) );    // ZG
    Serial.println("Imut" + SEP + String(pIMU_Data[6]) );    // I

    //Serial.println(String(Whole_GPS));

    Serial.println("GPS0" + SEP + String(pGPS_Data[0]) );
    Serial.println("GPS1" + SEP + String(pGPS_Data[1]) );
    Serial.println("GPS2" + SEP + String(pGPS_Data[2]) );
    Serial.println("GPS3" + SEP + String(pGPS_Data[3]) );
    Serial.println("GPS4" + SEP + String(pGPS_Data[4]) );
    Serial.println("GPS5" + SEP + String(pGPS_Data[5]) );
    Serial.println("GPS6" + SEP + String(pGPS_Data[6]) );

    Serial.println("Ends" + SEP + String(CardTime(1000)) ); // E
  #endif
}

float CardTime(unsigned long CONVERTER) {     // Give the time signo to the message (in seconds)
  float Time = millis();
  Time /= CONVERTER;
  return Time;
}

#undef TEST   // <<<
