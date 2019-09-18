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

/**
 * main.c
 * Prints the button that has been pressed
 */

int main(void) {
    // delete warning after implementing
    // Hint: You may need to use pointers to return the button that has been pressed
    //oi_t *sensor_data = oi_alloc();
    //oi_init(sensor_data);
    adc_init();
    lcd_init();
    uart_init();
    double irDat = 0;
    double calcDist = 0;
    char sendstr[65];
    char string2[65];

       // prepare the header
    sprintf(sendstr, "%-20s%-20s\r\n", "Distance", "Quantized Value");
          uart_sendStr(sendstr);
    while(1)
    {
        irDat = adc_read();
        calcDist = 105447 * pow(irDat, -1.159);
        sprintf(sendstr, "%-20f%-20f\r\n",irDat, calcDist);
        uart_sendStr(sendstr);
        timer_waitMillis(1000);
    }

    /*oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    double data[2][10];
    int i = 0;
    double distance = 0;
    for(i; i < 10; i++)
    {
        data[0][i] = 9 + distance/10;
        data[1][i] = adc_read();
        move_backwards(sensor_data, 41);
        distance+=41;
        timer_waitMillis(1000);
    }
    oi_free(sensor_data);
    int j = 0;
    int k = 0;
    for(k = 0; k < 2; k++)
    {
        for(j = 0; j < 10; j++)
        {
            sprintf(string2, "%-20f%-20f\r\n",data[k], data[1][j]);
            uart_sendStr(string2);
            printf("%f    %f\n", data[k], data[1][j]);

        }
    }*/
}
