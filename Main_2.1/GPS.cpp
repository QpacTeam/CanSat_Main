#include "GPS.h"
#include "globals.h"

#define TER '\n'

UART GPS(9, 8);

void GPS_Init(void) {
  GPS.begin(9600);
  delay(2000);  // < delay <<< 
}

static arduino::String parcer(arduino::String) {
  ;
}

void GPS_Run(void) {
  if (GPS.avilable() > 0) {
    GPS.readStringUntil(TER);
    GPS.readStringUntil(TER);
    arduino::String raw = GPS.readStringUntil(TER);
    parcer(raw);
  }
}

#undef TER
