
#include <genesis.h>
#include <resources.h>

u16 defaultColor = -1;
u16 grayColor = -1;
u16 blueColor = -1;
u16 redColor = -1;
u16 greenColor = -1;
u16 yellowColor = -1;
u16 orangeColor = -1;
u16 purpleColor = -1;

void initGraphics()
{
    PAL_setPalette(PAL1, sprPlayer.palette->data, DMA);

    SPR_init();

    for (int i = 0; i < 10; i++)
    {
        SPR_addSprite(&sprPlayer, 64 + (i * 16), 64, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    }

    SPR_update();
}

void initColors()
{
    grayColor = RGB24_TO_VDPCOLOR(0x808080);
    blueColor = RGB24_TO_VDPCOLOR(0x0000ff);
    redColor = RGB24_TO_VDPCOLOR(0xff0000);
    greenColor = RGB24_TO_VDPCOLOR(0x00ff00);
    yellowColor = RGB24_TO_VDPCOLOR(0xffd966);
    orangeColor = RGB24_TO_VDPCOLOR(0xb45f06);
    purpleColor = RGB24_TO_VDPCOLOR(0x351c75);
    defaultColor = PAL_getColor(18);
}

void swapToColor(u16 color)
{
    PAL_setColor(18, color);
}

void myJoyHandler(u16 joy, u16 change, u16 state)
{
    if (joy == JOY_1)
    {
        if (state & BUTTON_A)
        {
            swapToColor(grayColor);
        }
        else if (state & BUTTON_B)
        {
            swapToColor(blueColor);
        }
        else if (state & BUTTON_C)
        {
            swapToColor(redColor);
        }
        else if (state & BUTTON_START)
        {
            swapToColor(defaultColor);
        }
        else if (state & BUTTON_UP)
        {
            swapToColor(greenColor);
        }
        else if (state & BUTTON_DOWN)
        {
            swapToColor(yellowColor);
        }
        else if (state & BUTTON_LEFT)
        {
            swapToColor(orangeColor);
        }
        else if (state & BUTTON_RIGHT)
        {
            swapToColor(purpleColor);
        }
    }
}

int main()
{
    JOY_init();
    JOY_setEventHandler(&myJoyHandler);

    initGraphics();
    initColors();

    while (1)
    {
        SPR_update();
        SYS_doVBlankProcess();
    }

    return (0);
}
