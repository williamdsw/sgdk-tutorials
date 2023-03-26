
#include <genesis.h>
#include <resources.h>

int main()
{
    PAL_setPalette(PAL0, palAll.data, DMA);

    // Load the tileset and keep track of the index
    u16 index = TILE_USER_INDEX;
    VDP_loadTileSet(&tlsLevel, index, DMA);
    index += tlsLevel.numTile;

    Map *map = MAP_create(&mapLevel, BG_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USER_INDEX));

    u32 offset = 0;
    u32 scrollDirection = 1;

    while (1)
    {
        MAP_scrollTo(map, offset, 0);

        offset += scrollDirection;
        if (offset == 190)
        {
            scrollDirection = -1;
        }
        else if (offset == 0)
        {
            scrollDirection = 1;
        }

        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}