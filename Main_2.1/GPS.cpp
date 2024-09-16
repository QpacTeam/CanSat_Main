#include <Arduino.h>
#include "GPS.h"
#include "globals.h"

UART GPS(8, 9);

static char ggaLine[128];

static char sign[5];
static bool rec = false;
static bool dollarSign = false;


static int signIndex = 0;
static unsigned int lineIndex = 0;

double GPS_Data[7];    /*0 1 3 6 7 8 10   ==>  time, latitude(N) longitude(E) Satelites-used HDOP MSL-altitude(M) Geoid-separation(M)*/

void GPS_Init(void) {
  GPS.begin(9600);
  delay(2000);  // < delay <<< 
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

      /* convert and store char data into double */
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
/*
  for (int j = 0; j < 7; j++) {   // <<<
    Serial.println(GPS_Data[j]);
  }
  Serial.println("");*/
}


void GPS_Run(void) {
  while (GPS.available() > 0){
    char ch = GPS.read();

    if (rec && ch == '\n') {

//      Serial.println(ggaLine);  // <<<
      GPS_parcer();
      
      for (int i = 0; i <= lineIndex; i++){
        ggaLine[i] = '0';
      }
      lineIndex = 0;
      rec = false;
    }

    if (rec){
      ggaLine[lineIndex] = ch;
      lineIndex++;
    }

    if (signIndex == 5){
      signIndex = 0;
      dollarSign = false;
      
      if (sign[0] == 'G' && sign[1] == 'P' && sign[2] == 'G' && sign[3] == 'G' && sign[4] == 'A') rec = true;
    }
    
    if (dollarSign){
      sign[signIndex] = ch;
      signIndex++;
    }

    if (ch == '$') dollarSign = true;
  }
}
