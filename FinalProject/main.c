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
//(19356) * pow(adc_read(), -.861); //Cybot 0
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
void test1(void);
int main(void)
{
    uart_init();
    uart_sendStr("Start");
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    //test1();
    lcd_init();
    int start = 0;
    uart_sendStr("Start");
    while (start == 0)
    {
        char uReceive = uart_receive();
        if(uReceive == 'b'){
            start = 1;
        }
    }
      while(start == 1){
          char uReceive = uart_receive();
      if (uReceive == 'r'){
          test1();


      }
      else if (uReceive == 'w'){
                move_forward(sensor_data, 5);
                uReceive = NULL;
                oi_free(sensor_data);
                oi_init(sensor_data);
            }
      else if (uReceive == 'd'){
              turn_right(sensor_data, 15);
              uReceive = NULL;
           oi_free(sensor_data);
           oi_init(sensor_data);
      }
      else if(uReceive == 'a'){
          turn_left(sensor_data, 15);
                 uReceive = NULL;
              oi_free(sensor_data);
              oi_init(sensor_data);
    }
      else if(uReceive == 'm'){

          int songIndex = 1;
          int numNotes = 27;

          unsigned char notes2[] = {43,43,46,48, 43,43,41, 42, 43,43,46,48, 43,43,41, 42, 82,79,74,82,79,73,82,79,72,70,72};
           unsigned char duration2[] = {32,32,24,32,32,32,32,24, 32,32,24,32,32,32,32,32,16,16,128,16,16,128,16,16,128,16,16};
                  oi_loadSong(songIndex, numNotes, notes2, duration2);
           oi_play_song(songIndex);
      }
    }

    return 0;

    }
/*

    int songIndex = 1;
    int numNotes = 27;

   unsigned char notes[] = {43,43,46,48, 43,43,41, 42, 43,43,46,48, 43,43,41, 42, 82,79,74,82,79,73,82,79,72,70,72};
    unsigned char duration[] = {32,32,24,32,32,32,32,24, 32,32,24,32,32,32,32,32,16,16,128,16,16,128,16,16,128,16,16};
   unsigned char notes2[] = {77,30,77,79,30,79,80,30,80,30,77,30,77,84,30,84,80,30,80,30,77,30,77,79,30,79,77,30,77};
           unsigned char duration2[] = {12,12,24,12,12,24,12,12,28,28,12,12,24,12,12,24,12,12,24,12,16,12,24,12,12,24,12,12,24};



    unsigned char notes2[] = {83,76,71,83,76,71,83,76,83,76,71,83,76,71,83,76,84,76,72,84,76,72,84,76,86,76,72,84,76,72,84,76};
     unsigned char duration2[] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15};
     oi_loadSong(songIndex, numNotes, notes, duration);

         oi_play_song(songIndex);
*/



int compare(int tol, double ir, double sonar)
{
    if ((sonar >= (ir - tol)) && (sonar <= (ir + tol)))
        return 1;
    else
        return 0;
}

void test1(void)
{
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
    int i = 0;
    servo_move(0);
    timer_waitMillis(200);
    for (i = 0; i < 181; i++)
    {
        servo_move(i);
        calcDist = (157709) * pow(adc_read(), -1.213); //CYBOT 11
        sonarDist = ping_read();
        reading_array[i].ir_distance = calcDist;
        reading_array[i].sonar_distance = sonarDist;
        ;
        if (reading_array[i].ir_distance < 48 && !hasFirstEdge && i != 0)
        {
            object_array[numObjects].startDeg = i;
            hasFirstEdge = 1;
        }
        else if (reading_array[i].ir_distance > 48 && hasFirstEdge)
        {
            hasFirstEdge = 0;
            object_array[numObjects].endDeg = i;
            numObjects++;
        }
        timer_waitMillis(25);
    }
    for (i = 0; i < numObjects; i++)
    {
        int totDeg = (object_array[i].startDeg + object_array[i].endDeg);
        int regDeg = (object_array[i].endDeg - object_array[i].startDeg);
        object_array[i].distance = reading_array[totDeg / 2].sonar_distance;
        width[i] = ((double)regDeg/180.0)*(3.14*object_array[i].distance);
    }
    if (numObjects > 0)
    {
        int min = width[0];
        for (i = 1; i < numObjects; i++)
        {
            if (width[i] < min)
            {
                min = width[i];
                smallest = i;
            }
        }
        servo_move(object_array[smallest].startDeg);
    }
    else
    {
        servo_move(0);
    }
    for (i = 0; i < numObjects; i++)
    {
        sprintf(sendstr, "%f ", width[i]);
        uart_sendStr(sendstr);
    }
    sprintf(sendstr, "\n");
    uart_sendStr(sendstr);
    for (i = 0; i < numObjects; i++)
    {
        sprintf(sendstr, "%d ", object_array[i].distance);
        uart_sendStr(sendstr);
    }
    sprintf(sendstr, "\n");
    uart_sendStr(sendstr);
    for (i = 0; i < numObjects; i++)
    {
        sprintf(sendstr, "%d %d ", object_array[i].startDeg,
                object_array[i].endDeg);
        uart_sendStr(sendstr);
    }
    sprintf(sendstr, "\n");
    uart_sendStr(sendstr);
    sprintf(sendstr, "#");
    uart_sendStr(sendstr);
}
