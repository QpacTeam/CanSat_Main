#include <Arduino.h>
#include "LoRa.h"
#include "globals.h"

UART LoRa(4, 5);

static const arduino::String FREQ = "863000000";    // < Set frequence
static const arduino::String PWR = "500";

void LoRa_Init(void) {
  LoRa.begin(115200);
  delay(2000);
  LoRa.print("\r\n");
  delay(500);
  LoRa.print("sys reset\r\n");
  delay(500);
  arduino::String ms = "radio set freq " + FREQ + "\r\n";
  LoRa.print(ms);
  delay(500);
  LoRa.print("radio set pwr 1\r\n");  // < set pwr to 20
  delay(500);
  ms = "radio set bw " + PWR + "\r\n";  // < bw does something <<< 
  LoRa.print(ms);
  delay(500);
}

static arduino::String Parcer(void) {    // TODO parcer <<<
  return String("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef");
}

void LoRa_Run(void) {
  String ms = "radio tx " + Parcer() + " 1\r\n";
  LoRa.print(ms);
}
