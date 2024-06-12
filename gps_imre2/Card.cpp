#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "Card.h"


#define CHIPSELECT 10

void SD_Init(void) {

  SD.begin(CHIPSELECT);
}

void SD_run(String File_SD, String Data_SD) {
  File dataFile = SD.open(File_SD, FILE_WRITE);
  if (dataFile) {
    dataFile.print(Data_SD);
    Serial.print(Data_SD);
    dataFile.close();
  }
}

#undef CHIPSELECT