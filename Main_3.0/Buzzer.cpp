#include <Arduino.h>
#include <WiFiNINA.h>
#include "Buzzer.h"
#include "SwTimer.h"


#define BUZZER_PIN (21)
#define BUZZER_RESOUTION ((int)(100))  // 100 milisec
#define BUZZER_HIGH_PERIOD 6
#define BUZZER_LOW_PERIOD 20

typedef enum {
  BUZZER_SM_OFF = 0,
  BUZZER_SM_ON_HIGH = 1,
  BUZZER_SM_ON_LOW = 2
} buzzer_sm_e;

static buzzer_sm_e act_sm = BUZZER_SM_OFF;
static buzzer_sm_e new_sm = BUZZER_SM_OFF;
static int tick_counter;
static int period;
static int duty;

void Buzzer_tick(void);

void Buzzer_Init(void) {

  act_sm = BUZZER_SM_OFF;  //  Buzzer off State
  new_sm = BUZZER_SM_OFF;
  tick_counter = 0;
  period = 0;
  duty = 0;

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}



void Buzzer_Run(void) {

  if (act_sm != BUZZER_SM_OFF) {
    if (tick_counter >= period) {
      tick_counter = 0;
      digitalWrite(BUZZER_PIN, HIGH);
    } else if (tick_counter >= duty) {
      digitalWrite(BUZZER_PIN, LOW);
    } else {
      //do
    }
  }

  if (act_sm != new_sm) {
    switch (act_sm) {
      case BUZZER_SM_OFF:
        {
          switch (new_sm) {
            case BUZZER_SM_ON_HIGH:
              {
                period = BUZZER_HIGH_PERIOD;
                duty = period / 2;
                break;
              }
            case BUZZER_SM_ON_LOW:
              {
                period = BUZZER_LOW_PERIOD;
                duty = period / 2;
                break;
              }
            default:
              {
                // Do it nothing
                break;
              }
          }
          break;
        }
      case BUZZER_SM_ON_HIGH:
        {
          switch (new_sm) {
            case BUZZER_SM_OFF:
              {
                digitalWrite(BUZZER_PIN, LOW);
                break;
              }
            case BUZZER_SM_ON_LOW:
              {
                period = BUZZER_LOW_PERIOD;
                duty = period / 2;
                break;
              }
            default:
              {
                // Do it nothing
                break;
              }
          }
          break;
        }
      case BUZZER_SM_ON_LOW:
        {
          switch (new_sm) {
            case BUZZER_SM_OFF:
              {
                digitalWrite(BUZZER_PIN, LOW);
                break;
              }
            case BUZZER_SM_ON_HIGH:
              {
                period = BUZZER_HIGH_PERIOD;
                duty = period / 2;
                break;
              }
            default:
              {
                // Do it nothing
                break;
              }
          }
          break;
        }
      default:
        {
          break;
        }
    }
    act_sm = new_sm;
  }
}

void Buzzer_Cmd(buzzer_cmd_e cmd) {
  switch (cmd) {
    case BUZZER_CMD_OFF:
      {
        new_sm = BUZZER_SM_OFF;
        break;
      }
    case BUZZER_CMD_ON_LOW:
      {
        new_sm = BUZZER_SM_ON_LOW;
        break;
      }
    case BUZZER_CMD_ON_HIGH:
      {
        new_sm = BUZZER_SM_ON_HIGH;
        break;
      }
    default:
      {
        // Do it nothing!
        break;
      }
  }
}

void Buzzer_tick(void) {
  tick_counter++;
}

void Buzzer_Beep(int Buzzer_Beep_Num) {
  for (Buzzer_Beep_Num; Buzzer_Beep_Num > 0; Buzzer_Beep_Num --) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LEDR, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LEDR, HIGH);
    delay(300);
  }
  delay(700);
}




#undef BUZZER_PIN
#undef BUZZER_RESOUTION((int)(100))  // 100 milisec
#undef BUZZER_HIGH_PERIOD 6
#undef BUZZER_LOW_PERIOD 20