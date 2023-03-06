#include <genesis.h>
#include <string.h>
#include "position.h"
#include "velocity.h"
#include "size.h"

#ifndef _ENTITY_H_
#define _ENTITY_H_

typedef struct
{
    Position pos;
    Size size;
    Velocity vel;
    int health;
    Sprite *sprite;
    char name[6];

} Entity;

#endif // _ENTITY_H_