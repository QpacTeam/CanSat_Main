#include "Card.h"

String GPS = "$GNGGA,190202.00,4728.76713,N,01905.24027,E,1,05,8.29,141.8,M,39.3,M,,*4A";
char x;
int lat0;
int lat1;
String latitude;
String longitude;
String altitude;
String ido_ev;
String ido_honap;
String ido_nap;
String ido_ora;
String ido_min;
String ido_sec;
String speed; //horizontal
String irany;//measured heading

int alma;

void setup(void) {
  Serial1.begin(9600);
  Serial.begin(9600);
  //SD_Init();
}

void loop(void) {

  if (Serial1.available() > 0) {
    x = Serial1.read();
    //Serial.print(x);
    GPS.concat(x);//A bejővő adat hozzáírása a nagy változóhoz ami soronként veszi be a gps adatot
    if (x == '\n') {//Azért if mert a switch case nem csak "Any integer data type here is also allowed" így egyszerűbb
      //SD_run("VV19.txt", GPS);
      if (GPS.substring(1,6) == "GNGLL"){//$GNGLL,4728.76713,N,01905.24027,E,190202.00,A,A*7C
      }
      else if (GPS.substring(1,6) == "GNRMC") { //$GNRMC,190202.00,A,4728.76713,N,01905.24027,E,1.069,,160524,,,A*6F
      }
      else if (GPS.substring(1,6) == "GNGGA") {//$GNGGA,190202.00,4728.76713,N,01905.24027,E,1,05,8.29,141.8,M,39.3,M,,*4A
        Serial.println(GPS.indexOf(""));
      }
      else if (GPS.substring(1,6) == "GNVTG") {//$GNVTG,142.83,T,,M,32.919,N,60.967,K,A*21
      }
      GPS.remove(0,GPS.length()); //üríti a változót a következő sorhoz
    }
  }
}