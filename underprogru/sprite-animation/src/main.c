#include <genesis.h>
#include <resources.h>

#define ANIM_STAND 0
#define ANIM_WALK 2

Sprite *object_sonic;
s16 x = 0;
s16 y = 180;
s16 max_x_speed = 3;
s16 current_speed_x = 0;
s16 sonic_width = 48;

void updateAnimation()
{
    if (current_speed_x == 0)
    {
        SPR_setAnim(object_sonic, ANIM_STAND);
    }
    else
    {
        SPR_setAnim(object_sonic, ANIM_WALK);
    }

    if (current_speed_x > 0)
    {
        SPR_setHFlip(object_sonic, FALSE);
    }
    else if (current_speed_x < 0)
    {
        SPR_setHFlip(object_sonic, TRUE);
    }
}

void handleInput()
{
    u16 value = JOY_readJoypad(JOY_1);
    current_speed_x = 0;

    if (value & BUTTON_LEFT)
    {
        current_speed_x = -max_x_speed;
    }
    else if (value & BUTTON_RIGHT)
    {
        current_speed_x = max_x_speed;
    }
}

int main()
{
    SPR_init();

    PAL_setPalette(PAL3, sprite_sonic.palette->data, DMA);
    object_sonic = SPR_addSprite(&sprite_sonic, x, y, TILE_ATTR(PAL3, 0, FALSE, FALSE));

    while (1)
    {
        handleInput();
        updateAnimation();

        x += current_speed_x;
        if (x > 320 - sonic_width)
        {
            x = 320 - sonic_width;
        }
        else if (x < 0)
        {
            x = 0;
        }

        SPR_setPosition(object_sonic, x, y);

        SPR_update();

        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}