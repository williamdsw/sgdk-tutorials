
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
int player_attack_timer = 0;
const int PLAYER_ATTACK_DURATION = 56;

bool isFacingRight = TRUE;
bool isMoving = FALSE;

// Good for hold events, like moving, holding/charging attack
static void handleMoveInput()
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

// Pressed once, good for jumping, attack, menu controls
static void joyEvent(u16 joy, u16 changed, u16 state)
{
    if ((changed & state & BUTTON_B) && player_attack_timer == 0)
    {
        SPR_setAnim(player, PLAYER_ANIMATION_UPPER);
        player_attack_timer += 1;
    }
}

static void checkAttackTimer()
{
    if (player_attack_timer == 0)
    {
        handleMoveInput();
    }
    else if (player_attack_timer > 0 && player_attack_timer < PLAYER_ATTACK_DURATION)
    {
        player_attack_timer += 1;
    }
    else
        player_attack_timer = 0;
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

    JOY_setEventHandler(joyEvent);

    while (1)
    {
        // Scrolling for background
        // VDP_setHorizontalScroll(BG_B, horizontalScrollOffsetBackground);
        // horizontalScrollOffsetBackground -= 1;

        // Scrolling for foreground
        // VDP_setHorizontalScroll(BG_A, horizontalScrollOffsetForeground);
        // horizontalScrollOffsetForeground -= 2;

        checkAttackTimer();

        SPR_update();

        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
