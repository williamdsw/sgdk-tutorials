
#include <genesis.h>
#include <resources.h>

void handleConsecutiveInput()
{
    // Remove tiles from the specified area
    VDP_clearText(1, 1, 5);
    u16 value = JOY_readJoypad(JOY_1);

    // & = checking bit mask
    if (value & BUTTON_LEFT)
    {
        VDP_drawText("Left", 1, 1);
    }

    if (value & BUTTON_RIGHT)
    {
        VDP_drawText("Right", 1, 1);
    }
}

// joy = pressed joystick (JOY_1, JOY_2)
// if the key pressed has changed
// state = the key pressed
void handleParallelInput(u16 joy, u16 changed, u16 state)
{
    VDP_clearText(1, 1, 5);

    if (joy == JOY_1)
    {
        if (state & BUTTON_LEFT)
        {
            VDP_drawText("Left", 1, 1);
        }

        if (state & BUTTON_RIGHT)
        {
            VDP_drawText("Right", 1, 1);
        }
    }
}

int main()
{
    JOY_init();
    JOY_setEventHandler(&handleParallelInput);

    while (1)
    {
        // handleConsecutiveInput();

        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}