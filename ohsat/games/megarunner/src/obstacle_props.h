#ifndef _OBSTACLE_PROPS_H
#define _OBSTACLE_PROPS_H

#include "position.h"
#include "velocity.h"

typedef struct
{
    Position position;
    Velocity velocity;

} ObstacleProps;

#endif // _OBSTACLE_PROPS_H