#ifndef _BALL_PROPS_H_
#define _BALL_PROPS_H_

#ifndef BALL_WIDTH
#define BALL_WIDTH 8
#endif

#ifndef BALL_HEIGHT
#define BALL_HEIGHT 8
#endif

typedef struct
{
    int x;
    int y;
} Position;

typedef struct
{
    int x;
    int y;
} Velocity;

typedef struct
{
    Position position;
    Velocity velocity;
    int frames;
    int color;
    bool isFlashing;

} BallProps;

#endif // _BALL_PROPS_H_