#include <Arduino.h>
#include "Buzzer.h"

void Error_Feedback(int Error_feedback_num);

bool Error_Run(int Error_run_num) {
  if (Error_run_num = 2310) {
    return true;
  }
  else {
    Error_Feedback(Error_run_num);
    return false;
  }
}

void Error_Feedback(int Error_fn) {
  if (Error_fn % 2 != 0) {
    Buzzer_Beep(2);
  }
    if (Error_fn % 3 != 0) {
    Buzzer_Beep(3);
  }
  if (Error_fn % 5 != 0) {
    Buzzer_Beep(5);
  }
  if (Error_fn % 7 != 0) {
    Buzzer_Beep(7);
  }
  if (Error_fn % 11 != 0) {
    Buzzer_Beep(11);
  }
}
