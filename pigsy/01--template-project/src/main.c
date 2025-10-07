
#include <genesis.h>

int main()
{
    VDP_drawText("Welcome to the Pigsy SGDK template!!", 2, 13);

    while (1)
    {
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
