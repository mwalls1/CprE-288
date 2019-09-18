/**
 * main.c
 * @author:
 * @date:
 */

#include "lcd.h"
#include "button.h"
#include "uart.h"
#include "lab5_scan_data.h"


/**
 * main.c
 * Prints the button that has been pressed
 */

int main(void) {
    // delete warning after implementing
    // Hint: You may need to use pointers to return the button that has been pressed
  uart_init();
    lcd_init();

    struct reading reading_array[181];

    get_reading("dataset3.csv", reading_array);

    //get_reading("dataset2.csv", &reading_array);
    //get_reading("dataset3.csv", &reading_array);

    char sendstr[65];

    // prepare the header
       sprintf(sendstr, "%-20s%-20s%-20s\r\n", "Degrees", "IR Distance (cm)", "Sonar Distance(cm)");
       // send the header
       uart_sendStr(sendstr);
       int i = 0;
       for(i = 0; i < 181; i ++)
       {
           sprintf(sendstr, "%-20d%-20f%-20f\r\n",i, reading_array[i].ir_distance, reading_array[i].sonar_distance);
           uart_sendStr(sendstr);
       }
}
