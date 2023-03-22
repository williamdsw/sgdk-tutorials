
#include <genesis.h>
#include <resources.h>

int main()
{
    VDP_drawText("RETROGEMN SAMPLE", 0, 0);

    while (1)
    {
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}