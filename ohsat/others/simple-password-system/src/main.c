
#include <genesis.h>
#include <resources.h>
#include "option.h"

#define NUM_LETTERS 3
#define PASS_X 16
#define PASS_Y 4
#define PASS_LENGTH 3

Option options[NUM_LETTERS] = {
    {16, 8, "A"},
    {16, 9, "B"},
    {16, 10, "C"},
};

char password[PASS_LENGTH + 1] = "";

u8 currentIndex = 0;
Sprite *cursor;

void drawOptions()
{
    u16 i = 0;
    for (i = 0; i < NUM_LETTERS; i++)
    {
        Option item = options[i];
        VDP_drawText(item.label, item.x, item.y);
    }
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
    if (currentIndex < NUM_LETTERS - 1)
    {
        currentIndex++;
        updateCursorPosition();
    }
}

void updatePassword()
{
    VDP_drawText(password, PASS_X, PASS_Y);
}

void checkPassword()
{
    if (strcmp(password, "BAC") == 0)
    {
        VDP_drawText("LEVEL 2", PASS_X, 16);
    }
    else if (strcmp(password, "AAC") == 0)
    {
        VDP_drawText("LEVEL 3", PASS_X, 16);
    }
    else
    {
        VDP_drawText("WRONG", PASS_X, 16);

        password[0] = '\0';
        VDP_drawText("---", PASS_X, PASS_Y);
        updatePassword();
    }
}

void selectOption()
{
    if (strlen(password) == PASS_LENGTH)
    {
        checkPassword();
    }
    else
    {
        strcat(password, options[currentIndex].label);
        updatePassword();
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

    if (changed & state & BUTTON_C)
    {
        selectOption();
    }
}

int main()
{
    drawOptions();

    SPR_init();
    cursor = SPR_addSprite(&sprCursor, 0, 0, 0);
    updateCursorPosition();

    JOY_init();
    JOY_setEventHandler(&joyEventHandler);

    VDP_drawText("---", PASS_X, PASS_Y);

    while (1)
    {
        SPR_update();
        SYS_doVBlankProcess();
    }

    return (0);
}