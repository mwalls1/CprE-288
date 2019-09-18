#ifndef ADC_H_
#define ADC_H_


#include "UART.h"
#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "movement.h"
#include "open_interface.h"

void adc_init(void);
int adc_read(void);

#endif
