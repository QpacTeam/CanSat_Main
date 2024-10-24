#ifndef BUZZER_H_INCLUDED
#define BUZZER_H_INCLUDED

typedef enum {
  BUZZER_CMD_OFF = 0,
  BUZZER_CMD_ON_HIGH = 1,
  BUZZER_CMD_ON_LOW = 2
} buzzer_cmd_e;

extern void Buzzer_Init(void);
extern void Buzzer_Set(void);
extern void Buzzer_Run(void);
extern void Buzzer_Cmd(buzzer_cmd_e cmd);
//extern void Buzzer_Beep(int Buzzer_Beep_Num);

#endif  // BUZZER_H_INCLUDED
