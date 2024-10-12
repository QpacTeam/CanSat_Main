#ifndef TRUSTER_H_INCLUDED
#define TRUSTER_H_INCLUDED

typedef enum {
  TRUSTER_CMD_OFF = 0,
  BUZZER_CMD_ON = 1,
} truster_cmd_e;

void Truster_Init(void);
void Truster_Run(void);
void Truster_Cmd(void);

#endif