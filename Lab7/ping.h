
#ifndef PING_H_
#define PING_H_


#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

void ping_init(void);
void ping_read(void);
void send_pulse();
void getData(int *timeOne, int *timeTwo);
void TIMER3B_Handler();
#endif
