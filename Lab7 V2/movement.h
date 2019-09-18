/*
 * movement.h
 *
 *  Created on: Feb 5, 2019
 *      Author: Mason
 *      Author: Abdalla Abdelrahman
 *      Author:  Michael Mazur
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_
#include "open_interface.h"

int move_forward(oi_t *sensor, int centimeters);
void turn_right(oi_t *sensor, int degrees);
void turn_left(oi_t *sensor, int degrees);
int move_backwards(oi_t *sensor, int centimeters);
void turn_left(oi_t *sensor, int degrees);
void bump(oi_t *sensor, int centimeters);

#endif /* MOVEMENT_H_ */
