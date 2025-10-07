
#include <genesis.h>
#include <resources.h>

u16 ind = TILE_USER_INDEX;

int main()
{
    PAL_setPalette(PAL0, bg0.palette->data, DMA);
    VDP_drawImageEx(BG_B, &bg0, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += bg0.tileset->numTile;

    PAL_setPalette(PAL2, bg1.palette->data, DMA);
    VDP_drawImageEx(BG_A, &bg1, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += bg1.tileset->numTile;

    VDP_setScreenWidth256();

    while (1)
    {
        SYS_doVBlankProcess();
    }

    return (0);
}