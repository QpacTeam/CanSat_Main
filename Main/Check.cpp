#include <Arduino.h>
#include "Error.h"

static int Check_Num;
  
void Check_Run(void) {

  do {

    //TODO Check system

  } while (!Error_Run(Check_Num));
}
