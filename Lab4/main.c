/**
 * main.c
 * @author:
 * @date:
 */

#include "lcd.h"
#include "button.h"
#include "uart.h"



/**
 * main.c
 * Prints the button that has been pressed
 */

int main(void) {
    // delete warning after implementing
    // Hint: You may need to use pointers to return the button that has been pressed
  uart_init();
    lcd_init();
    init_uart_interrupts();
}
