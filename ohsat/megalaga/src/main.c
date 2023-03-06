
#include <genesis.h>
#include <resources.h>
#include "entity.h"

#define MAX_ENEMIES 6

#define LEFT_EDGE 0
#define RIGHT_EDGE 320

#define PLAYER_ANIMATION_STRAIGHT 0
#define PLAYER_ANIMATION_MOVE 1

#define MAX_BULLETS 3

Entity player = {0, 0, 16, 16, 0, 0, 0, NULL, "PLAYER"};
Entity enemies[MAX_ENEMIES];
Entity bullets[MAX_BULLETS];

u16 enemiesLeft = 0;
u16 bulletsOnScreen = 0;

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
    int index = 0;
    Entity* enemy = enemies;
    for (index = 0; index < MAX_ENEMIES; index++)
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

void generateBullets()
{
    int index = 0;
    Entity* currentBullet = bullets;
    for (index = 0; index < MAX_BULLETS; index++)
    {
        currentBullet->pos.x = 0;
        currentBullet->pos.y = -10;
        currentBullet->size.w = currentBullet->size.h = 8;
        currentBullet->sprite = SPR_addSprite(&bullet, bullets[0].pos.x, bullets[0].pos.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
        sprintf(currentBullet->name, "Bu%d", index);
        currentBullet++;
    }
    
}

void moveEnemies()
{
    u16 index = 0;
    for (index = 0; index < MAX_ENEMIES; index++)
    {
        // Ponteiro para o item do array
        Entity* enemy = &enemies[index];
        if (enemy->health > 0)
        {
            if ((enemy->pos.x + enemy->size.w) > RIGHT_EDGE)
            {
                // Mover para esquerda
                enemy->vel.x = -1;
            }
            else if (enemy->pos.x < LEFT_EDGE)
            {
                // Mover para direita
                enemy->vel.x = 1;
            }

            enemy->pos.x += enemy->vel.x;
            SPR_setPosition(enemy->sprite, enemy->pos.x, enemy->pos.y);
        }
    }
}

void movePlayer()
{
    player.pos.x += player.vel.x;

    if (player.pos.x < LEFT_EDGE)
    {
        player.pos.x = LEFT_EDGE;
    }

    if (player.pos.x + player.size.w > RIGHT_EDGE)
    {
        player.pos.x = RIGHT_EDGE - player.size.w;
    }

    SPR_setPosition(player.sprite, player.pos.x, player.pos.y);
}

void moveBullets()
{
    u16 index = 0;
    Entity *currentBullet;
    for (index = 0; index < MAX_BULLETS; index++)
    {
        currentBullet = &bullets[index];
        if (currentBullet->health > 0)
        {
            currentBullet->pos.y += currentBullet->vel.y;

            if (currentBullet->pos.y + currentBullet->size.h < 0)
            {
                killEntity(currentBullet);
                bulletsOnScreen--;
            }
            else
            {
                SPR_setPosition(currentBullet->sprite, currentBullet->pos.x, currentBullet->pos.y);
            }
        }
    }
}

void shootBullet()
{
    if (bulletsOnScreen < MAX_BULLETS)
    {
        Entity *currentBullet;
        u16 index = 0;
        for (index = 0; index < MAX_BULLETS; index++)
        {
            currentBullet = &bullets[index];
            if (currentBullet->health == 0)
            {
                currentBullet->pos.x = player.pos.x + 4;
                currentBullet->pos.y = player.pos.y;

                reviveEntity(currentBullet);
                currentBullet->vel.y = -3;

                SPR_setPosition(currentBullet->sprite, currentBullet->pos.x, currentBullet->pos.y);
                bulletsOnScreen++;
                break;
            }
        }
    }
}

void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if (state & BUTTON_RIGHT)
        {
            player.vel.x = 2;
            SPR_setAnim(player.sprite, PLAYER_ANIMATION_MOVE);
            SPR_setHFlip(player.sprite, TRUE);
        }
        else if (state & BUTTON_LEFT)
        {
            player.vel.x = -2;
            SPR_setAnim(player.sprite, PLAYER_ANIMATION_MOVE);
            SPR_setHFlip(player.sprite, FALSE);
        }
        else
        {
            if ((changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT))
            {
                player.vel.x = 0;
                SPR_setAnim(player.sprite, PLAYER_ANIMATION_STRAIGHT);
            }
        }

        if (state & BUTTON_B & changed)
        {
            VDP_drawText("Pressed", 0, 0);
            shootBullet();
        }
    }
}

int main()
{
    JOY_init();
    JOY_setEventHandler(&myJoyHandler);

    SYS_disableInts();

    VDP_loadTileSet(background.tileset, 1, DMA);
    PAL_setPalette(PAL1, background.palette->data, DMA);
    PAL_setPalette(PAL2, background.palette->data, DMA);

    SPR_init();
    initPlayer();
    SPR_update();

    generateEnemies();
    generateBullets();

    // Indexes for PAL2 = 32-47
    PAL_setColor(34, RGB24_TO_VDPCOLOR(0x0078f8));

    int offset = 0;
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    while (1)
    {
        VDP_setVerticalScroll(BG_B, offset -= 2);
        if (offset <= -256)
            offset = 0;

        // generateStarsTiles();

        movePlayer();
        moveBullets();
        moveEnemies();

        SPR_update();
        SYS_doVBlankProcess();
    }

    SYS_enableInts();

    return (0);
}