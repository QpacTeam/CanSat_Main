#include <Arduino.h>
#include "LoRa.h"
#include "globals.h"

UART LoRa(4, 5);

static const arduino::String FREQ = "863000000";    // < Set frequence
static const arduino::String PWR = "125";

static char LoRa_Ms[64];

arduino::String ms;

void LoRa_Init(void) {
  LoRa.begin(115200);
  delay(2000);
  LoRa.print("\r\n");
  delay(500);
  LoRa.print("sys reset\r\n");
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
  delay(500);
  LoRa.print("radio set pwr 1\r\n");  // < set pwr to 20
  delay(500);
  ms = "radio set bw " + PWR + "\r\n";  // < bw does something <<< 
  LoRa.print(ms);
  delay(500);
  */
}

static void Parcer(void) {    // TODO parcer <<<
  for (int i=0; i < 10; i++) LoRa_Ms[i] = i;

}

void LoRa_Run(void) {
  Parcer();
  
  String ms = "radio tx 1234321 1\r\n";
  Serial.println(ms);
  LoRa.print("radio tx 1234321 1\r\n");   // < sending
}
