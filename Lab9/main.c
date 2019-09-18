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
#include "Servo.h"
#include "math.h"
#include "cyBot_Sonar.h"



struct reading
{
    double ir_distance;
    double sonar_distance;
};

struct object
{
    int distance;
    int startDeg;
    int endDeg;
};

int compare(int tol, double ir, double sonar);
/**
 * main.c
 * Prints the button that has been pressed
 * CYBOT 8
 */


int main(void) {
    // delete warning after implementing
    // Hint: You may need to use pointers to return the button that has been pressed
    //oi_t *sensor_data = oi_alloc();
    //oi_init(sensor_data);
    adc_init();
    lcd_init();
    uart_init();
    servo_init();
    TIMER3B_init();
    double calcDist = 0;
    char sendstr[65];
    double sonarDist = 0;
    int numObjects = 0;
    struct reading reading_array[181];
    struct object object_array[10];
    double width[5];
    int hasFirstEdge = 0;
    int smallest = 0;
    // prepare the header
    sprintf(sendstr, "%-20s%-20s%-20s\r\n", "Degrees", "IR Distance (cm)", "Sonar Distance (cm)");
    uart_sendStr(sendstr);
    int i = 0;
    servo_move(0);
    timer_waitMillis(200);
    for (i = 0; i < 181; i++)
    {
        servo_move(i);
        calcDist = (96412) * pow(adc_read(), -1.142); //CYBOT 7
        sonarDist = ping_read();
        reading_array[i].ir_distance = calcDist;
        reading_array[i].sonar_distance = sonarDist;
        sprintf(sendstr, "%-20d%-20f%-20f\r\n", i, reading_array[i].ir_distance,
        reading_array[i].sonar_distance);
        uart_sendStr(sendstr);
        if (reading_array[i].ir_distance < 51 && compare(17, reading_array[i].ir_distance,reading_array[i].sonar_distance) && !hasFirstEdge && i != 0)
        {
            object_array[numObjects].startDeg = i;
            hasFirstEdge = 1;
        }
        else if (reading_array[i].ir_distance > 50 && hasFirstEdge)
        {
            hasFirstEdge = 0;
            object_array[numObjects].endDeg = i-1;
            numObjects++;
        }
        timer_waitMillis(200);
    }
    for(i = 0; i < numObjects; i++)
    {
        int totDeg = (object_array[i].startDeg+object_array[i].endDeg);
        int regDeg = (object_array[i].endDeg-object_array[i].startDeg);
        object_array[i].distance = reading_array[totDeg/2].sonar_distance;
        width[i] = ((((double)regDeg)/360.0)*(2.0*3.14*object_array[i].distance));
    }
    if(numObjects>0)
    {
        int min = width[0];
        for(i = 1; i < numObjects; i++)
        {
            if(width[i]<min)
            {
                min = width[i];
                smallest = i;
            }
        }
        sprintf(sendstr,"%d Objects Found. Smallest Object: %f, At %d degrees",numObjects, width[smallest],object_array[smallest].startDeg);
        uart_sendStr(sendstr);
        servo_move(object_array[smallest].startDeg);
    }
    else
    {
        sprintf(sendstr,"No objects found");
        servo_move(0);
    }

    /*while(1)
    {
       // servo_move(90);
        pulse();
        sonarDist = dist_time();
        irDat = adc_read();
        calcDist = (8840.9)*pow(irDat, -.914); //CYBOT 8
        lcd_printf("IR: %d\nSONAR: %d",calcDist,sonarDist);
        timer_waitMillis(1000);
    }*/
}
int compare(int tol, double ir, double sonar)
{
    if((sonar>=(ir-tol))&&(sonar<=(ir+tol)))
            return 1;
        else
            return 0;
}
