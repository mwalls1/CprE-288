#ifndef PING_H_

#include "lcd.h"
#include "timer.h"
#include <stdbool.h>
#include "driverlib/interrupt.h"
/*

enum {LOW, HIGH, DONE} state;
unsigned int overflow = 0;
unsigned int rising_time = 0; // start time of the return pulse
unsigned int falling_time = 0 ; // end time of the return pulse
*/



void ping_init(void);
void clock_timer_init(void) ;
void TIMER3B_Handler(void);
void pulse(void);
void dist_time(void);

#endif
