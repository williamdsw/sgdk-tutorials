
#include <genesis.h>
#include <resources.h>

// 0: grass; 1: walls; 2: doors
u8 levelTilesIndexes[8][8] = 
{
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
};

void init()
{
    VDP_loadTileSet(imgFloorTiles.tileset, 1, DMA);
    PAL_setPalette(PAL1, imgFloorTiles.palette->data, DMA);
}

void loadLevel()
{
    u8 x = 0;
    u8 y = 0;
    u8 tile = 0;

    // y = row
    for (y = 0; y < 8; y++)
    {
        // x = column
        for (x = 0; x < 8; x++)
        {
            tile = levelTilesIndexes[y][x];
            VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, tile + 1), x, y);
        }
    }
}

int main()
{
    init();
    loadLevel();

    while (1)
    {
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}