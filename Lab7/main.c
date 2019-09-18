/**
 * main.c
 * @author:
 * @date:
 */
//Bot 4
#include "lcd.h"
#include "button.h"
#include "uart.h"
#include "adc.h"
#include "open_interface.h"
#include "movement.h"
#include "math.h"
#include "ping.h"

/**
 * main.c
 * Prints the button that has been pressed
 */

int main(void) {
    int time1;
    int time2;
    ping_init();
    lcd_init();
    send_pulse();
    getData(&time1, &time2);
    lcd_printf("Time 1: %d\n Time 2: %d",time1, time2);


    return 0;
}
