#include <Arduino.h>

#define LORA_LINE_BEGIN ((String)("radio tx"))


void LoRa_Init(void) {
  
  Serial1.begin(115200);
  Serial1.println(LORA_LINE_BEGIN + "__START COMMUNICATION__");

}

void LoRa_Run(int Typ_LoRa, const char* Data_LoRa) {

  if (Serial1) {
    switch (Typ_LoRa) {
      case 0:
        {  // Pressure and teperature T
          Serial1.print(LORA_LINE_BEGIN + "T;");
          Serial1.println(Data_LoRa);
          break;
        }
      case 1:
        {  // GPS data G
          Serial1.print(LORA_LINE_BEGIN + "G;");
          Serial1.println(Data_LoRa);
          break;
        }
      case 2:
        { // IMU I
          Serial1.print(LORA_LINE_BEGIN + "I;");
          Serial1.println(Data_LoRa);
          break;
        }
      default:
        { // Unsigned U
          Serial1.print(LORA_LINE_BEGIN + "U;");
          Serial1.println(Data_LoRa);
          break;
        }
    }
  }
}

#undef LINE_BEGIN
