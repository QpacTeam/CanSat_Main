#ifndef IMU_H_INCLUDED
#define IMU_H_INCLUDED

extern void IMU_Init(void);
extern void IMU_Run(void);
extern float* IMU_GetData(void);
extern unsigned int IMU_GetDataSize(void);

#endif  // IMU_H_INCLUDED
