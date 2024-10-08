#include <Arduino_LSM6DSOX.h>

float RateRoll, RatePitch, RateYaw;
float RateCalibrationRoll, RateCalibrationPitch, RateCalibrationYaw;

int RateCalibrationNumber;

float AccX, AccY, AccZ;
float AngleRoll, AnglePitch;
uint32_t LoopTimer;

float KalmanAngleRoll = 0,
      KalmanUncertaintyAngleRoll = 2*2;

float KalmanAnglePitch = 0,
      KalmanUncertaintyAnglePitch = 2*2;

float Kalman1DOutput{0,0};


void setup() {
  Serial.begin(9600);
  for (RateCalibrationNumber=0; RateCalibrationNumber<2000; RateCalibrationNumber++ ) {
    
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}

void Read_Gyro() {
  if (IMU.accelerationAvailable()) { IMU.readAcceleration(AccX, AccY, AccZ);
  
  AngleRoll = atan(AccY/sqrt(AccX*AccX+AccZ*AccZ))*1/(3.142/180);
  AngleRoll = atan(AccX/sqrt(AccY*AccY+AccZ*AccZ))*1/(3.142/180);
}

void kalman_1d(float KalmanState, float KalmanUncertainty, float KalmanInput, float KalmanMeasurement) {
  
  KalmanState = KalmanState + 0.004*KalmanInput;
  KalmanUncertainty = KalmanUncertainty + 0.004*0.004 * 4*4;
  
  float KalmanGain = KalmanUncertainty*1 / (1*KalmanUncertainty + 3*3);
  
  KalmanState = KalmanState + KalmanGain*(KalmanMeasurement-KalmanState);
  KalmanUncertainty = (1-KalmanGain)*KalmanUncertainty;

  Kalman1DOutput[0] = KalmanState;
  Kalman1DOutput[1] = KalmanUncertainty;
}
