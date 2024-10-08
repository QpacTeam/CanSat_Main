/* Sensor data */
extern double BMP_Data[3];              // < from BMP.cpp
extern float IMU_Data[7];               // < from IMU.cpp
extern double GPS_Data[7];              // < from GPS.cpp
extern char Whole_GPS[128];             // < from GPS.cpp 

/* system data */
extern bool error_report[];             // < Get the errors < TODO finish
extern unsigned long missionState;      // < from Main_2.1.cpp
extern unsigned long SwTimer_Cycle;     // < from SwTimer.cpp
