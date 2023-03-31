
#include <genesis.h>
#include <resources.h>
#include "cup.h"

#define CUP_COUNT 10

Cup cups[CUP_COUNT];

int main()
{
    VDP_drawImage(BG_A, &img, 0, 0);

    SPR_init();

    PAL_setPalette(PAL3, spr_cup.palette->data, DMA);

    s16 index;
    for (index = 0; index < CUP_COUNT; index++)
    {
        s16 randomSpeedX = (random() % 5) + 1;
        s16 randomSpeedY = (random() % 5) + 1;
        Cup cup = {NULL, {0, 0}, {randomSpeedX, randomSpeedY}, {64, 64}};
        cup.sprite = SPR_addSprite(&spr_cup, cup.position.x, cup.position.y, TILE_ATTR(PAL3, 0, FALSE, FALSE));
        cups[index] = cup;
    }

    while (1)
    {
        for (index = 0; index < CUP_COUNT; index++)
        {
            Cup cup = cups[index];
            cup.position.x += cup.speed.x;
            cup.position.y += cup.speed.y;

            if (cup.position.x > 320 - cup.size.width || cup.position.x < 0)
            {
                cup.speed.x *= -1;
            }

            if (cup.position.y > 240 - cup.size.height || cup.position.y < 0)
            {
                cup.speed.y *= -1;
            }

            SPR_setPosition(cup.sprite, cup.position.x, cup.position.y);

            cups[index] = cup;
        }

        SPR_update();
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}