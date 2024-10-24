#include <Arduino_LSM6DSOX.h>

//float RateRoll, RatePitch;

float AccX, AccY, AccZ;
float AngleRoll, AnglePitch; // own

float Calc_Angle(float Numerator, float Devider_1, float Devider_2);
void gyro_Run(void);

void setup(void) {
  Serial.begin(9600);
  IMU.begin();
}

void loop(void) {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(AccX, AccY, AccZ);
  }
  Serial.println("");
  Serial.println(AccX);
  Serial.println(AccY);
  Serial.println(AccZ);


/*
  gyro_Run();

  Serial.println("");
  Serial.println(String(AngleRoll/3.14*180));
//  Serial.println("Pitch: " + String(AnglePitch/3.14*180));

*/
  delay(200);
}



void gyro_Run(void){
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(AccX, AccY, AccZ);
  }

  AngleRoll = Calc_Angle(AccY, AccX, AccZ);
  AnglePitch = Calc_Angle((-1)*AccX, AccY, AccZ);
  
}

float Calc_Angle(float Numerator, float Devider_1, float Devider_2) {
  return atan(Numerator/sqrt((Devider_1*Devider_1) + (Devider_2*Devider_2)));
}
