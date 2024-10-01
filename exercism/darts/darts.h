#ifndef DARTS_H
#define DARTS_H

#include <math.h>
#include <stdlib.h>

typedef struct
{
    float x;
    float y;
} coordinate_t;

unsigned int score(coordinate_t landing_position);

#endif
