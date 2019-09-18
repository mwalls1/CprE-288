/*
 * movement.c
 *
 *  Created on: Feb 5, 2019
 *      Author: Mason Walls
 *      Author: Abdalla Abdelrahman
 *      Author:  Michael Mazur
 */
#include "movement.h"
//#include "open_interface.h"

int move_forward(oi_t *sensor, int centimeters)
{
    int sum = 0;
    oi_setWheels(500, 500);
    while (sum < centimeters * 10)
    {
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
    oi_setWheels(-500, -500);
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

void bump(oi_t *sensor, int centimeters){
    int sum = 0;

     while (sum < centimeters * 10)
     {
         oi_setWheels(500, 500);
         if(sensor -> bumpLeft){
             oi_setWheels(0,0);
             move_backwards(sensor, 15);
             sum -= 150;
             turn_right(sensor, 90);
             move_forward(sensor, 25);
             oi_setWheels(0,0);
             turn_left(sensor, 90);
         }
         if(sensor -> bumpRight){
                     oi_setWheels(0,0);
                     move_backwards(sensor, 15);
                     sum -= 150;
                     turn_left(sensor, 90);
                     move_forward(sensor, 25);
                     oi_setWheels(0,0);
                     turn_right(sensor, 90);
                 }
         oi_update(sensor);
         sum += sensor->distance;
     }

}


