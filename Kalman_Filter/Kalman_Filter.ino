#include <Arduino_LSM6DSOX.h>

const unsigned int size = 7;
float Ax, Ay, Az, RRoll, RPitch, RYaw, ARoll, APitch, AYaw;
float RCRoll, RCPitch, RCYaw;
int RCNumber;
float KARoll = 0, KAPitch = 0, KUARoll = 1*1, KUAPitch = 2*2;
float Output[] = {0, 0};
double Ts = 0.004;
float cal;
float IMU_Data[size];


void kalman(float KState, float KUncertainty, float KInput, float KMeasurement){
  KState = KState + Ts * KInput;
  KUncertainty = KUncertainty + Ts*Ts*1*1;
  float KGain = KUncertainty*1/(1*KUncertainty + 1*1);
  KState = KState + KGain * (KMeasurement - KState);
  KUncertainty = (1-KGain)*KUncertainty;
  Output[0] = KState;
  Output[1] = KUncertainty;
}


void setup() {
  Serial.begin(9600);
  unsigned int i;
  Ax, Ay, Az, RRoll, RPitch, RYaw = 0;

  for (i=0; i < 7; i++) IMU_Data[i] = '\0';
  if (!IMU.begin()) Serial.println("Failed to initialize IMU!");  // TODO add error modul!
  delay(500);
  //i = 0;
  //cal = 0;
  //while (i < 2000) {
  //  if (IMU.gyroscopeAvailable()) {
  //    IMU.readGyroscope(RRoll, RPitch, RYaw);
  //    i++;
  //    cal += RRoll;
  //    Serial.println(RRoll);
  //  }
  //  delay(1);
  //}
  //cal = cal/2000;
}

void loop(void) {
  if (IMU.accelerationAvailable()) { IMU.readAcceleration(Ax, Ay, Az);
    IMU_Data[0] = Ax;
    IMU_Data[1] = Ay;
    IMU_Data[2] = Az;

    ARoll = atan(Ay/sqrt(Ax*Ax + Az*Az)) / 3.14 * 180;
    APitch = atan(-1*Ax/sqrt(Ay*Ay + Az*Az));
    //AYaw = atan(Az/sqrt(Ax*Ax + Ay*Ay));
    //Serial.println(AnglePitch/3.14*180);
    //Serial.println(AngleRoll/3.14*180);
    //Serial.println(AngleYaw/3.14*180);

  }
  if (IMU.gyroscopeAvailable()) { IMU.readGyroscope(RRoll, RPitch, RYaw);
    IMU_Data[3] = RRoll;
    IMU_Data[4] = RPitch;
    IMU_Data[5] = RYaw;

    //Serial.println(RRoll - cal);
    //Serial.println(RPitch);
    //Serial.println(RYaw);
  
  }

  kalman(KARoll, KUARoll, RRoll-cal, ARoll);
  KARoll = Output[0];
  KUARoll = Output[1];
  //kalman(KAPitch, KUAPitch, RPitch, APitch);
  //KAPitch = Output[0];
  //KUAPitch = Output[1];

  delay(Ts*1000);
  Serial.print("Kalman: ");
  Serial.println(KARoll);
  Serial.print("Acc: ");
  Serial.println(ARoll);
}