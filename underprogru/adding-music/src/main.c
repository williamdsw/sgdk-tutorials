
#include <genesis.h>
#include <resources.h>

// wav, vgm/xgm are supported
// wav = used for sounds but possible for music
// vga/xgm = used for music

int counter = 0;

void myInputHandler(u16 joy, u16 state, u16 changed)
{
    if (state & changed & BUTTON_ALL)
    {
        counter++;
        char text[100] = "";
        sprintf(text, "Pressed: %d time(s)!", counter);
        VDP_drawText(text, 0, 0);

        // sample, priority (0 to 15), channel
        XGM_startPlayPCM(64, 15, SOUND_PCM_CH2);
    }
}

int main()
{
    JOY_init();
    JOY_setEventHandler(&myInputHandler);

    XGM_startPlay(xgm_music);

    // sample_id, sample, sample_size_in_bytes
    // 1 to 63 used for music, 64 to 255 for SFX
    XGM_setPCM(64, jump_sfx, sizeof(jump_sfx));

    while (1)
    {
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}