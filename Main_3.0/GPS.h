#ifndef GPS_H_INCLUDED
#define GPS_H_INCLUDED

extern void GPS_Init(void);
extern void GPS_Run(void);
extern double* GPS_GetData(void);
extern unsigned int GPS_GetDataSize(void);

#endif  // LORA_H_INCLUDED
