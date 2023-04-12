#include <genesis.h>
#include "resources.h"
#include "defines.h"
#include "level.h"
#include "player.h"

Map *map;

Player player = {FALSE, FALSE, {0, 0}, {0, 0}, {0, 0}, NULL};

s16 cameraPositionX = -1;
s16 cameraPositionY = -1;

bool isPaused = FALSE;

bool checkCollision(s16 x, s16 y)
{
    player.isOnFloor = FALSE;

    s16 yTile = y >> 3;
    s16 xTile = x >> 3;

    s16 leftTile = xTile;
    s16 rightTile = xTile + player.size.w;
    s16 topTile = yTile;
    s16 bottomTile = yTile + player.size.h;

    for (s16 i = leftTile; i <= rightTile; i++)
    {
        for (s16 j = topTile; j <= bottomTile; j++)
        {
            if (level[j][i] == 0)
            {
                if (j == bottomTile)
                {
                    player.isOnFloor = TRUE;
                }

                return FALSE;
            }
        }
    }
    return TRUE;
}

void moveEntity()
{
    s16 posX = fix32ToInt(player.position.x);
    s16 posY = fix32ToInt(player.position.y);
    s16 spdX = fix32ToInt(player.speed.x);
    s16 spdY = fix32ToInt(player.speed.y);

    s16 testPosX;
    s16 testPosY;

    if (checkCollision(posX + spdX, posY + spdY) == 1)
    {
        posX += spdX;
        posY += spdY;
    }
    else
    {
        if (spdX)
        {
            testPosX = posX;
            if (spdX > 0)
            {
                for (u8 i = 1; i < spdX; i++)
                {
                    testPosX++;
                    if (checkCollision(testPosX, posY))
                    {
                        posX = testPosX;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                for (u8 i = spdX; i > 0; i++)
                {
                    testPosX--;
                    if (checkCollision(testPosX, posY))
                    {
                        posX = testPosX;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        if (spdY)
        {
            testPosY = posY;
            if (spdY > 0)
            {
                for (u8 i = 1; i < spdY; i++)
                {
                    testPosY++;
                    if (checkCollision(posX, testPosY))
                    {
                        posY = testPosY;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                for (u8 i = spdY; i > 0; i++)
                {
                    testPosY--;
                    if (checkCollision(posX, testPosY))
                    {
                        posY = testPosY;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    player.position.x = FIX32(posX);
    player.position.y = FIX32(posY);

    setCameraPosition(posX, posY);
}

void setCameraPosition(s16 x, s16 y)
{
    if ((x - 160 != cameraPositionX) || (y - 120 != cameraPositionY))
    {
        cameraPositionX = x - 160;
        cameraPositionY = y - 120;

        if (cameraPositionX < 0)
        {
            cameraPositionX = 0;
        }
        else if (cameraPositionX > MAX_X - 320)
        {
            cameraPositionX = MAX_X - 320;
        }
        if (cameraPositionY < 0)
        {
            cameraPositionY = 0;
        }
        else if (cameraPositionY > MAX_Y - 120)
        {
            cameraPositionY = MAX_Y - 120;
        }

        SPR_setPosition(player.sprite, x - cameraPositionX, y - cameraPositionY);
        MAP_scrollTo(map, cameraPositionX, cameraPositionY);
    }
}

void handleInput()
{
    u16 value = JOY_readJoypad(JOY_1);

    if (!isPaused && !player.isMoving)
    {
        player.speed.x = 0;

        if (!player.isOnFloor)
        {
            player.speed.y += FIX32(1);
        }
        else
        {
            player.speed.y = 0;
        }

        if (value & BUTTON_RIGHT)
        {
            player.speed.x = FIX32(5);
        }
        else if (value & BUTTON_LEFT)
        {
            player.speed.x = FIX32(-5);
        }

        if (value & BUTTON_UP)
        {
            if (player.isOnFloor)
            {
                player.speed.y = FIX32(-10);
            }
        }
    }
}

int main()
{
    player.isMoving = FALSE;
    player.isOnFloor = FALSE;
    player.position.x = FIX32(160);
    player.position.y = FIX32(950);
    player.speed.x = 0;
    player.speed.y = 0;
    player.size.h = 4;
    player.size.w = 4;

    u16 ind = TILE_USER_INDEX;

    VDP_loadTileSet(&tilesetBG, ind, DMA);
    map = MAP_create(&mapBG, BG_B, TILE_ATTR_FULL(0, FALSE, FALSE, FALSE, ind));

    PAL_setColors(0, paletteBG.data, 16 * 2, DMA);
    SPR_init();
    PAL_setPalette(PAL3, sprPlayer.palette->data, DMA);
    setCameraPosition(fix32ToInt(player.position.x), fix32ToInt(player.position.y));
    setCameraPosition(fix32ToInt(player.position.x) - 1, fix32ToInt(player.position.y) - 1);

    player.sprite = SPR_addSprite(&sprPlayer, fix32ToInt(player.position.x), fix32ToInt(player.position.y), TILE_ATTR(PAL3, 0, FALSE, FALSE));

    SPR_update();
    SYS_doVBlankProcess();

    while (1)
    {
        SPR_update();
        handleInput();
        moveEntity();

        VDP_showFPS(FALSE);
        setCameraPosition(fix32ToInt(player.position.x), fix32ToInt(player.position.y));

        SYS_doVBlankProcess();
    }

    return (0);
}
