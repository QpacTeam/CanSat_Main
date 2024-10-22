#include <Arduino.h>
#include "SwTimer.h"

#define MAX_TIMER 8


static volatile unsigned long counters[MAX_TIMER];   // < Counters for Software Timer channels
static volatile unsigned long maxValues[MAX_TIMER];  // < Counters for Software Timer channels

static void (*cb[MAX_TIMER])(void);  //< Callbacks to call by the Software Timers

static unsigned long tick_time;
static unsigned long time_ms;

void SwTimer_Init(unsigned long ticktime) {
  unsigned int i;
  for (i = 0; i < MAX_TIMER; i++) {
    cb[i] = 0;
    counters[i] = 0;
    maxValues[i] = 0;
  }
  tick_time = ticktime;
  time_ms = millis();
}


void SwTimer_Run(void) {
  unsigned long act_time_ms;
  unsigned long diff;
  unsigned int i;
  act_time_ms = millis();
  diff = act_time_ms - time_ms;

  if (diff >= tick_time) {
    time_ms = act_time_ms - (diff - tick_time);
    for (i = 0; i < MAX_TIMER; i++) {
      if (counters[i] != 0) {
        counters[i]--;
        if (counters[i] == 0) {
          if (maxValues[i] != 0) {  // Reload
            counters[i] = maxValues[i];
          }
          if (cb[i] != 0) cb[i]();
        }
      }
    }
  }
}

void SwTimer_Set_Single(unsigned int ch, unsigned int value_ms, void (*callback)(void)) {
  if (ch < MAX_TIMER) {
    counters[ch] = value_ms;
    maxValues[ch] = 0;
    cb[ch] = callback;
  }
}

void SwTimer_Set_Continues(unsigned int ch, unsigned int value_ms, void (*callback)(void)) {
  if (ch < MAX_TIMER) {
    counters[ch] = value_ms;
    maxValues[ch] = value_ms;
    cb[ch] = callback;
  }
}

void SwTimer_Stop(unsigned int ch) {
  if (ch < MAX_TIMER) {
    counters[ch] = 0;
    maxValues[ch] = 0;
    cb[ch] = 0;
  }
}

unsigned long SwTimer_Get_Remaining_Time(unsigned int ch) {
  if (ch < MAX_TIMER) {
    return counters[ch];
  }
  return 0;
}

#undef MAX_TIMER
