#include <genesis.h>
#include "point.h"
#include "size.h"
#include "move_direction.h"

#ifndef _ENTITY_H_
#define _ENTITY_H_

typedef struct
{
    Point position;
    Point tilePosition;
    Size size;
    int health;
    bool isMoving;
    MoveDirection moveDirection;
    Sprite *sprite;
    char name[6];
} Entity;

#endif // _ENTITY_H_