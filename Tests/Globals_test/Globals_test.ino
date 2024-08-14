#include "globals.h"


void setup() {
  Serial.begin(9600);

}

void loop() {
  delay(500);
  Serial.println(valami);

  function();

  valami++;

}
