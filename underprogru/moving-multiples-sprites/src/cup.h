#include <genesis.h>
#include "vector.h"
#include "size.h"

#ifndef _CUP_H_
#define _CUP_H_

typedef struct
{
    Sprite *sprite;
    Vector position;
    Vector speed;
    Size size;
} Cup;

#endif // _CUP_H_