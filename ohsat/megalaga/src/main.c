
#include <genesis.h>
#include <resources.h>

int main()
{
    SYS_disableInts();

    VDP_loadTileSet(background.tileset, 1, DMA);
    PAL_setPalette(PAL1, background.palette->data, DMA);

    int offset = 0;
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    while (1)
    {
        VDP_setVerticalScroll(BG_B, offset -= 2);
        if (offset <= -256)
            offset = 0;

        for (int index = 0; index < 1280; index++)
        {
            int thex = index % 40;
            int they = index / 40;

            // (max - min + 1) + min
            int value = (random() % (10 - 1 + 1)) + 1;

            if (value > 3)
                value = 1;

            VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, value), thex, they);
        }

        SYS_doVBlankProcess();
    }

    SYS_enableInts();

    return (0);
}