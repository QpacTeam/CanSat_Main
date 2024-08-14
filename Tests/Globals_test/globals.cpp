#include <Arduino.h>

unsigned long valami = 5;

void function(void) {
 
  Serial.print("from func: ");
  Serial.println(valami);
}