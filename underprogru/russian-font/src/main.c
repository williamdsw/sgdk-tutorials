
#include <genesis.h>
#include <resources.h>

u16 array_u16len(const u16 *arr)
{
    const u16 *src;
    src = arr;
    while (*src++)
        ;
    return (src - arr) - 1;
}

void VDP_drawTextOffset(VDPPlane plane, const u16 *vram_offsets, u16 len, u16 first_tile, u16 x, u16 y)
{

    // get the horizontal plane size (in cell)
    u16 pw = (plane == WINDOW) ? windowWidth : planeWidth;
    u16 ph = (plane == WINDOW) ? 32 : planeHeight;

    // string outside plane --> exit
    if ((x >= pw) || (y >= ph))
    {
        return;
    }

    // sometimes works sometimes no, scored on this function now enter the length of the handles.
    // len = array_u16len(vram_offsets);

    // if string don't fit in plane, we cut it
    if (len > (pw - x))
    {
        len = pw - x;
    }

    PAL_setColor(16 + 1, RGB24_TO_VDPCOLOR(0xffffff));

    u16 curTileIndex = 0;
    u16 i = 0;
    u16 curX = 1;
    while (i < len)
    {
        curTileIndex = first_tile - 1 + vram_offsets[i];
        // KLog_S1("curTileIndex: ", curTileIndex);
        VDP_setTileMapXY(plane, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, curTileIndex), curX, y);
        i++;
        curX++;
    }
}

void drawCharCode(const char ch)
{
    KLog_S1("char: ", (int)ch);
}

int main()
{
    // VDP_drawText("Hello world", 0, 0);

    VDP_drawImage(BG_A, &img, 0, 0);

    // index of initial tile, where our font begins
    u16 ind = 1300;
    VDP_loadTileSet(&font_rus, ind, DMA);

    // arrays of displacements/lines
    u16 textArr1[15] = {49, 86, 79, 76, 88, 72, 74, 83, 103, 102, 1, 51, 37, 38, 44};
    u16 textArr2[28] = {52, 77, 87, 77, 88, 100, 13, 1, 90, 99, 1, 87, 86, 85, 80, 84, 72, 77, 96, 100, 1, 88, 91, 89, 89, 82, 80, 81};

    VDP_drawTextOffset(BG_A, textArr1, 15, ind, 1, 1);
    VDP_drawTextOffset(BG_A, textArr2, 28, ind, 1, 2);
    // drawCharCode('a');

    while (1)
    {
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}