#include "SwTimer.h"
#include "BMP.h"
#include "IMU.h"
#include "Card.h"
#include "LoRa.h"
#include "GPS.h"
#include "Buzzer.h"

unsigned long long int timer = 0;
bool state = true;

void setup() {
  delay(500);

  SwTimer_Init(1);
  BMP_Init();
  Card_Init();
  IMU_Init();
  LoRa_Init();
  GPS_Init();
//  Buzzer_Init();

  //                     CH:   Time:        Func:      // rewrite MAX_TIMER in SwTimer.cpp
  SwTimer_Set_Continues(  0,    1,        GPS_Run );
  SwTimer_Set_Continues(  1,    100,      BMP_Run );    
  SwTimer_Set_Continues(  2,    100,      IMU_Run );
  SwTimer_Set_Continues(  3,    100,      Card_Run );
  SwTimer_Set_Continues(  4,    100,      LoRa_Run );

  Buzzer_Cmd(BUZZER_CMD_ON_HIGH);
  Buzzer_Set();

}

void loop() {  
  SwTimer_Run();    // < The core of everything
  if (timer == 2000) {
    if (state) Buzzer_Cmd(BUZZER_CMD_ON_HIGH);
    if (!state) Buzzer_Cmd(BUZZER_CMD_ON_LOW);
    Buzzer_Set();
    timer = 0;
    state = !state;
  }

  timer++;
  delay(1);
}
