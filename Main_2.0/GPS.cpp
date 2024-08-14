#include <Arduino.h>
#include "SwTimer.h"
#include "GPS.h"

#define SWTIMER_CH_GPS 2
#define MAX_DATA 4

UART GPS(4, 5, NC, NC);

static arduino::String GPS_raw_Data = "";
arduino::String GPS_final_Data[MAX_DATA];

void GPS_Init(void) {

  GPS.begin(9600);
  while (!GPS) {
    ;
  }

  arduino::String GPS_raw_Data = "";
}

void GPS_Run(void) {

  static arduino::String buffer = "";
  unsigned int slot = 0;
  unsigned int counter = 0;
  
  while (GPS.available() == 0) {}   // < Wait until the data is available
  
  GPS_raw_Data = GPS.readString();   // < Read the data from the GPS
  GPS_raw_Data.trim();     // < Remove The whitespaces and the /n /r on lineend

  //TODO test needed (I hope it works...)

  for (unsigned int i =1; i <= (GPS_raw_Data.length()-4); i++ ) {
    if (GPS_raw_Data.charAt(i) == '$') {
      counter = 5;
      if (i == 1) {}
      else {
        GPS_final_Data[slot] = buffer;
        slot++;
      }
    }
    else {
      if (counter == 0 ) buffer += String(GPS_raw_Data.charAt(i));
      else counter--;
    }
    if (slot == MAX_DATA) {
      break;
    }
  }
  GPS_final_Data[slot] = buffer;
}

arduino::String GPS_Get_Data(void) {
  return GPS_final_Data[MAX_DATA];
}

#undef SWTIMER_CH_GPS
