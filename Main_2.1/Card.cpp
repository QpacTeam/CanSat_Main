#include <cstdio>   // < WTF <<<
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "globals.h"
#include "Card.h"

/* === Test Statement === */
#define TEST true

#define CHIPSELECT 10
#define FILE "aa00.txt"   // < Itt lehet gond   <<<

static const arduino::String SEP = "=";

static arduino::String CardTime(const unsigned long CONVERTER);   // < pre-caal the function

void Card_Init(void) {

  SD.begin(CHIPSELECT);
  File dataFile = SD.open(FILE, FILE_WRITE);       // < Start sequenc
  dataFile.println("BEGIN" +SEP + CardTime(1000));     // < Writeing the start sequence
  dataFile.close();

  if (TEST) Serial.println("BEGIN" +SEP + CardTime(1000));
}

void Card_Run(void) {

  File dataFile = SD.open(FILE, FILE_WRITE);  // < Start sequenc
  if (dataFile) {
    dataFile.println("Star" + SEP + String(CardTime(1000)) ); // S
    dataFile.println("Cycl" + SEP + String(SwTimer_Cycle) ); // C
    dataFile.println("Miss" + SEP + String(missionState) ); // M
    dataFile.println("Temp" + SEP + String(BMP_Data[0]) ); // T
    dataFile.println("Pres" + SEP + String(BMP_Data[1]) ); // P
    dataFile.println("Aalt" + SEP + String(BMP_Data[2]) ); // A

    dataFile.println("XAcc" + SEP + String(IMU_Data[0]) ); // XA
    dataFile.println("YAcc" + SEP + String(IMU_Data[1]) ); // YA
    dataFile.println("ZAcc" + SEP + String(IMU_Data[2]) ); // ZA
    dataFile.println("XGry" + SEP + String(IMU_Data[3]) ); // XG
    dataFile.println("YGry" + SEP + String(IMU_Data[4]) ); // YG
    dataFile.println("ZGry" + SEP + String(IMU_Data[5]) ); // ZG
    dataFile.println("Imut" + SEP + String(IMU_Data[6]) ); // I

    dataFile.println("Ends" + SEP + String(CardTime(1000)) ); // E
    dataFile.close();
  }

  if (TEST) {     // < Test statement <<<
    Serial.println("Star" + SEP + String(CardTime(1000)) ); //S
    Serial.println("Cycl" + SEP + String(SwTimer_Cycle) ); // C
    Serial.println("Miss" + SEP + String(missionState) ); // M
    Serial.println("Temp" + SEP + String(BMP_Data[0]) ); // T
    Serial.println("Pres" + SEP + String(BMP_Data[1]) ); // P
    Serial.println("Aalt" + SEP + String(BMP_Data[2]) ); // A

    Serial.println("XAcc" + SEP + String(IMU_Data[0]) ); // XA
    Serial.println("YAcc" + SEP + String(IMU_Data[1]) ); // YA
    Serial.println("ZAcc" + SEP + String(IMU_Data[2]) ); // ZA
    Serial.println("XGry" + SEP + String(IMU_Data[3]) ); // XG
    Serial.println("YGry" + SEP + String(IMU_Data[4]) ); // YG
    Serial.println("ZGry" + SEP + String(IMU_Data[5]) ); // ZG
    Serial.println("Imut" + SEP + String(IMU_Data[6]) ); // I

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
