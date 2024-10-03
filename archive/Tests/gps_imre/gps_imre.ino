#include "Card.h"

String GPS = "";
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

void setup(void) {
  Serial1.begin(9600);
  //Serial.begin(9600);
  SD_Init();

}

void loop(void) {

  if (Serial1.available() > 0) {
    x = Serial1.read();
    //Serial.print(x);
    GPS.concat(x);//A bejővő adat hozzáírása a nagy változóhoz ami soronként veszi be a gps adatot
    if (x == '\n') {//Azért if mert a switch case nem csak "Any integer data type here is also allowed" így egyszerűbb
      SD_run("VV19.txt", GPS);
      if (GPS.substring(1,6) == "GNGLL"){//$GNGLL,4728.76713,N,01905.24027,E,190202.00,A,A*7C
        lat0 = GPS.substring(7,9).toInt(); //A lat0 és a lat1 a gps adatát ami fokokban van megadva átalakítja egy tizedestörté
        lat1 = GPS.substring(9,11).toInt()*10000000*5/3+ GPS.substring(12,17).toInt()*100*5/3;
        latitude = GPS.substring(7,11)+GPS.substring(12,17);//a gps nyers adata lorának készen
        if (GPS.charAt(32) == 'N') {//A féltek megállapítása (nálunk ez akár elhanygolható)
          latitude += "0"; //N = 0 = North
        }
        else {
          longitude += "1"; //S = 1 = South
        }
        latitude = String(latitude.toInt());
        longitude = GPS.substring(20,25)+GPS.substring(26,31);//a gps nyers adata lorának készen
        if (GPS.charAt(32) == 'E') {//a féltek megállapítása (nálunk ez akár elhanygolható)
          longitude += "0"; //E = 0 = East
        }
        else {
          longitude += "1";//W = 1 = West
        }
        longitude = String(longitude.toInt());
        //Serial.println("latitude "+latitude+" longitude "+ longitude);
        SD_run("VV19.txt", "latitude "+latitude+" longitude "+ longitude+"\n");
      }
      else if (GPS.substring(1,6) == "GNRMC") { //$GNRMC,190202.00,A,4728.76713,N,01905.24027,E,1.069,,160524,,,A*6F

        ido_ora = GPS.substring(7,9);
        ido_min = GPS.substring(9,11);
        ido_sec = GPS.substring(11,13);
        Serial.println(GPS.length());
        if (GPS.length() == 66) {
          ido_nap = GPS.substring(53,55);
          ido_honap = GPS.substring(55,57);
          ido_ev = GPS.substring(57,59);
        }
        else if (GPS.length() == 75) {
          ido_nap = GPS.substring();
          ido_honap = GPS.substring(55,57);
          ido_ev = GPS.substring(57,59);
        }
        SD_run("VV19.txt", "időő"+ido_ev+"\n");//+ido_honap+ido_nap+ido_ora+ido_min+ido_sec+"\n");
        
      }
      else if (GPS.substring(1,6) == "GNGGA") {//$GNGGA,190202.00,4728.76713,N,01905.24027,E,1,05,8.29,141.8,M,39.3,M,,*4A
        altitude = String((GPS.substring(54,59).toFloat()+GPS.substring(62,67).toFloat())*10);//A magasság 10 szerese az altitude így le lehet küldeni a földre és nem veszít a pontosságból
        altitude = altitude.substring(0,4);//levágom a tizedes jegyeket és a pontot
        SD_run("VV19.txt", "altitude*10" + altitude+"\n");
      }
      else if (GPS.substring(1,6) == "GNVTG") {//$GNVTG,142.83,T,,M,32.919,N,60.967,K,A*21
        speed = String(GPS.substring(28,34).toFloat()*1000);//sebesség km/h ban (horizontal)
        speed = speed.substring(0,5);
        irany = String(GPS.substring(7,13).toFloat()*100);//irány 
        irany = irany.substring(0,5);
        SD_run("VV19.txt", "speed*1000 "+speed+" irany*100 "+ irany+"\n");
      }
      GPS.remove(0,GPS.length()); //üríti a változót a következő sorhoz
    }
  }
}