#include "globals.h"
#include "SwTimer.h"
#include "BMP.h"
#include "IMU.h"
#include "Card.h"
#include "LoRa.h"
#include "GPS.h"

/* === Test Statement === */
#define TEST false

// TODO finish the enum!
/*
typedef enum {
  MAIN_STATE_BLS = 0,
  MAIN_STATE_LOS = 1,
  MAIN_STATE_MMS = 2,
  MAIN_STATE_AMS = 3
} missin_state_e;
*/

unsigned long missionState = 0;   // TOTO make the states!

void setup() {
  Serial.begin(9600);

  SwTimer_Init(1);
  BMP_Init();
  Card_Init();
  IMU_Init();
  LoRa_Init();
  GPS_Init();
  //                     CH:   Time:     Func:
  SwTimer_Set_Continues(  0,    10,     BMP_Run );    // rewrite MAX_TIMER in SwTimer.cpp
  SwTimer_Set_Continues(  1,    10,     IMU_Run );
  SwTimer_Set_Continues(  2,    200,    Card_Run );
  SwTimer_Set_Continues(  3,    100,    LoRa_Run );
  SwTimer_Set_Continues(  4,    100,    GPS_Run ); 

}

void loop() {
  switch (missionState) {
    case 0:
      // Tasks
      break;
    case 1:
      // Tasks
      break;
    case 2:
      // Tasks
      break;
    case 3:
      // Tasks
      break;
    default: break;
  }
  SwTimer_Run();
}

#undef TEST     // <<<
