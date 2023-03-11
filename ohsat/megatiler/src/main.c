
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
    player.position.x = player.tilePosition.x * TILE_SIZE;
    player.position.y = player.tilePosition.y * TILE_SIZE;
    player.sprite = SPR_addSprite(&sprPlayer, player.position.x, player.position.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
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

    while (1)
    {
        SPR_update();
        SYS_doVBlankProcess();
    }

    return (0);
}