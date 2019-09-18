#include "lcd.h"
#include "movement.h"
#include "open_interface.h"

/**
 * main.c
 *
 * Simple 'Hello, world program'.
 * This program prints "Hello, world" to the LCD screen
 *      Author: Mason Walls
 *      Author: Abdalla Abdelrahman
 *      Author: Michael Mazur
 */
int main(void)
{
    lcd_init();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    bump(sensor_data, 200);

    oi_free(sensor_data);
    return 0;
}

