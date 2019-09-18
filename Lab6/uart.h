
#ifndef UART_H_
#define UART_H_


#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"



void uart_init(void);
void uart_sendChar(char data);
char uart_receive(void);
void UART1_Handler(void);
void init_uart_interrupts();
void uart_sendStr(const char *data);

#endif
