#include <Arduino.h>
#include "BMP.h"

void DataProcess_Init(void) {
  ;
}

arduino::String DataProcess_Run(void) {
  
  arduino::String BMP_data[3];
  
  /* === Get All === */
  BMP_data[3] = BMP_Get_Data();   // < BMP



}