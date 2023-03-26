
#include <genesis.h>
#include <resources.h>

u16 colors[6] = {
    RGB24_TO_VDPCOLOR(0xFF0000),
    RGB24_TO_VDPCOLOR(0xFFFF00),
    RGB24_TO_VDPCOLOR(0x00FF00),
    RGB24_TO_VDPCOLOR(0x00FFFF),
    RGB24_TO_VDPCOLOR(0x0000FF),
    RGB24_TO_VDPCOLOR(0xFF00FF),
};

bool isPaused = FALSE;
u8 currentColor = 0;
u8 ticker = 0;

void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if (changed & state & BUTTON_START)
    {
        isPaused = !isPaused;
        if (isPaused)
        {
            XGM_pausePlay();
        }
        else
        {
            XGM_resumePlay();
        }
    }
}

void changeColor()
{
    if (!isPaused)
    {
        ticker++;
        if (ticker == 60)
        {
            ticker = 0;
            if (currentColor < 5)
            {
                currentColor++;
            }
            else
            {
                currentColor = 0;
            }

            PAL_setColor(15, colors[currentColor]);
        }
    }
}

int main()
{
    XGM_setLoopNumber(-1);
    XGM_startPlay(&xgmTrack1);

    JOY_init();
    JOY_setEventHandler(&myJoyHandler);

    VDP_drawText("Welcome to Disco Zone!", 9, 13);

    while (1)
    {
        changeColor();

        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}