
#include <genesis.h>
#include <resources.h>

u16 ind = TILE_USER_INDEX;
int horizontalScrollOffsetBackground = 0;
int horizontalScrollOffsetForeground = 0;

int main()
{
    // Use PAL0 for background images
    PAL_setPalette(PAL0, background.palette->data, DMA);
    VDP_drawImageEx(BG_B, &background, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, -4, FALSE, TRUE);
    ind += background.tileset->numTile;

    // Use PAL1 for foreground images
    PAL_setPalette(PAL1, foreground.palette->data, DMA);
    VDP_drawImageEx(BG_A, &foreground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, -4, FALSE, TRUE);
    ind += foreground.tileset->numTile;

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    while (1)
    {
        // Scrolling for background
        VDP_setHorizontalScroll(BG_B, horizontalScrollOffsetBackground);
        horizontalScrollOffsetBackground -= 1;

        // Scrolling for foreground
        VDP_setHorizontalScroll(BG_A, horizontalScrollOffsetForeground);
        horizontalScrollOffsetForeground -= 2;

        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
