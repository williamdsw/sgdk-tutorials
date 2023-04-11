
#include <genesis.h>
#include <resources.h>

u16 ind = TILE_USER_INDEX;
Map *level_1_map;

int x = 0;
int y = 0;

int main()
{
    // VDP_loadTileSet(&our_tileset, ind, DMA);
    // level_1_map = MAP_create(&our_level_map, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind));
    // PAL_setPalette(PAL0, our_palette.data, DMA);
    // MAP_scrollTo(level_1_map, x, y);

    VDP_loadTileSet(&bomber_tileset, ind, DMA);
    level_1_map = MAP_create(&bomber_map, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind));
    PAL_setPalette(PAL0, bomber_palette.data, DMA);
    MAP_scrollTo(level_1_map, x, y);

    SPR_init();

    PAL_setPalette(PAL1, obj_zero.palette->data, DMA);
    SPR_addSprite(&obj_zero, 100, 100, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));

    SPR_update();

    while (1)
    {
        SYS_doVBlankProcess();
    }

    return (0);
}