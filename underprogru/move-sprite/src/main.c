
#include <genesis.h>
#include <resources.h>

Sprite *obj_cup;
s16 x = 0;
s16 y = 0;
s16 x_speed = 3;
s16 y_speed = 4;
u16 cup_width = 64;
u16 cup_height = 64;

int main()
{
    VDP_drawImage(BG_A, &img, 0, 0);

    SPR_init();

    // set the colors from cup/mug sprite on the 4th palette
    PAL_setPalette(PAL3, spr_cup.palette->data, DMA);

    obj_cup = SPR_addSprite(&spr_cup, x, y, TILE_ATTR(PAL3, 0, FALSE, FALSE));

    while (1)
    {
        // Add speed to position
        x += x_speed;
        y += y_speed;

        // check boundaries of screen
        if (x > 320 - cup_width || x < 0)
        {
            x_speed *= -1;
        }

        // check boundaries of screen
        if (y > 240 - cup_height || y < 0)
        {
            y_speed *= -1;
        }

        // update position
        SPR_setPosition(obj_cup, x, y);

        SPR_update();
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}