#include <genesis.h>
#include <resources.h>

Sprite *test_sprite;
s16 test_sprite_x = 50;
s16 test_sprite_y = 50;

Sprite *spectre;
s16 spectre_x = 100;
s16 spectre_y = 100;

static void handleInput();

int main()
{
    u16 index = TILE_USER_INDEX;
    PAL_setPalette(PAL0, kitchen_bg_image.palette->data, DMA);

    // image needs to set to high priority to avoid dark color
    VDP_drawImageEx(BG_B, &kitchen_bg_image, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, index), 0, 0, FALSE, TRUE);

    SPR_init();

    PAL_setPalette(PAL3, spectre_sprite.palette->data, DMA);
    PAL_setPalette(PAL2, sh_palette_sprite.palette->data, DMA);
    spectre = SPR_addSprite(&spectre_sprite, spectre_x, spectre_y, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
    test_sprite = SPR_addSprite(&sh_palette_sprite, test_sprite_x, test_sprite_y, TILE_ATTR(PAL2, TRUE, FALSE, FALSE));

    VDP_setHilightShadow(TRUE);

    while (1)
    {
        handleInput();
        SPR_update();
        SYS_doVBlankProcess();
    }

    return (0);
}

static void handleInput()
{
    u16 value = JOY_readJoypad(JOY_1);

    if (value & BUTTON_LEFT)
    {
        test_sprite_x--;
    }
    if (value & BUTTON_RIGHT)
    {
        test_sprite_x++;
    }
    if (value & BUTTON_UP)
    {
        test_sprite_y--;
    }
    if (value & BUTTON_DOWN)
    {
        test_sprite_y++;
    }

    if (value & BUTTON_A)
    {
        spectre_x--;
    }
    if (value & BUTTON_C)
    {
        spectre_x++;
    }
    if (value & BUTTON_Y)
    {
        spectre_y--;
    }
    if (value & BUTTON_B)
    {
        spectre_y++;
    }

    SPR_setPosition(test_sprite, test_sprite_x, test_sprite_y);
    SPR_setPosition(spectre, spectre_x, spectre_y);
}