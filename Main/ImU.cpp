#include <Arduino.h>
#include <Arduino_LSM6DSOX.h>

const char* ImU_Data;

void ImU_Init(void) {

  IMU.begin();
}

const char* ImU_Run(void) {

  String Im = String(IMU.accelerationSampleRate()) + String(IMU.gyroscopeSampleRate());
  ImU_Data = Im.c_str();

  return ImU_Data;
}

bool ImU_Acceleration_Test(void) {
  for (static int i = 3; i > 0; i --)
    if (IMU.accelerationSampleRate() < 20) {
      return false;
    }
  }
  return true;
}
