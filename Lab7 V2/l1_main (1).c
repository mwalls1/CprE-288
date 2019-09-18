#include "lcd.h"
#include "movement.h"
#include "button.h"
#include "uart.h"
#include "lab5_scan_data.h"
#include "adc.h"
#include "ping.h"

extern volatile int data;
extern volatile int OF;

int main(void)
{
    //Initialize the LCD. This also clears the screen
    lcd_init();
   // button_init();
    //uart_init();
    //adc_init();
    ping_init();
   // clock_timer_init();
    while(1)
    {
     //timer_waitMillis(5);
     pulse();
 dist_time(); //part 3

  // lcd_printf("time is: %d\noverflow: %d", data, OF);//Comment out for part 3
    }

	return 0;
}

