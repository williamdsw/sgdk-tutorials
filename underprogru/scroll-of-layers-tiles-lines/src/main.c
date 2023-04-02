
#include <genesis.h>
#include <resources.h>

int planeScroll()
{
    // x-axis displacement
    s16 x_offset = 0;

    // size of the layer in tiles (32, 64, 128)
    VDP_setPlaneSize(32, 32, TRUE);

    VDP_drawImage(BG_A, &bg1, -1, -3);

    // scroll mode
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    while (1)
    {
        x_offset += 10;
        if (x_offset > 256)
        {
            x_offset -= 256;
        }

        VDP_setHorizontalScroll(BG_A, x_offset);
        SYS_doVBlankProcess();
    }

    return (0);
}

int tilesScroll()
{
    VDP_setPlaneSize(32, 32, TRUE);
    VDP_drawImage(BG_A, &bg1, 0, 0);

    // x-axis = tiles, y-axis = meta-tiles
    VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_2TILE);

    s16 offset_mask[6] = {0, 5, 10, 15, 20, 25};
    s16 index = 0;

    while (1)
    {
        // responsible for vertical scrolling of tiles
        // VDP_setVerticalScrollTile(BG_A, 3, offset_mask, 6, CPU);

        // responsible for horizontal scrolling of tiles
        VDP_setHorizontalScrollTile(BG_A, 3, offset_mask, 6, CPU);

        for (index = 0; index < 6; index++)
        {
            offset_mask[index] += 1;
        }

        SYS_doVBlankProcess();
    }

    return (0);
}

int main()
{
    VDP_setPlaneSize(32, 32, TRUE);
    VDP_drawImage(BG_A, &bg2, 0, 0);

    // scroll of horizontal lines
    VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);

    // mask for all lines
    s16 offset_mask_line[224];
    s16 index = 0;
    for (index = 0; index < 224; index++)
    {
        offset_mask_line[index] = 0;
    }

    while (1)
    {
        VDP_setHorizontalScrollLine(BG_A, 0, offset_mask_line, 224, CPU);

        // for (index = 0; index < 224; index++)
        // {
        //     offset_mask_line[index] += random() % 10;
        // }

        // even lines - right, odd lines - left
        for (index = 0; index < 224; index += 2)
        {
            offset_mask_line[index] += 1;
            offset_mask_line[index - 1] -= 1;
        }

        SYS_doVBlankProcess();
    }

    return (0);
}