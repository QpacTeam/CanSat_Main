#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "SwTimer.h"
#include "BMP.h"

#define BMP_SEE_LEVEL_PRESSURE ((float)(1013.25f))
#define SWTIMER_CH_BMP 1

static Adafruit_BMP280 bmp;
static float temperature;
static float pressure;
static float altitude;
const char* TPA_Data;


void BMP_Init(void) {
  unsigned int status;

  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

}

const char* BMP_Run(void) {

  temperature = bmp.readTemperature();
  pressure = bmp.readPressure();
  altitude = bmp.readAltitude(BMP_SEE_LEVEL_PRESSURE);

  String Ra = String(temperature) + ';' + String(pressure) + ';' + String(altitude);
  const char* TPA_Data =  Ra.c_str();
  return TPA_Data;

}


#undef BMP_SEE_LEVEL_PRESSURE
#undef SWTIMER_CH_BMP
