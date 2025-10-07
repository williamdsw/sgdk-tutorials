
#include <genesis.h>
#include <resources.h>

// Drawing backgrounds for Mega Drive/Sega Genesis: multiple of 8, 16 colors in each of 4 palletes, exported to PNG

// u16 ind = TILE_USER_INDEX;
// int horizontalScrollOffsetBackground = 0;
// int horizontalScrollOffsetForeground = 0;

// -- Player 1 -- //

#define PLAYER1_ANIMATION_STILL 0
#define PLAYER1_ANIMATION_IDLE 1
#define PLAYER1_ANIMATION_WALK 2
#define PLAYER1_ANIMATION_UPPER 3

Sprite *player1;

int player1_x_position = 100;
int player1_y_position = 50;
int player1_attack_timer = 0;
const int PLAYER1_ATTACK_DURATION = 56;

bool isPlayer1FacingRight = TRUE;
bool isPlayer1Moving = FALSE;

// -- Player 2 -- //

#define PLAYER2_ANIMATION_STILL 0
#define PLAYER2_ANIMATION_IDLE 1
#define PLAYER2_ANIMATION_START_WALK 2
#define PLAYER2_ANIMATION_WALK 3
#define PLAYER2_ANIMATION_STOP_WALK 4
#define PLAYER2_ANIMATION_LOOK_UP 5
#define PLAYER2_ANIMATION_CROUCH 6
#define PLAYER2_ANIMATION_SPIN 7

Sprite *player2;

int player2_x_position = 200;
int player2_y_position = 50;
int player2_attack_timer = 0;
const int PLAYER2_ATTACK_DURATION = 56;

bool isPlayer2FacingRight = TRUE;
bool isPlayer2Moving = FALSE;

// Good for hold events, like moving, holding/charging attack
static void handleMoveInput()
{
    u16 joyValue1 = JOY_readJoypad(JOY_1);
    u16 joyValue2 = JOY_readJoypad(JOY_2);

    isPlayer1Moving = FALSE;
    isPlayer2Moving = FALSE;

    // -- Player 1 --//

    if (player1_attack_timer == 0)
    {
        if (joyValue1 & BUTTON_RIGHT)
        {
            player1_x_position += 1;
            isPlayer1Moving = TRUE;
            isPlayer1FacingRight = TRUE;
        }
        else if (joyValue1 & BUTTON_LEFT)
        {
            player1_x_position -= 1;
            isPlayer1Moving = TRUE;
            isPlayer1FacingRight = FALSE;
        }

        if (joyValue1 & BUTTON_UP)
        {
            player1_y_position -= 1;
            isPlayer1Moving = TRUE;
        }
        else if (joyValue1 & BUTTON_DOWN)
        {
            player1_y_position += 1;
            isPlayer1Moving = TRUE;
        }

        if (isPlayer1Moving)
        {
            SPR_setAnim(player1, PLAYER1_ANIMATION_WALK);
        }

        if (!isPlayer1Moving)
        {
            SPR_setAnim(player1, PLAYER1_ANIMATION_IDLE);
        }
    }

    // -- Player 2 --//

    if (player2_attack_timer == 0)
    {
        if (joyValue2 & BUTTON_RIGHT)
        {
            player2_x_position += 1;
            isPlayer2Moving = TRUE;
            isPlayer2FacingRight = FALSE;
        }
        else if (joyValue2 & BUTTON_LEFT)
        {
            player2_x_position -= 1;
            isPlayer2Moving = TRUE;
            isPlayer2FacingRight = TRUE;
        }

        if (joyValue2 & BUTTON_UP)
        {
            player2_y_position -= 1;
            isPlayer2Moving = TRUE;
        }
        else if (joyValue2 & BUTTON_DOWN)
        {
            player2_y_position += 1;
            isPlayer2Moving = TRUE;
        }

        if (isPlayer2Moving)
        {
            SPR_setAnim(player2, PLAYER2_ANIMATION_WALK);
        }

        if (!isPlayer2Moving)
        {
            SPR_setAnim(player2, PLAYER2_ANIMATION_STILL);
        }
    }

    SPR_setHFlip(player1, isPlayer1FacingRight);
    SPR_setHFlip(player2, isPlayer2FacingRight);
    SPR_setPosition(player1, player1_x_position, player1_y_position);
    SPR_setPosition(player2, player2_x_position, player2_y_position);
}

// Pressed once, good for jumping, attack, menu controls
static void joyEvent(u16 joy, u16 changed, u16 state)
{
    u16 joyValue1 = JOY_readJoypad(JOY_1);
    u16 joyValue2 = JOY_readJoypad(JOY_2);

    if (joyValue1)
    {
        if ((changed & state & BUTTON_B) && player1_attack_timer == 0)
        {
            SPR_setAnim(player1, PLAYER1_ANIMATION_UPPER);
            player1_attack_timer += 1;
        }
    }

    if (joyValue2)
    {
        if ((changed & state & BUTTON_B) && player2_attack_timer == 0)
        {
            SPR_setAnim(player2, PLAYER2_ANIMATION_SPIN);
            player2_attack_timer += 1;
        }
    }
}

static void checkAttackTimer()
{
    if (player1_attack_timer > 0 && player1_attack_timer < PLAYER1_ATTACK_DURATION)
    {
        player1_attack_timer += 1;
    }
    else
        player1_attack_timer = 0;

    if (player2_attack_timer > 0 && player2_attack_timer < PLAYER2_ATTACK_DURATION)
    {
        player2_attack_timer += 1;
    }
    else
        player2_attack_timer = 0;
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
    player1 = SPR_addSprite(&axel_spritesheet, player1_x_position, player1_y_position, TILE_ATTR(PAL2, FALSE, FALSE, TRUE));
    SPR_setAnim(player1, PLAYER1_ANIMATION_IDLE);

    PAL_setPalette(PAL3, sonic_spritesheet.palette->data, DMA);
    player2 = SPR_addSprite(&sonic_spritesheet, player2_x_position, player2_y_position, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));
    SPR_setAnim(player2, PLAYER2_ANIMATION_STILL);

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
        handleMoveInput();

        SPR_update();

        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
