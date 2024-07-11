/* === INCLUDES === */
#include "SwTimer.h"
#include "Card.h"
#include "BMP.h"
#include "GPS.h"
#include "LoRa.h"

arduino::String Data_Flow[10];
unsigned long Main_State = 0;

/* === SW TIMER SETTINGS === */
#define BMP_CH 0
#define BMP_TIME 10
#define CARD_CH 1
#define CARD_TIME 10
#define LORA_CH 2
#define LORA_TIME 10


void setup() {

  Serial.begin(9600);

  /* === INITS === */
  SwTimer_Init(1);
  BMP_Init();
  Card_Init();
  LoRa_Init();

  /* === SET TIMERS === */
  SwTimer_Set_Continues( BMP_CH,    BMP_TIME,    BMP_Run  );
  SwTimer_Set_Continues( CARD_CH,   CARD_TIME,   Card_Run );
  SwTimer_Set_Continues( LORA_CH,   LORA_TIME,   LoRa_Run );
}

void loop() {         // TODO make the states
  swich(Main_State){
    case 0:
    {
      SwTimer_Run();
      break;
    }
    default:
    {

      break;
    }
  }
}

#undef BMP_CH
#define BMP_TIME
