#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "globals.h"
#include "Card.h"
#include "SwTimer.h"

/* === Test Statement === */
#define TEST true

#define CHIPSELECT 10
static const arduino::String SEP = "=";

arduino::String CardTime(const unsigned long CONVERTER) {     // Give the time signo to the message (in seconds)
  float Time = millis();
  Time /= CONVERTER;
  return String(Time);
}

void Card_Init(void) {

  SD.begin(CHIPSELECT);

  File dataFile = SD.open("aa00.txt", FILE_WRITE);       // < Start sequenc
  dataFile.println("BEGIN" +SEP + CardTime(1000));     // < Writeing the start sequence

  if (TEST) Serial.println("BEGIN" +SEP + CardTime(1000));
}

void Card_Run(void) {

  File dataFile = SD.open("aa00.txt", FILE_WRITE);  // < Start sequenc
  if (dataFile) {

    dataFile.println("START" +SEP + CardTime(1000) );
    dataFile.println("Cycl" + SEP + String(SwTimer_Cycle) );
    dataFile.println("Temp" + SEP + BMP_Data[0] );
    dataFile.println("Pres" + SEP + BMP_Data[1] );
    dataFile.println("Aalt" + SEP + BMP_Data[2] );
    dataFile.println("END" + SEP + CardTime(1000) );
    dataFile.close();
  }

  if (TEST) {
    Serial.println("START" + SEP + CardTime(1000) );
    Serial.println("Cycl" + SEP + String(SwTimer_Cycle) );
    Serial.println("Temp" + SEP + BMP_Data[0] );
    Serial.println("Pres" + SEP + BMP_Data[1] );
    Serial.println("Aalt" + SEP + BMP_Data[2] );
    Serial.println("END__" + SEP + CardTime(1000) );
  }
}

#undef CHIPSELECT
#undef TEST
