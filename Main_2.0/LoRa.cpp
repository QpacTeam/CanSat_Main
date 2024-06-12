#include <Arduino.h>

#define LORA_LINE_BEGIN ((String)("radio tx"))

UART LoRa(4, 5, NC, NC);      // < define the pins pls!

void LoRa_Init(void) {
  
  LoRa.begin(115200);
  LoRa.println(LORA_LINE_BEGIN + "0");

}

void LoRa_Run(void) {

}

#undef LINE_BEGIN
