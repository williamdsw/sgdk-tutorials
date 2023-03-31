
#include <genesis.h>
#include <resources.h>

u8 currentTrack = 0;

int main()
{
    XGM_setLoopNumber(0);
    XGM_startPlay(&xgmTrack2);
    currentTrack = 1;

    while (1)
    {
        if (currentTrack == 1 && XGM_getElapsed() == 490)
        {
            XGM_stopPlay();
            XGM_setLoopNumber(-1);
            XGM_startPlay(&xgmTrack2);
            currentTrack = 2;
        }

        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}