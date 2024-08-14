#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "Card.h"
#include "SwTimer.h"
/*
#include "BMP.h"
*/

#define CHIPSELECT 10
static const arduino::String SEP = " < ";
static float Time;

arduino::String BMP_data[3];

void Card_Init(void) {

  SD.begin(CHIPSELECT);

  File dataFile = SD.open("aa00.txt", FILE_WRITE);       // < Start sequenc
  Time = millis();
  Time /= 1000;

  dataFile.println("BEGIN" +SEP +String(Time));     // < Writeing the start sequence
}

void Card_Run( ) { //TODO Data be

  static arduino::String Data_from_BMP[3];
  static unsigned long Cycle_from_SwTimer;

  File dataFile = SD.open("aa00.txt", FILE_WRITE);
  if (dataFile) {

    /* === start === */
    Time = millis();
    Time /= 1000;
    dataFile.println("START" +SEP +String(Time));

    Cycle_from_SwTimer = SwTimer_Get_Cycle();

    dataFile.println("Cycl=" + String());

    /* === BMP senzor === */

    BMP_data[3] = BMP_Get_Data();

    dataFile.println("Temp=" + BMP_data[0]);
    dataFile.println("Pres=" + BMP_data[1]);
    dataFile.println("Aalt=" + BMP_data[2]);
    /* === GPS === */



    /* === Other === */



    /* === end === */
    Time = millis();
    Time /= 1000;
    dataFile.println("END" +SEP +String(Time));

    dataFile.close();
  }
}

#undef CHIPSELECT
