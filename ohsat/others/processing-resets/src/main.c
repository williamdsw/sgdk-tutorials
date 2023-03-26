
#include <genesis.h>
#include <resources.h>

// Soft Reset: doesn't delete RAM
// Hard Reset: deletes everything

int ticker = 0;
char tickerString[4] = "0000";

// 0: soft reset
// 1: hard reset
int main(int resetType)
{
    while (1)
    {
        ticker++;
        sprintf(tickerString, "%d", ticker);
        VDP_clearText(12, 12, 4);
        VDP_drawText(tickerString, 12, 12);

        char typeString[14] = "";
        sprintf(typeString, "Reset Type: %d", resetType);
        VDP_drawText(typeString, 0, 0);

        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}