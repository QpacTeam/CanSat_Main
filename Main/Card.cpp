#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "Card.h"


#define CHIPSELECT 10

void SD_Init(void) {

  SD.begin(CHIPSELECT);
}

void SD_run(int Typ_SD, const char* Data_SD) {

  File dataFile = SD.open("aa00.txt", FILE_WRITE);

  if (dataFile) {
    switch (Typ_SD) {
      case 0:
        {  // Pressure and teperature T
          dataFile.print("T;");
          dataFile.println(Data_SD);
          break;
        }
      case 1:
        {  // GPS data G
          dataFile.print("G;");
          dataFile.println(Data_SD);
          break;
        }
      case 2:
        { // IMU I
          dataFile.print("I;");
          dataFile.println(Data_SD);
          break;
        }
      default:
        { // Unsigned U
          dataFile.print("U;");
          dataFile.println(Data_SD);
          break;
        }
    }
  }
}

#undef CHIPSELECT
