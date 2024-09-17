/* Sensor data */
extern double BMP_Data[3];             // < from BMP.cpp  <<< to double
extern float IMU_Data[7];             // < from IMU.cp   <<< to double
extern double GPS_Data[7];     // < from GPS.cpp <<< put the value

/* system data */
extern bool error_report[];           // < Get the errors <<< put the value
extern unsigned long missionState;    // < from Main_2.1.cpp
extern unsigned long SwTimer_Cycle;   // < from SwTimer.cpp
