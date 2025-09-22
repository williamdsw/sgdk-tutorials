
#include <genesis.h>
#include <resources.h>

u16 current_line = 0;
f16 v_offset = 0;
f16 v_scroll_step = FIX16(3);

void HIntHandler()
{
    VDP_setVerticalScroll(BG_A, current_line + F16_toInt(v_offset));
    v_scroll_step += FIX16(0.02);
    v_offset -= v_scroll_step;
}

void VIntHandler()
{
    current_line += 1;
    v_scroll_step = FIX16(3);
    v_offset = 0;
}

int main()
{
    VDP_drawImage(BG_A, &img, 0, 0);

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    PAL_setColors(0, palette_black, 64, DMA);

    // Disable interrupts
    SYS_disableInts();

    // how many lines an interrupt is called (0 = every line, 4 = every 5th line)
    VDP_setHIntCounter(0);

    // include horizontal (HBLANK) interrupts
    VDP_setHInterrupt(1);

    // callback that will called during the HBLANK interrupt
    // ILLEGAL INSTRUCTION
    // SYS_setHIntCallback(&HIntHandler);

    // callback that will called during the VBLANK interrupt
    // ILLEGAL INSTRUCTION
    // SYS_setVIntCallback(&VIntHandler);

    // // interrupts are configured and can be enabled
    SYS_enableInts();

    PAL_fadeIn(0, 15, img.palette->data, 32, FALSE);

    while (1)
    {
        SYS_doVBlankProcess();
    }

    return (0);
}