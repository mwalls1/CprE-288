/*
 * movement.c
 *
 *  Created on: Feb 5, 2019
 *      Author: Mason Walls
 *      Author: Abdalla Abdelrahman
 *      Author:  Michael Mazur
 */
#include "movement.h"
#include "open_interface.h"
#include "cliff_detect.h"
#include "uart.h"

int move_forward(oi_t *sensor, int centimeters)
{
    int speedL = 120;
    int speedR = 100;
    int fRight;
    int fLeft;
    int right;
    int left;
    int sum = 0;
    oi_setWheels(speedR, speedL);
    while (sum < centimeters * 10)
    {
        cliff_detect(sensor, &fRight, &fLeft,&right,&left);


        if (right > 2700 || left > 2700 || right < 700 || left < 700 || fRight > 2700 || fLeft > 2700 || fRight < 700 || fLeft < 700)
        {
            if(right > 2700 || left > 2700 || fRight > 2700 || fLeft > 2700){
            uart_sendStr("boundary");
            }
           if(right < 700 || left < 700 || fRight < 700 || fLeft < 700){
               uart_sendStr("cliff");
           }
            oi_setWheels(0, 0);
            oi_update(sensor);
            move_backwards(sensor, 5);
            turn_right(sensor, 90);
            break;

        }

        else if(sensor -> bumpLeft){
            uart_sendStr("bumpLeft");
            oi_setWheels(0,0);

            move_backwards(sensor, 5);
            turn_right(sensor, 90);
            oi_setWheels(100, 100);

            break;

        }
        else  if (sensor->bumpRight)
        {
            uart_sendStr("bumpRight");

            oi_setWheels(0, 0);
            move_backwards(sensor,5);
            turn_left(sensor, 90);
            oi_setWheels(100,100);

            break;
        }
        else
        {
            uart_sendStr(" ");
        }

        oi_update(sensor);
        sum += sensor->distance;
    }
    return sum;
}

void turn_right(oi_t *sensor, int degrees)
{
    int num = 0;
    while (num < degrees)
    {
        oi_update(sensor);
        oi_setWheels(-100, 100);
        num += -(sensor->angle);
    }
    oi_setWheels(0, 0);
}
int move_backwards(oi_t *sensor, int centimeters)
{
    int sum = centimeters*10;
    oi_setWheels(-100, -100);
    while (sum > 0)
    {
        oi_update(sensor);
        sum += sensor->distance;
    }
    oi_setWheels(0, 0);
    return sum;
}

void turn_left(oi_t *sensor, int degrees)
{

    int turnedDeg = 0;
    while (turnedDeg < degrees)
    {
        oi_update(sensor);
        oi_setWheels(100, -100);
        turnedDeg += sensor->angle;

    }
    oi_setWheels(0, 0);
}

void bump(oi_t *sensor, int centimeters)
{
    int sum = 0;

    while (sum < centimeters * 10)
    {
        oi_setWheels(100, 100);
        if (sensor->bumpLeft)
        {
            oi_setWheels(0, 0);
            move_backwards(sensor, 15);
            sum -= 150;
            turn_right(sensor, 90);
            move_forward(sensor, 25);
            oi_setWheels(0, 0);
            turn_left(sensor, 90);
        }
        if (sensor->bumpRight)
        {
            oi_setWheels(0, 0);
            move_backwards(sensor, 15);
            sum -= 150;
            turn_left(sensor, 90);
            move_forward(sensor, 25);
            oi_setWheels(0, 0);
            turn_right(sensor, 90);
        }
        oi_update(sensor);
        sum += sensor->distance;
    }

}


