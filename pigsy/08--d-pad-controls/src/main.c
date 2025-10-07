
#include <genesis.h>
#include <resources.h>

// Drawing backgrounds for Mega Drive/Sega Genesis: multiple of 8, 16 colors in each of 4 palletes, exported to PNG

// u16 ind = TILE_USER_INDEX;
// int horizontalScrollOffsetBackground = 0;
// int horizontalScrollOffsetForeground = 0;

#define PLAYER_ANIMATION_STILL 0
#define PLAYER_ANIMATION_IDLE 1
#define PLAYER_ANIMATION_WALK 2
#define PLAYER_ANIMATION_UPPER 3

Sprite *player;
int player_x_position = 100;
int player_y_position = 50;
bool isFacingRight = TRUE;
bool isMoving = FALSE;

static void handleInput()
{
    u16 value = JOY_readJoypad(JOY_1);
    isMoving = FALSE;

    if (value & BUTTON_RIGHT)
    {
        player_x_position += 1;
        isMoving = TRUE;
        isFacingRight = TRUE;
    }
    else if (value & BUTTON_LEFT)
    {
        player_x_position -= 1;
        isMoving = TRUE;
        isFacingRight = FALSE;
    }

    if (value & BUTTON_UP)
    {
        player_y_position -= 1;
        isMoving = TRUE;
    }
    else if (value & BUTTON_DOWN)
    {
        player_y_position += 1;
        isMoving = TRUE;
    }

    if (isMoving)
    {
        SPR_setAnim(player, PLAYER_ANIMATION_WALK);
    }

    if (!isMoving)
    {
        SPR_setAnim(player, PLAYER_ANIMATION_IDLE);
    }

    SPR_setHFlip(player, isFacingRight);
    SPR_setPosition(player, player_x_position, player_y_position);
}

int main()
{
    // Use PAL0 for background images
    // PAL_setPalette(PAL0, background.palette->data, DMA);
    // VDP_drawImageEx(BG_B, &background, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, -4, FALSE, TRUE);
    // ind += background.tileset->numTile;

    // Use PAL1 for foreground images
    // PAL_setPalette(PAL1, foreground.palette->data, DMA);
    // VDP_drawImageEx(BG_A, &foreground, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, -4, FALSE, TRUE);
    // ind += foreground.tileset->numTile;

    // VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    // Initialize sprite engine
    SPR_init();

    // PAL2 for players
    PAL_setPalette(PAL2, axel_spritesheet.palette->data, DMA);
    player = SPR_addSprite(&axel_spritesheet, player_x_position, player_y_position, TILE_ATTR(PAL2, FALSE, FALSE, TRUE));
    SPR_setAnim(player, PLAYER_ANIMATION_IDLE);

    while (1)
    {
        // Scrolling for background
        // VDP_setHorizontalScroll(BG_B, horizontalScrollOffsetBackground);
        // horizontalScrollOffsetBackground -= 1;

        // Scrolling for foreground
        // VDP_setHorizontalScroll(BG_A, horizontalScrollOffsetForeground);
        // horizontalScrollOffsetForeground -= 2;

        handleInput();

        SPR_update();

        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
