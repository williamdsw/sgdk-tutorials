
#include <genesis.h>
#include <resources.h>

Map *bga;

s16 camPosX = -1;
s16 camPosY = -1;

fix32 posX = 0;
fix32 posY = 0;

bool paused = FALSE;

void setCameraPosition(s16 x, s16 y)
{
    if ((x != camPosX) || (y != camPosY))
    {
        camPosX = x;
        camPosY = y;
        MAP_scrollTo(bga, x, y);
    }
}

void handleInput()
{
    u16 value = JOY_readJoypad(JOY_1);

    if (!paused)
    {
        // FIX32 = converts an integer into fake 32-bit fractional number
        // F32_toInt = converts a fake 32-bit fractional number into an integer

        if (value & BUTTON_RIGHT)
        {
            posX += FIX32(5);
            setCameraPosition(F32_toInt(posX), F32_toInt(posY) - 140);
        }
        else if (value & BUTTON_LEFT)
        {
            posX -= FIX32(5);
            setCameraPosition(F32_toInt(posX), F32_toInt(posY) - 140);
        }

        if (value & BUTTON_UP)
        {
            posY -= FIX32(5);
            setCameraPosition(F32_toInt(posX), F32_toInt(posY) - 140);
        }
        else if (value & BUTTON_DOWN)
        {
            posY += FIX32(5);
            setCameraPosition(F32_toInt(posX), F32_toInt(posY) - 140);
        }
    }
}

int main()
{
    // index of the initial tile
    u16 ind = TILE_USER_INDEX;

    // writes the tileset to VRAM
    VDP_loadTileSet(&bga_tileset, ind, DMA);

    bga = MAP_create(&bga_map, BG_A, TILE_ATTR_FULL(0, 0, FALSE, FALSE, ind));

    setCameraPosition(F32_toInt(posX), F32_toInt(posY) - 140);
    SYS_doVBlankProcess();

    PAL_setColors(0, palette_all.data, 16 * 2, DMA);

    while (1)
    {
        handleInput();
        SYS_doVBlankProcess();
    }

    return (0);
}