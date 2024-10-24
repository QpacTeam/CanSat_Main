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

const float C_R = 0.10;
const float C_P = 0.14;
const float C_W = -0.005;

const float C_X = 0;
const float C_Y = 0;
const float C_Z = 0.01;

int counter = 0; 


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

    Ax -= C_X;
    Ay -= C_Y;
    Az -= C_Z;

    IMU_Data[0] = Ax;
    IMU_Data[1] = Ay;
    IMU_Data[2] = Az;

    //Serial.println(Ax);
    //Serial.println(Ay);
    //Serial.println(Az);

    ARoll = atan(Ay/sqrt(Ax*Ax + Az*Az)) / PI * 180;
    APitch = atan(-1*Ax/sqrt(Ay*Ay + Az*Az)) / PI * 180;

    //Serial.println(Ax);
    //Serial.println(Ay);
    //Serial.println(Az);

  }
  if (IMU.gyroscopeAvailable()) { IMU.readGyroscope(RRoll, RPitch, RYaw);
    
    RRoll  -= C_R;
    RPitch -= C_P;
    RYaw   -= C_W;

    IMU_Data[3] = RRoll;
    IMU_Data[4] = RPitch;
    IMU_Data[5] = RYaw;

    //Serial.println("");
    //Serial.println(RRoll);
    //Serial.println(RPitch);
    //Serial.println(RYaw);

  }

  kalman(KARoll, KUARoll, RRoll-cal, ARoll);
  KARoll = Output[0];
  KUARoll = Output[1];
  //kalman(KAPitch, KUAPitch, RPitch, APitch);
  //KAPitch = Output[0];
  //KUAPitch = Output[1];

  //delay(1);
  delay(Ts*1000);
  Serial.print("Variable_1:");
  Serial.print(KARoll);
  Serial.print(",");
  Serial.print("Variable_2:");
  Serial.print(ARoll);
  Serial.print(",");
  Serial.print("Variable_3:");
  Serial.print(-90);
  Serial.print(",");
  Serial.print("Variable_4:");
  Serial.println(90);

 


}
