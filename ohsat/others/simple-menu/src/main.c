
#include <genesis.h>
#include <resources.h>
#include "option.h"

#define NUM_OPTIONS 3

Option options[NUM_OPTIONS] = {
    {8, 8, "START"},
    {10, 9, "OPTIONS"},
    {12, 10, "EXIT"},
};

u8 currentIndex = 0;
Sprite *cursor;

void updateCursorPosition();
void moveUp();
void moveDown();
void joyEventHandler(u16 joy, u16 changed, u16 state);
void select(u16 option);
void pickStart();
void pickOptions();
void pickExit();

int main()
{
    SPR_init();

    cursor = SPR_addSprite(&sprCursor, 0, 0, 0);
    updateCursorPosition();

    JOY_init();
    JOY_setEventHandler(&joyEventHandler);

    u16 i = 0;
    for (i = 0; i < NUM_OPTIONS; i++)
    {
        Option item = options[i];
        VDP_drawText(item.label, item.x, item.y);
    }

    while (1)
    {
        SPR_update();
        SYS_doVBlankProcess();
    }

    return (0);
}

void updateCursorPosition()
{
    SPR_setPosition(cursor, options[currentIndex].x * 8 - 12, options[currentIndex].y * 8);
}

void moveUp()
{
    if (currentIndex > 0)
    {
        currentIndex--;
        updateCursorPosition();
    }
}

void moveDown()
{
    if (currentIndex < NUM_OPTIONS - 1)
    {
        currentIndex++;
        updateCursorPosition();
    }
}

void joyEventHandler(u16 joy, u16 changed, u16 state)
{
    if (changed & state & BUTTON_UP)
    {
        moveUp();
    }
    else if (changed & state & BUTTON_DOWN)
    {
        moveDown();
    }

    if (changed & state & BUTTON_START)
    {
        select(currentIndex);
    }
}

void select(u16 option)
{
    switch (option)
    {
    case 0:
        pickStart();
        break;
    case 1:
        pickOptions();
        break;
    case 2:
        pickExit();
        break;
    default:
        break;
    }
}

void pickStart()
{
    VDP_clearText(8, 12, 20);
    VDP_drawText("Picked Start", 8, 12);
}

void pickOptions()
{
    VDP_clearText(8, 12, 20);
    VDP_drawText("Picked Options", 8, 12);
}

void pickExit()
{
    VDP_clearText(8, 12, 20);
    VDP_drawText("Picked Exit", 8, 12);
}