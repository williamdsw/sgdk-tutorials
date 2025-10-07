
#include <genesis.h>
#include <resources.h>

u16 ind = TILE_USER_INDEX;
Map *level_1_map;

int x = 0;
int y = 768;

int main()
{
    VDP_loadTileSet(&our_tileset, ind, DMA);
    level_1_map = MAP_create(&our_level_map, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind));
    PAL_setPalette(PAL0, our_palette.data, DMA);
    MAP_scrollTo(level_1_map, x, y);

    while (1)
    {
        MAP_scrollTo(level_1_map, x, y);
        x += 1;

        SYS_doVBlankProcess();
    }

    return (0);
}