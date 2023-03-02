
#include <genesis.h>
#include <resources.h>

int main()
{
    u16 ind = TILE_USER_INDEX;

    // Use PAL0 for background images
    PAL_setPalette(PAL0, background.palette->data, DMA);
    VDP_drawImageEx(BG_B, &background, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += background.tileset->numTile;

    // Use PAL1 for foreground images
    PAL_setPalette(PAL1, foreground.palette->data, DMA);
    VDP_drawImageEx(BG_A, &foreground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += foreground.tileset->numTile;

    while (1)
    {
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
