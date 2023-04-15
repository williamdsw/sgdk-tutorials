#include <genesis.h>
#include "point.h"
#include "size.h"

#ifndef _PLAYER_H_
#define _PLAYER_H_

typedef struct
{
    bool isMoving;
    bool isOnFloor;
    Point position;
    Point speed;
    Size size;
    Sprite *sprite;
} Player;

#endif // _PLAYER_H_