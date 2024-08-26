#include <sys/_types.h>
#include <Arduino.h>
#include <WiFiNINA.h>
#include "Buzzer.h"

#define BUZZER_PIN 21
#define BUZZER_RES ((int)(100)) // < 100 milisec

typedef enum {
  BUZZER_SM_OFF = 0,
  BUZZER_SM_ON_HIGH = 1,      // This shit is connected to 
  BUZZER_SM_ON_LOW = 2              
} buzzer_sm_e;

static buzzer_sm_e act_sm = BUZZER_SM_OFF;    // < This shit! 
static buzzer_sm_e new_sm = BUZZER_SM_OFF;
static unsigned int tick_counter;

static unsigned int period;
static unsigned int duty;

void Buzzer_Init(void) {
  act_sm = BUZZER_SM_OFF;
  tick_counter = 0;
}

void Buzzer_Run(void) {
  if (act_sm != BUZZER_SM_OFF) {
    if tick_counter 
  }




}







void Buzzer_Beep(int unsigned Buzzer_Beep_Num) {
  for (Buzzer_Beep_Num; Buzzer_Beep_Num > 0; Buzzer_Beep_Num --) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LEDR, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LEDR, LOW);
    delay(300);
  }
  delay(700);
}

#undef BUZZER_PIN
#undef BUZZER_RES
