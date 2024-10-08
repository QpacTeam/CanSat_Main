#include <Arduino.h>
#include "GPS.h"
#include "globals.h"

UART GPS(8, 9);

static char ggaLine[128];
static unsigned int lineIndex = 0;

static bool dollarSign = false;   // < "It was a new line!" indicator
static char sign[5];              // < Holds the line indicator
static int signIndex = 0;

static bool rec = false;          // < Recording data if its the right line

char Whole_GPS[128];    // <<<
double GPS_Data[7];    /*0 1 3 6 7 8 10   ==>  time, latitude(N) longitude(E) Satelites-used HDOP MSL-altitude(M) Geoid-separation(M)*/

void GPS_Init(void) {
  GPS.begin(9600);
  delay(2000);  // < delay <<<

    /* THING */
  Whole_GPS[0] = '$';
  Whole_GPS[1] = 'G';
  Whole_GPS[2] = 'P';
  Whole_GPS[3] = 'G';
  Whole_GPS[4] = 'G';
  Whole_GPS[5] = 'A';
  Whole_GPS[6] = ',';
  
}

// sample:        
//        $GNGGA,143257.00,4712.82720,N,01933.15625,E,1,11,0.98,147.7,M,38.7,M,,*4E

static void GPS_parcer(void){
  
  unsigned int i = 0;
  unsigned int counter = 0;    // < Counts the comas
  unsigned int slot = 0;
  
  while (ggaLine[i] != '\n' && ggaLine[i] != '\r') {    // < loop trught the whol line until  end
    double num = 0;
    unsigned int point = 0;

    if (counter == 0 || counter == 1 || counter == 3 || counter == 6 || counter == 7 || counter == 8 || counter == 10) {  // < data needed

      /* convert and store char array data into double */
      while (ggaLine[i] != ',') {
        if (ggaLine[i] == '.') {
          point++;
        }
        else {
          if (point > 0) point++;
          num += int(ggaLine[i]) -48;
          num *= 10;
        }
        i++;
      }
      for (point; point > 1; point--) num /= 10;  // correcting the value
      num /= 10;
      GPS_Data[slot] = num; // < store converted data
      slot++;
      
    } 
    else {
      while (ggaLine[i] != ',') i ++;   // < skipp unneeded data
    }
    
    i++;
    counter++;
  }
}


void GPS_Run(void) {
  
  while (GPS.available() > 0){    // Read data constantaniusly from the GPS serial buffer
    char ch = GPS.read();

    if (rec && ch == '\n') {

      GPS_parcer();   // Parce the data
      
      for (unsigned int i =7; i < 128; i++) {    // Emptying Whole_GPS array
        Whole_GPS[i] = '\0';
      }
      for (unsigned int j = 0; j <= lineIndex; j++) {  // Copying ggaLine array into Whole_GPS array
        Whole_GPS[j + 7] = ggaLine[j];
      }
      
      for (unsigned int k = 0; k <= lineIndex; k++){   // Emptying ggaLine array
        ggaLine[k] = '0';
      }
      lineIndex = 0;
      rec = false;
    }

    if (rec){
      ggaLine[lineIndex] = ch;    // Recording the line
      lineIndex++;
    }

    if (signIndex == 5){
      signIndex = 0;        // Identify the linebegin
      dollarSign = false;
      
      if (sign[0] == 'G' && sign[1] == 'P' && sign[2] == 'G' && sign[3] == 'G' && sign[4] == 'A') rec = true;   // Starts saving tle line if it's the <GPGGA>
    }
    
    if (dollarSign){
      sign[signIndex] = ch;   // Recording the linebeginn
      signIndex++;
    }

    if (ch == '$') dollarSign = true;     // < Begin recording if it's new line
  }
}
