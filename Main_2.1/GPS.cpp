#include <Arduino.h>
#include "GPS.h"
#include "globals.h"

// TODO finish <<<

#define L_END '\n'

UART GPS(8, 9);

void GPS_Init(void) {
  GPS.begin(9600);
  delay(2000);  // < delay <<< 
}

// sample:        
//        $GNGGA,143257.00,4712.82720,N,01933.15625,E,1,11,0.98,147.7,M,38.7,M,,*4E

static void parSender(ardudino::String raw) {
  
  static unsigned long Lg = raw.length();
  static unsigned long coma = 0;
  // data to save from the raw string:
  static unsigned long neede[] = {1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1};

  if (raw.charAt(3) != 'G' && raw.charAt(4) != 'G' && raw.charAt != 'A') {      // << TODO finish
    // add error to the error array
    return;
  }

  for (unsigned int i =7; i < Lg; i++) {
    
  }
}arduino::String

void GPS_Run(void) {
  if (GPS.avilable() > 0) {
    GPS.readStringUntil(L_END);   // < Skipp the 1th line 
    GPS.readStringUntil(L_END);   // < Skipp the 2th line
    arduino::String Raw = GPS.readStringUntil(L_END);   // < Save the 3th line --> GGA data
    parcer(RAw);
    GPS.readString(); // < Clear the buffer
  }
}

#undef L_END
