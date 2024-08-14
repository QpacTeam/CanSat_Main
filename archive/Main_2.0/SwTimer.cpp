#include <Arduino.h>
#include "SwTimer.h"

// DO NOT TOUCH IT!

#define MAX_TIMER 8   // < Maximal number of timers

static volatile unsigned long counters[MAX_TIMER];   // < Counters for Software Timer channels
static volatile unsigned long maxValues[MAX_TIMER];  // < Counters for Software Timer channels

static void (*cb[MAX_TIMER])(void);  // < Callbacks to call by the Software Timers

static unsigned long tick_time;
static unsigned long time_ms;

static unsigned long Cycle;   // < Counting the cycles

void SwTimer_Init(unsigned long ticktime) {

  unsigned int i;

  for (i = 0; i < MAX_TIMER; i++) {   // < Set all timers to 0
    
    cb[i] = 0;
    counters[i] = 0;
    maxValues[i] = 0;
  }

  tick_time = ticktime;   // < Store the clock frequence
  time_ms = millis();     // < Get the actual time
}


void SwTimer_Run(void) {

  unsigned long act_time_ms;
  unsigned long diff;
  unsigned int i;
  
  act_time_ms = millis();         // < Get the actual time
  diff = act_time_ms - time_ms;   // < Calculate the time delation between the actual yet and the past time

  if (diff >= tick_time) {
    time_ms = act_time_ms - (diff - tick_time);   // < Corrigate the tick using the difference of diff and the tick_time

    for (i = 0; i < MAX_TIMER; i++) {             // < Make the opperations on all timer

      if (counters[i] != 0) {
        counters[i]--;              // < Reduce the timer's time

        if (counters[i] == 0) {       // < If the time is over...
          if (maxValues[i] != 0) {      
            counters[i] = maxValues[i];   // < Reload the timer
          }
          if (cb[i] != 0) cb[i]();    // < Run the function attached function
        }
      }
    }
  }

  Cycle++;    // < Cycle grow
}

// Set the timers

void SwTimer_Set_Single(unsigned int ch, unsigned int value_ms, void (*callback)(void)) {
  if (ch < MAX_TIMER) {
    counters[ch] = value_ms;
    maxValues[ch] = 0;          // If the timer ends call a function
    cb[ch] = callback;
  }
}

void SwTimer_Set_Continues(unsigned int ch, unsigned int value_ms, void (*callback)(void)) {
  if (ch < MAX_TIMER) {
    counters[ch] = value_ms;
    maxValues[ch] = value_ms;   // If the timer ends call a function and reset the timer for rerun.
    cb[ch] = callback;
  }
}

void SwTimer_Stop(unsigned int ch) {
  if (ch < MAX_TIMER) {
    counters[ch] = 0;
    maxValues[ch] = 0;        // Stop the chosen timer
    cb[ch] = 0;
  }
}

unsigned long SwTimer_Get_Remaining_Time(unsigned int ch) {
  if (ch < MAX_TIMER) {
    return counters[ch];    // Show the remaining time of the chosen timer
  }
  return 0;
}

#undef MAX_TIMER
