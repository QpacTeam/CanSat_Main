#include <Arduino.h>
#include <Arduino_LSM6DSOX.h>
#include "IMU.h"

static float Ax, Ay, Az, Gx, Gy, Gz;
static int Temp;
float IMU_Data[7];

void IMU_Init(void) {
  unsigned int i;
  Ax, Ay, Az, Gx, Gy, Gz = 0;
  Temp = 0;

  for (i=0; i < 7; i++) IMU_Data[i] = '\0';
  if (!IMU.begin()) Serial.println("Failed to initialize IMU!");  // TODO add error modul!
}

void IMU_Run(void) {
  if (IMU.accelerationAvailable()) { IMU.readAcceleration(Ax, Ay, Az);
    IMU_Data[0] = Ax;
    IMU_Data[1] = Ay;
    IMU_Data[2] = Az;
  }
  if (IMU.gyroscopeAvailable()) { IMU.readGyroscope(Gx, Gy, Gz);
    IMU_Data[3] = Gx;
    IMU_Data[4] = Gy;
    IMU_Data[5] = Gz;
  }
  if (IMU.temperatureAvailable()) { IMU.readTemperature(Temp);
    IMU_Data[6] = Temp;
  }
}
