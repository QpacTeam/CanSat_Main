#include <Arduino.h>
#include "GPS.h"

#define whole_line 0

const unsigned int size = 7;

UART GPS(8, 9);

#if whole_line == 1
  char Whole_GPS[128] = "GPGGA";    // <<<
#endif

void GPS_parcer(void);

double GPS_Data[size];    /*0 1 3 6 7 8 10   ==>  time, latitude(N) longitude(E) Satelites-used HDOP MSL-altitude(M) Geoid-separation(M)*/

char ggaLine[128];
unsigned int lineIndex = 0;

bool dollarSign = false;   // < "It was a new line!" indicator
char sign[5];              // < Holds the line indicator
int signIndex = 0;

bool rec = false;          // < Recording data if its the right line

                            // sample:        
                            //        $GNGGA,143257.00,4712.82720,N,01933.15625,E,1,11,0.98,147.7,M,38.7,M,,*4E

void GPS_Init(void) {
  GPS.begin(9600);
  delay(2000);  // < delay <<<  
}

void GPS_Run(void) {
  unsigned int max = 10;
  while (max > 0 && GPS.available() > 0){    // Read data constantaniusly from the GPS serial buffer
    max--;
    
    char ch = GPS.read();

    if (rec && ch == '\n') {

      GPS_parcer();   // Parce the data

      #if whole_line == 1
        for (unsigned int i =7; i < 128; i++) {    // Emptying Whole_GPS array
          Whole_GPS[i] = '\0';
        }
        for (unsigned int j = 0; j <= lineIndex; j++) {  // Copying ggaLine array into Whole_GPS array
          Whole_GPS[j + 7] = ggaLine[j];
        }
      #endif
      
      for (unsigned int k = 0; k < lineIndex; k++){   // Emptying ggaLine array
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

double* GPS_GetData(void) {
  return GPS_Data;
}
//unsigned int GPS_GetDataSize(void) return size;


void GPS_parcer(void){
  
  unsigned int i = 0;
  unsigned int counter = 0;    // < Counts the comas
  unsigned int slot = 0;
  
  while (ggaLine[i] != '\n' && ggaLine[i] != '\r') {    // < loop though the whole line until the end
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

#undef whole_line
