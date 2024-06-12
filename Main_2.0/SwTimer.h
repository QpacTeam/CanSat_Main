#ifndef SW_TIMER_H_INCLUDED
#define SW_TIMER_H_INCLUDED

// DO NOT TOUCH IT!

void SwTimer_Init(unsigned long ticktime);
void SwTimer_Run(void);

void SwTimer_Set_Single(unsigned int ch, unsigned int value_ms, void (*callback)(void));
void SwTimer_Set_Continues(unsigned int ch, unsigned int value_ms, void (*callback)(void));

void SwTimer_Stop(unsigned int ch);
unsigned long SwTimer_Get_Remaining_Time(unsigned int ch);

unsigned long SwTimer_Get_Cycle(void);

#endif  // SW_TIMER_H_INCLUDED
