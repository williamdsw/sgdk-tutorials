
#include <genesis.h>

int main(bool resetType)
{
    VDP_drawText("Hello world !", 12, 12);

    while (TRUE)
    {
        SYS_doVBlankProcess();
    }

    return 0;
}