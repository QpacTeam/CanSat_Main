#include <Arduino.h>
#include "LoRa.h"
#include "globals.h"

UART LoRa(4, 5);
/*
static const arduino::String FREQ = "863000000";    // < Set frequence
static const arduino::String PWR = "125";
*/
static char LoRa_Ms[64];

arduino::String ms;

void LoRa_Init(void) {
  LoRa.begin(115200);
  delay(2000);
  LoRa.print("\r\n");   // < the first message is trash 
  delay(500);
  LoRa.print("sys reset\r\n");  // < system reset
  delay(500);
  /*
  ms = "radio set sync 34\r\n";
  LoRa.print(ms);
  delay(500);

  ms = "radio set sync 34\r\n";
  LoRa.print(ms);
  delay(500);
  
  
  arduino::String ms = "radio set freq " + FREQ + "\r\n";
  LoRa.print(ms);
  delay(500);*/
  LoRa.print("radio set pwr 20\n");  // < set pwr to 20
  delay(500);
  /*ms = "radio set bw " + PWR + "\r\n";  // < bw does something <<< 
  LoRa.print(ms);
  delay(500);
  */
}

static void Parcer(void) {

  int cur_time = GPS_Data[0];         // first data: time, 6 digits in message, no decimals
  for (int i = 5; i >= 0; i--){
    LoRa_Ms[i] = cur_time % 10 + 48;
    cur_time = cur_time / 10;
  }

  int latitude = GPS_Data[1] * 10000;    // second data: latitude, 8 digits in message, last 4 are decimals
  for (int i = 13; i >= 6; i--){
    LoRa_Ms[i] = latitude % 10 + 48;
    latitude = latitude / 10;
  }

  int longitude = GPS_Data[2] * 10000;    // third data: longitude, 9 digits in message, last 4 are decimals
  for (int i = 22; i >= 14; i--){
    LoRa_Ms[i] = longitude % 10 + 48;
    longitude = longitude / 10;
  }

  int sat = GPS_Data[3];               // forth data: satelites used, 2 digits in message, no decimals
  for (int i = 24; i >= 23; i--){
    LoRa_Ms[i] = sat % 10 + 48;
    sat = sat / 10;
  }

  int hdop = GPS_Data[4] * 100;     // fifth data: hdop, 3 digits in message, last 2 are decimals
  for (int i = 27; i >= 25; i--){
    LoRa_Ms[i] = hdop % 10 + 48;
    hdop = hdop / 10;
  }

  int altitude = GPS_Data[5] * 10;    // sixth data: msl_altitude, 5 digits in message, last 1 is decimal
  for (int i = 32; i >= 28; i--){
    LoRa_Ms[i] = altitude % 10 + 48;
    altitude = altitude / 10;
  }

  int geo = GPS_Data[6] * 10;        // seventh data: geoid separation, 4 digits in message, last 1 is decimal
  for (int i = 36; i >= 33; i--){
    LoRa_Ms[i] = geo % 10 + 48;
    geo = geo / 10;
  }

  int temp = BMP_Data[0] * 100;     // eighth data, temperature, first digit is SIGN!!!, 0 if +, 1 if -, plus 4 digits data, last 2 are decimals               
  if (temp < 0) {
    temp = -temp;
    LoRa_Ms[37] = 1 + 48;
  } else LoRa_Ms[37] = 0 + 48;
  for (int i = 41; i >= 38; i--){
    LoRa_Ms[i] = temp % 10 + 48;
    temp = temp / 10;
  }

  int pres = BMP_Data[1] * 100;    // ninth data, pressure, 8 digits in message, last 2 are decimals
  for (int i = 49; i >= 42; i--){
    LoRa_Ms[i] = pres % 10 + 48;
    pres = pres / 10;
  }
  
}

void LoRa_Run(void) {
  Parcer();
  String ms = "radio tx " + String(LoRa_Ms) + " 1\r\n";
  LoRa.print(ms);   // < sending
}
