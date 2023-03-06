
#include <genesis.h>
#include <resources.h>
#include "entity.h"

#define MAX_ENEMIES 6

Entity player = {0, 0, 16, 16, 0, 0, 0, NULL, "PLAYER"};
Entity enemies[MAX_ENEMIES];

u16 enemiesLeft = 0;

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
    int index = 0;
    for (index = 0; index < 1280; index++)
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

void generateEnemies()
{
    Entity* enemy = enemies;
    for (int index = 0; index < MAX_ENEMIES; index++)
    {
        enemy->pos.x = index * 32;
        enemy->pos.y = 32;
        enemy->size.w = enemy->size.h = 16;
        enemy->vel.x = 1;
        enemy->health = 1;
        enemy->sprite = SPR_addSprite(&ship, enemy->pos.x, enemy->pos.y, TILE_ATTR(PAL2, 0, TRUE, FALSE));
        sprintf(enemy->name, "En%d", index);

        enemiesLeft++;
        enemy++;
    }
}

int main()
{
    SYS_disableInts();

    VDP_loadTileSet(background.tileset, 1, DMA);
    PAL_setPalette(PAL1, background.palette->data, DMA);
    PAL_setPalette(PAL2, background.palette->data, DMA);

    SPR_init();
    initPlayer();
    SPR_update();

    generateEnemies();

    // Indexes for PAL2 = 32-47
    PAL_setColor(34, RGB24_TO_VDPCOLOR(0x0078f8));

    int offset = 0;
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    while (1)
    {
        VDP_setVerticalScroll(BG_B, offset -= 2);
        if (offset <= -256)
            offset = 0;

        generateStarsTiles();

        SPR_update();
        SYS_doVBlankProcess();
    }

    SYS_enableInts();

    return (0);
}