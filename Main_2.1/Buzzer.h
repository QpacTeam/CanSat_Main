#ifndef BUZZER_H_INCLUDED
#define BUZZER_H_INCLUDED

typedef enum {
  BUZZER_CMD_OFF      = 0,
  BUZZER_CMD_ON_HIGH  = 1,
  BUZZER_CMD_ON_LOW   = 2
} buzzer_cmd_e;

/*
void Buzzer_Init(void);
void Buzzer_Run(void);
void Buzzer_tick(void);
void Buzzer_Cmd(buzzer_cmd_e cmd);
void Buzzer_Beep(int Buzzer_Beep_Num);
*/

void Buzzer_Init(void);
void Buzzer_Run(void);
void Buzzer_Cmd(buzzer_cmd_e cmd);
void Buzzer_Beep(int unsigned Buzzer_Beep_Num);

#endif  // BUZZER_H_INCLUDED