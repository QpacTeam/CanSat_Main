#include "SwTimer.h"
#include "BMP.h"
#include "IMU.h"
#include "Card.h"
#include "LoRa.h"
#include "GPS.h"

void setup() {
  delay(500);

  SwTimer_Init(1);
  BMP_Init();
  Card_Init();
  IMU_Init();
  LoRa_Init();
  GPS_Init();

  //                     CH:   Time:        Func:      // rewrite MAX_TIMER in SwTimer.cpp
  SwTimer_Set_Continues(  0,    1,        GPS_Run );
  SwTimer_Set_Continues(  1,    100,      BMP_Run );    
  SwTimer_Set_Continues(  2,    100,      IMU_Run );
  SwTimer_Set_Continues(  3,    100,      Card_Run );
  SwTimer_Set_Continues(  4,    100,      LoRa_Run );
}

void loop() {  
  SwTimer_Run();    // < The core of everything
}
