#ifndef SERVO_H_

#include "lcd.h"
#include "timer.h"
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
void servo_init(void);
void servo_move(double degrees);

#endif
