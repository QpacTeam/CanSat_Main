#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "BMP.h"

#define cPress ((float)(1013.25))    // < Constans sea level pressure in hPa (hectopascal)

static Adafruit_BMP280 bmp;
static float temperature;
static float pressure;
static float altitude;

double BMP_Data[3];

void BMP_Init(void) {
  for (static unsigned int i =0; i <2; i++) BMP_Data[i] = 0;    // < Clear the array

  unsigned int status;                                      // < Idk (what the fuck is this!?)
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void BMP_Run(void) {
  temperature = bmp.readTemperature();    BMP_Data[0] = temperature;  // < celsius 
  pressure    = bmp.readPressure();       BMP_Data[1] = pressure;     // < Pa (pascal)
  altitude    = bmp.readAltitude(cPress); BMP_Data[2] = altitude;     // < meter
  /*
  BMP_Data[0] = bmp.readTemperature();
  BMP_Data[1] = bmp.readPressure();
  BMP_Data[2] = bmp.readAltitude(cPress);*/
//  for (int i = 0; i < 3; i++){
//    Serial.println(BMP_Data[i]);
//  }
//  Serial.println("");
}

#undef cPress
