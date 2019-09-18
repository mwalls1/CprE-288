/**
 * main.c
 * @author:
 * @date:
 */

#include "lcd.h"
#include "button.h"

volatile int button_event = 0; // Boolean to keep track of whether a hardware event has happened (button pressed)
volatile int button_num = 0; // keeps track of button pressed

/**
 * main.c
 * Prints the button that has been pressed
 */
int main(void) {
    // delete warning after implementing
    // Hint: You may need to use pointers to return the button that has been pressed
    button_init();
    init_button_interrupts(&button_event, &button_num);
    lcd_init();
    while(1)
    {
        if(button_event == 1){
        lcd_printf("%d",button_num);
        }
    }


}
