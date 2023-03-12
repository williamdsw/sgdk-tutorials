
#include <genesis.h>
#include <resources.h>
#include "defines.h"
#include "entity.h"

// 0: grass; 1: walls; 2: doors
u8 levelTilesIndexes[8][8] = 
{
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 4, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
};

Entity player = { {0, 0}, {0, 0}, 8, 8, 0, FALSE, NONE, NULL, "PLAYER" };

void initGraphics()
{
    // Tilesheet
    VDP_loadTileSet(imgFloorTiles.tileset, 1, DMA);
    PAL_setPalette(PAL1, imgFloorTiles.palette->data, DMA);

    // Player
    PAL_setPalette(PAL2, sprPlayer.palette->data, DMA);
}

void placePlayer(u16 x, u16 y)
{
    player.tilePosition.x = x;
    player.tilePosition.y = y;
    player.position.x = player.tilePosition.x * LEVEL_TILE_SIZE;
    player.position.y = player.tilePosition.y * LEVEL_TILE_SIZE;
    player.sprite = SPR_addSprite(&sprPlayer, player.position.x, player.position.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
}

int getTileAtXY(u16 x, u16 y)
{
    // or &levelTilesIndexes[y][x]
    return *(&levelTilesIndexes[0][0] + (y * MAP_HEIGHT + x));
}

void movePlayer(MoveDirection nextDirection)
{
    if (!player.isMoving)
    {
        switch (nextDirection)
        {
            case UP: 
            {
                if (player.tilePosition.y > 0 && getTileAtXY(player.tilePosition.x, player.tilePosition.y - 1) != SOLID_TILE)
                {
                    player.tilePosition.y =- 1;
                    player.isMoving = TRUE;
                    player.moveDirection = nextDirection;
                }
            
                break;
            }

            case DOWN:
            {
                if (player.tilePosition.y < MAP_HEIGHT - 1 && getTileAtXY(player.tilePosition.x, player.tilePosition.y + 1) != SOLID_TILE)
                {
                    player.tilePosition.y += 1;
                    player.isMoving = TRUE;
                    player.moveDirection = nextDirection;
                }

                break;
            }

            case LEFT:
            {
                if (player.tilePosition.x > 0 && getTileAtXY(player.tilePosition.x - 1, player.tilePosition.y) != SOLID_TILE)
                {
                    player.tilePosition.x -= 1;
                    player.isMoving = TRUE;
                    player.moveDirection = nextDirection;
                }

                break;
            }

            case RIGHT: 
            {
                if (player.tilePosition.x < MAP_HEIGHT - 1 && getTileAtXY(player.tilePosition.x + 1, player.tilePosition.y) != SOLID_TILE)
                {
                    player.tilePosition.x += 1;
                    player.isMoving = TRUE;
                    player.moveDirection = nextDirection;
                }

                break;
            }

            default: break;
        }
    }
}

void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if (state & BUTTON_UP) movePlayer(UP);
        else if (state & BUTTON_DOWN) movePlayer(DOWN);
        else if (state & BUTTON_LEFT) movePlayer(LEFT);
        else if (state & RIGHT) movePlayer(RIGHT);
    }
}

void loadLevel()
{
    u8 x = 0;
    u8 y = 0;
    u8 tile = 0;

    SPR_init();

    // y = row
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        // x = column
        for (x = 0; x < MAP_WIDTH; x++)
        {
            tile = levelTilesIndexes[y][x];
            if (tile == SPAWN_TILE)
            {
                placePlayer(x, y);
                VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), x, y);
            }
            else
            {
                VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, tile + 1), x, y);
            }
        }
    }
}

int main()
{
    initGraphics();
    loadLevel();

    JOY_init();
    JOY_setEventHandler(&myJoyHandler);

    while (1)
    {
        SPR_update();
        SYS_doVBlankProcess();
    }

    return (0);
}