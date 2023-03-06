
#include <genesis.h>
#include <resources.h>
#include "entity.h"

Entity player = {0, 0, 16, 16, 0, 0, 0, NULL, "PLAYER"};

void initPlayer()
{
    player.pos.x = 152;
    player.pos.y = 192;
    player.health = 1;
    player.sprite = SPR_addSprite(&ship, player.pos.x, player.pos.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
}

void killEntity(Entity *entity)
{
    entity->health = 0;
    SPR_setVisibility(entity->sprite, HIDDEN);
}

void reviveEntity(Entity *entity)
{
    entity->health = 1;
    SPR_setVisibility(entity->sprite, VISIBLE);
}

void generateStarsTiles()
{
    for (int index = 0; index < 1280; index++)
    {
        int thex = index % 40;
        int they = index / 40;

        // (max - min + 1) + min
        int value = (random() % (10 - 1 + 1)) + 1;

        if (value > 3)
            value = 1;

        VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, value), thex, they);
    }
}

int main()
{
    SYS_disableInts();

    VDP_loadTileSet(background.tileset, 1, DMA);
    PAL_setPalette(PAL1, background.palette->data, DMA);

    SPR_init();
    initPlayer();
    SPR_update();

    int offset = 0;
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    while (1)
    {
        VDP_setVerticalScroll(BG_B, offset -= 2);
        if (offset <= -256)
            offset = 0;

        // generateStarsTiles();

        SPR_update();
        SYS_doVBlankProcess();
    }

    SYS_enableInts();

    return (0);
}