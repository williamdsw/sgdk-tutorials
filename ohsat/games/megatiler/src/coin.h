#include <genesis.h>
#include "point.h"
#include "size.h"

#ifndef _COIN_H_
#define _COIN_H_

typedef struct
{
    Point position;
    Size size;
    Sprite *sprite;
    u8 health;
} Coin;

#endif // _COIN_H_