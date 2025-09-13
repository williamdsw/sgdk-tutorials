#include <genesis.h>
#include <resources.h>

#define REGION *(u8 *)0xA10001

int main()
{
    char out[12] = "";
    sprintf(out, "HEX VALUE: %X", REGION);
    VDP_drawText(out, 2, 4);

    // Check the region bit (7)
    if (REGION & (1 << 7))
    {
        VDP_drawText("REGION: NOT JAPAN", 2, 5);
    }
    else
    {
        VDP_drawText("REGION: JAPAN", 2, 5);
    }

    // Check the video bit (6)
    if (REGION & (1 << 6))
    {
        VDP_drawText("REGION: PAL", 2, 6);
    }
    else
    {
        VDP_drawText("REGION: NTSC", 2, 6);
    }

    while (1)
    {
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}