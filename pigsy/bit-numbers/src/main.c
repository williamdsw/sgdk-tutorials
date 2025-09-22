
#include <genesis.h>
#include <resources.h>

int main()
{
    VDP_drawText("8 bit numbers\0", 0, 0); // 8 bit: 0 to 255 or -128 to 127
    u8 number_8bit_pos = 0;                // 0 to 255
    s8 number_8bit_neg = 0;                // -128 to 127
    char text_8bit_pos[4] = "";
    char text_8bit_neg[4] = "";

    VDP_drawText("16 bit numbers\0", 0, 3); // 16 bit: 0 to 65,535 or -32,768 to 32,767
    u16 number_16bit_pos = 0;               // 0 to 65,535
    s16 number_16bit_neg = 0;               // -32,768 to 32,767
    char text_16bit_pos[6] = "";
    char text_16bit_neg[6] = "";

    VDP_drawText("32 bit numbers\0", 0, 6); // 32 bit: -2,147,483,648 to 2,147,483,647
    u32 number_32bit_pos = 0;
    s32 number_32bit_neg = 0;
    int number_32bit = 0;
    char text_32bit_pos[11] = "";
    char text_32bit_neg[11] = "";
    char text_32bit[11] = "";

    // slow parallax
    VDP_drawText("Fixed16 numbers\0", 0, 10); // fix16: -512 to 512
    fix16 fixed16_number = FIX16(0);
    char text_fixed16[10] = "";

    // gravity, jumping, player/enemy movement on large map
    VDP_drawText("Fixed32 numbers\0", 0, 12); // fix16: -512 to 512
    fix32 fixed32_number = FIX32(0);
    char text_fixed32[10] = "";

    // small data, etc.
    u8 player_continues = 255;
    u8 invincibility_frame_counter = 255;

    while (1)
    {
        sprintf(text_8bit_pos, "%4i", number_8bit_pos);
        VDP_drawTextBG(BG_A, text_8bit_pos, 0, 1);
        number_8bit_pos++;

        sprintf(text_8bit_neg, "%4i", number_8bit_neg);
        VDP_drawTextBG(BG_A, text_8bit_neg, 0, 2);
        number_8bit_neg++;

        sprintf(text_16bit_pos, "%6i", number_16bit_pos);
        VDP_drawTextBG(BG_A, text_16bit_pos, 0, 4);
        number_16bit_pos += 100;

        sprintf(text_16bit_neg, "%6i", number_16bit_neg);
        VDP_drawTextBG(BG_A, text_16bit_neg, 0, 5);
        number_16bit_neg += 100;

        sprintf(text_32bit_pos, "%11i", number_32bit_pos);
        VDP_drawTextBG(BG_A, text_32bit_pos, 0, 7);
        number_32bit_pos += 1000000;

        sprintf(text_32bit_neg, "%11i", number_32bit_neg);
        VDP_drawTextBG(BG_A, text_32bit_neg, 0, 8);
        number_32bit_neg += 1000000;

        sprintf(text_32bit, "%11i", number_32bit);
        VDP_drawTextBG(BG_A, text_32bit, 0, 9);
        number_32bit += 1000000;

        sprintf(text_fixed16, "%10i", F16_toInt(fixed16_number));
        VDP_drawTextBG(BG_A, text_fixed16, 0, 11);
        fixed16_number += FIX16(0.0157);

        sprintf(text_fixed32, "%10i", F32_toInt(fixed32_number));
        VDP_drawTextBG(BG_A, text_fixed32, 0, 13);
        fixed32_number += FIX32(0.001);

        SYS_doVBlankProcess();
    }

    return (0);
}
