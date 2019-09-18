#include "open_interface.h"
int *fRight_sense;
int *fLeft_sense;
int *right_sense;
int *left_sense;
void cliff_detect(oi_t*sensor, int *Fright, int *Fleft, int *Bright, int *Bleft)
{
    fRight_sense = Fright;
    fLeft_sense = Fleft;
    right_sense = Bright;
    left_sense = Bleft;
    oi_update(sensor);
    *fRight_sense = sensor -> cliffFrontRightSignal;
    *fLeft_sense = sensor -> cliffFrontLeftSignal;
    *right_sense = sensor -> cliffRightSignal;
    *left_sense = sensor -> cliffLeftSignal;
}
