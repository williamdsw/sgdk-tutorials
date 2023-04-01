
#include <genesis.h>
#include <resources.h>

int main()
{
    // this array will store all palettes
    u16 palette_full[64];

    // copies palette data (16 elements, 32 bytes) to another variable
    memcpy(&palette_full[0], imgBackground.palette->data, 16 * 2);

    // rewrite the palette to make it black
    PAL_setPaletteColors(0, palette_black, DMA);

    VDP_drawImage(BG_A, &imgBackground, 0, 0);

    // start_color, end_color, palette, transition_time_in_frames, execute_asynchronously
    PAL_fadeIn(0, 60, palette_full, 100, FALSE);

    // wait for 3 seconds
    waitMs(3000);

    // start_color, end_color, palette, transition_time_in_frames, execute_asynchronously
    PAL_fadeOut(0, 63, 100, FALSE);

    while (1)
    {
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}