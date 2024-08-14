#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "SwTimer.h"
#include "BMP.h"

#define BMP_SEE_LEVEL_PRESSURE ((float)(1013.25))

static Adafruit_BMP280 bmp;
static float temperature;
static float pressure;
static float altitude;
arduino::String BMP_Data[3];

void BMP_Init(void) {

  for (unsigned int i =0; i <2; i++) {    // < Clear the array
    BMP_Data[i] = "";
  }

  unsigned int status;                                      // < Idk (what the fuck is this!?)
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void BMP_Run(void) {

  temperature = bmp.readTemperature();
  pressure = bmp.readPressure();
  altitude = bmp.readAltitude(BMP_SEE_LEVEL_PRESSURE);

  BMP_Data[0] = String(temperature);
  BMP_Data[1] = String(pressure);
  BMP_Data[2] = String(altitude);
}

arduino::String BMP_Get_Data(void) {
  return BMP_Data[3];
}

#undef BMP_SEE_LEVEL_PRESSURE
