#ifndef _PLAYER_PROPS_H
#define _PLAYER_PROPS_H

#ifndef PLAYER_ANIMATION_RUN
#define PLAYER_ANIMATION_RUN 0
#endif

#ifndef PLAYER_ANIMATION_JUMP
#define PLAYER_ANIMATION_JUMP 1
#endif

#ifndef PLAYER_POSITION_X
#define PLAYER_POSITION_X 32
#endif

typedef struct
{
    fix16 positionY;
    fix16 velocityY;
    int height;

} PlayerProps;

#endif // _PLAYER_PROPS_H