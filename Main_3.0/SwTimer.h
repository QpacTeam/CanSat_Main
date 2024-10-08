#ifndef SW_TIMER_H_INCLUDED
#define SW_TIMER_H_INCLUDED

extern void SwTimer_Init(unsigned long ticktime);
extern void SwTimer_Run(void);

extern void SwTimer_Set_Single(unsigned int ch, unsigned int value_ms, void (*callback)(void));
extern void SwTimer_Set_Continues(unsigned int ch, unsigned int value_ms, void (*callback)(void));
extern void SwTimer_Stop(unsigned int ch);
extern unsigned long SwTimer_Get_Remaining_Time(unsigned int ch);

#endif  // SW_TIMER_H_INCLUDED
