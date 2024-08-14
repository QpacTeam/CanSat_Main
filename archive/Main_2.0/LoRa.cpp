#include <Arduino.h>
#include "DataProcess.h"

#define LORA_LINE_BEGIN ((String)("radio tx"))

UART LoRa(4, 5, NC, NC);      // < define the pins pls!

void LoRa_Init(void) {
  
  LoRa.begin(115200);
  LoRa.println("sys reset");
  LoRa.println(LORA_LINE_BEGIN + "0");
  // TODO set the device to transmitter !!! 

}

void LoRa_Run(void) {
  arduino::String LoRa_Data_To_Send = "1";

  while (!LoRa) {
    ; //TODO delay buffer 
  }

  LoRa_Data_To_Send = DataProcess_Run();

  LoRa.print(LORA_LINE_BEGIN + LoRa_Data_To_Send);

}

#undef LORA_LINE_BEGIN
