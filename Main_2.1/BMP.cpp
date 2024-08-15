#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
//#include "SwTimer.h"
#include "BMP.h"

#define cPress ((float)(1013.25))    // < Constans sea level pressure in hPa (hectopascal)

static Adafruit_BMP280 bmp;
static float temperature;
static float pressure;
static float altitude;

arduino::String BMP_Data[3];

void BMP_Init(void) {
  for (static unsigned int i =0; i <2; i++) BMP_Data[i] = "";    // < Clear the array

  unsigned int status;                                      // < Idk (what the fuck is this!?)
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void BMP_Run(void) {
  temperature = bmp.readTemperature();    BMP_Data[0] = String(temperature);  // < celsius 
  pressure    = bmp.readPressure();       BMP_Data[1] = String(pressure);     // < Pa (pascal)
  altitude    = bmp.readAltitude(cPress); BMP_Data[2] = String(altitude);     // < meter
}

#undef cPress
