
#include <genesis.h>
#include <resources.h>

// 4 palettes of 16 colors each = 64 colors
// 320 x 240 (Sega Genesis Resolution)
// color depth = 4 bits
int main()
{
    // layer: (BGA_A, BG_B)
    // image: pointer to our image declared in resources.res
    // tile_x, tile_y: coordinates (1 tile = 8x8px)
    VDP_drawImage(BG_A, &img, 0, 0);

    while (1)
    {
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}