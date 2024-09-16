#include <Arduino.h>
#include "GPS.h"
#include "globals.h"

char sign[5];
bool dollarjel = false;
int signindex = 0;
char ggaline[128];
bool rec = false;
int lineindex = 0;

UART GPS(8, 9);

void GPS_Init() {
  GPS.begin(9600);
  delay(2000);
}


void GPS_Run(){
  
  while (GPS.available() > 0){

    char a = GPS.read();  //  < takes in one character  <<<

    if (rec && a == '\n') {      // 
      // TODO  SAVE SOMEWHERE GGALINE!!!
      Serial.println(ggaline);
      for (int i = 0; i <= lineindex; i++){
        ggaline[i] = '0';
      }
      lineindex = 0;
      rec = false;
    }

    if (rec){
      ggaline[lineindex] = a;
      lineindex++;
    }

    if (signindex == 5){
      signindex = 0;
      dollarjel = false;
      Serial.println(sign);
      if (sign[0] == 'G' && sign[1] == 'P' && sign[2] == 'G' && sign[3] == 'G' && sign[4] == 'A') {
        rec = true;
      }
    }

    if (dollarjel){
      sign[signindex] = a;
      signindex++;
    }

    if (a == '$'){
      dollarjel = true;
      Serial.println("dollár");
    }
  }
}

static void GPS_Save(){ // TODO this one saves the data
  
}
