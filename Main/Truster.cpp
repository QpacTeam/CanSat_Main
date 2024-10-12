#include <Arduino.h>

#define TRUSTER_PIN (20)

static bool truster_act_sm = false;
static bool truster_new_sm = false;

typedef enum {
  TRASTER_SM_OFF = 0,
  TRASTER_SM_ON_HIGH = 1,
} truster_cmd_e;

void Truster_Init(void) {
  
  pinMode(TRUSTER_PIN, OUTPUT);
  digitalWrite(TRUSTER_PIN, LOW);
}

static void Truster_Run(void) {
  //TUDO biztonsági rendszer
}
void Truster_Cmd(truster_cmd_e cmd) {
  truster_new_sm = cmd;
  if (truster_new_sm != truster_act_sm) {
    switch (truster_act_sm) {
      case true:
        {
          switch (truster_new_sm) {
            case true:
              {
                break;
              }
            case false:
              {
                digitalWrite(TRUSTER_PIN, LOW);
                break;
              }
            default:
              {
                break;
              }
          }
          break;
        }
      case false:
        {
          switch (truster_new_sm) {
            case true:
              {
                digitalWrite(TRUSTER_PIN, HIGH);
                break;
              }
            case false:
              {
                break;
              }
            default:
              {
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
    truster_act_sm = truster_new_sm;
  }
}

#undef TRUSTER_PIN
