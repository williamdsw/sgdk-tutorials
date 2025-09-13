
#include <genesis.h>
#include <resources.h>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

s16 textPosX = 9;
s16 textPosY = 30;

char texts[14][25] = {
    "THIS CITY WAS ONCE A",
    "MOST EXCELLENT",
    "PLACE... UNTIL ONE",
    "DAY, A POWERFUL BUNCH",
    "OF BAD DUDES",
    "TOOK OVER.",
    "THESE HEINOUS DUDES",
    "SOON HAD CONTROL OF THE",
    "GOVERNMENT AND EVEN",
    "THE POLICE FORCE. THE",
    "CITY HAS BECOME A",
    "TYPICAL SETTING FOR",
    "A BEAT 'EM UP",
    "BOGUS",
};

void drawTexts()
{
    for (int index = 0; index < (int)ARRAY_LENGTH(texts); index++)
    {
        int counter = index;

        if (index > 5)
            counter += 4;

        VDP_drawText(texts[index], textPosX, textPosY + counter);
    }
}

int main()
{
    VDP_setPlaneSize(32, 128, TRUE);
    VDP_setTextPlane(BG_A);

    // Set background color to red
    PAL_setColor(0, RGB24_TO_VDPCOLOR(0xA20000));

    // Load the background tileset
    VDP_loadTileSet(imgBackground.tileset, 1, DMA);

    // Load the palette of the image into PAL1
    PAL_setPalette(PAL1, imgBackground.palette->data, DMA);

    VDP_setTileMapEx(BG_B, imgBackground.tilemap, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), 0, 12, 0, 0, 32, 18, DMA);

    drawTexts();

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    fix16 offsetX = FIX16(0);
    fix16 offsetY = FIX16(0);

    while (1)
    {
        offsetY += FIX16(0.2);
        offsetX -= FIX16(0.3);

        VDP_setHorizontalScroll(BG_B, F16_toInt(offsetX));
        VDP_setVerticalScroll(BG_A, F16_toInt(offsetY));

        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}