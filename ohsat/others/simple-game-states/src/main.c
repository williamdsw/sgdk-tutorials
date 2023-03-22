
#include <genesis.h>
#include <resources.h>
#include "game-states.h"

enum GAME_STATE currentState;

void init()
{
    JOY_init();
    currentState = MENU;
}

void joyHandlerMenu(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if (state & BUTTON_START)
        {
            currentState = PLAY;
        }
    }
}

void processStateMenu()
{
    // init
    JOY_setEventHandler(&joyHandlerMenu);
    PAL_setColor(0, RGB24_TO_VDPCOLOR(0x000000));
    VDP_drawText("MENU STATE", 10, 13);

    // update
    while (currentState == MENU)
    {
        SYS_doVBlankProcess();
    }

    // cleanup
    VDP_clearText(10, 13, 10);
}

void processStatePlay()
{
    // init
    JOY_setEventHandler(NULL);
    PAL_setColor(0, RGB24_TO_VDPCOLOR(0xff0000));
    VDP_drawText("PLAY STATE", 10, 13);

    // update
    u16 timer = 120;
    while (currentState == PLAY)
    {
        timer--;
        if (timer == 0)
        {
            currentState = MENU;
        }

        SYS_doVBlankProcess();
    }

    // cleanup
    VDP_clearText(10, 13, 10);
}

int main()
{
    init();

    while (1)
    {
        switch (currentState)
        {
        case MENU:
            processStateMenu();
            break;

        case PLAY:
            processStatePlay();
            break;

        default:
            break;
        }
    }

    return (0);
}