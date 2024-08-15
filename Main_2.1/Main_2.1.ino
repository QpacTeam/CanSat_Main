#include "globals.h"
#include "SwTimer.h"
#include "BMP.h"
#include "Card.h"

/* === Test Statement === */
#define TEST false

static unsigned long State = 0;   // TOTO make the states!

void setup() {
  Serial.begin(9600);
  SwTimer_Init(1);
  BMP_Init();
  Card_Init();
  //                     CH:   Time:     Func:
  SwTimer_Set_Continues(  0,    10,     BMP_Run );    // rewrite MAX_TIMER in SwTimer.cpp
  SwTimer_Set_Continues(  1,    10,     Card_Run );

}

void loop() {

  if (TEST) {
    Serial.println(SwTimer_Cycle);

    Serial.println(BMP_Data[0]);
    Serial.println(BMP_Data[1]);
    Serial.println(BMP_Data[2]);
    Serial.println("");
  }

  SwTimer_Run();
}

#undef TEST
