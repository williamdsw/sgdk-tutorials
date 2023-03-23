
#include <genesis.h>
#include <resources.h>

u16 redColor = RGB24_TO_VDPCOLOR(0xff0000);
u16 defaultColor;
u16 currentColor;
u16 timer = 120;

void changeColor(u16 color)
{
    PAL_setColor(15, color);
    timer = 120;
    currentColor = color;
}

int main()
{
    defaultColor = currentColor = PAL_getColor(15);
    VDP_drawText("Hello world", 8, 8);

    while (1)
    {
        timer--;
        if (timer <= 0)
        {
            changeColor(currentColor == defaultColor ? redColor : defaultColor);
        }

        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}