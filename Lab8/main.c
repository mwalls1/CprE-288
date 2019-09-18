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
#include "Servo.h"
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include <string.h>
#include <stdio.h>

/**
 * main.c
 * Prints the button that has been pressed
 */
double degrees = 0;
int clockwise = 1;
char direction[20] = "";
volatile int button_event = 0; // Boolean to keep track of whether a hardware event has happened (button pressed)
volatile int button_num = 0; // keeps track of button pressed
void main(void)
 {
    lcd_init();
    servo_init();
    button_init();
    init_button_interrupts(&button_event, &button_num);

    servo_move(90);
    degrees = 90;
    while(1)
    {
        if(clockwise ==0)
        {
            strcpy(direction, "Clockwise");
        }
        else if(clockwise == 1)
        {
            strcpy(direction, "Counter-Clockwise");
        }

        lcd_printf("%f\n%s",degrees, direction);

        if (button_num == 6)
        {
            servo_move(180);
            degrees = 180;
        }
        if (button_num == 5)
        {
            servo_move(0);
            degrees = 0;
        }
        if(button_num==4)
        {
            if(clockwise==1)
                clockwise=0;
            else
                clockwise=1;
            timer_waitMillis(300);
        }
        if(button_num==3)
        {
            if(clockwise==1&&degrees<176)
            {
                degrees+=5;
                servo_move(degrees);
            }
            else if(clockwise==1&&degrees>175)
            {
                servo_move(180);
                degrees=180;
            }
            else if(clockwise==0&&degrees<5)
            {
                servo_move(0);
                degrees = 0;
            }
            else if(clockwise==0&&degrees>4)
            {
                degrees-=5;
                servo_move(degrees);

            }
            timer_waitMillis(300);
        }
        if(button_num==2)
        {
            if(clockwise==1&&degrees<177.5)
            {
                degrees+=2.5;
                servo_move(degrees);
            }
            else if(clockwise==1&&degrees>=177.5)
            {
                servo_move(180);
                degrees=180;
            }
            else if(clockwise==0&&degrees<=2.5)
            {
                servo_move(0);
                degrees = 0;
            }
            else if(clockwise==0&&degrees>2.5)
            {
                degrees-=2.5;
                servo_move(degrees);

            }
            timer_waitMillis(300);
        }
        if(button_num==1)
                {
                    if(clockwise==1&&degrees<179)
                    {
                        degrees+=1;
                        servo_move(degrees);
                    }
                    else if(clockwise==1&&degrees>=179)
                    {
                        servo_move(180);
                        degrees=180;
                    }
                    else if(clockwise==0&&degrees<=1)
                    {
                        servo_move(0);
                        degrees = 0;
                    }
                    else if(clockwise==0&&degrees>1)
                    {
                        degrees-=1;
                        servo_move(degrees);

                    }
                    timer_waitMillis(300);
                }
    }


}
