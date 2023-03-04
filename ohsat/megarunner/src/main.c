#include <genesis.h>
#include <string.h>
#include <resources.h>

#define ANIMATION_RUN 0
#define ANIMATION_JUMP 1

//------------------------------------------------------------------//
// FIELDS

// Text labels
char MESSAGE_START[22] = "Press START to Begin!";
char MESSAGE_RESET[22] = "Press START to Reset!";

const int SCROLL_SPEED = 2;
const int FLOOR_HEIGHT = 128; // altura do chao
fix16 gravity = FIX16(0.2);

// Score
int currentScore = 0;
char labelScore[6] = "SCORE\0";
char textScore[3] = "0";

// Player
Sprite *player;
const int PLAYER_POSITION_X = 32;
fix16 playerPositionY = FIX16(112); // fix16 e tipo para disfarcar floats
fix16 playerVelocityY = FIX16(0);
int playerHeight = 16;

// Obstacle
Sprite *obstacle;
int obstaclePositionX = 320;
int obstaclePositionY = 128;
int obstacleVelocityX = 0;

// State
bool isGameOn = FALSE;
bool isJumping = FALSE;
bool wasScoreAdded = FALSE;

//------------------------------------------------------------------//
// HELPER FUNCTIONS

void showText(char text[])
{
    int x = (20 - strlen(text) / 2);
    VDP_drawText(text, x, 10);
}

void clearText()
{
    VDP_clearText(0, 10, 32);
}

void updateScoreDisplay()
{
    sprintf(textScore, "%d", currentScore);
    VDP_clearText(1, 2, 3);
    VDP_drawText(textScore, 10, 2);
}

void startGame()
{
    if (isGameOn == FALSE)
    {
        isGameOn = TRUE;
        clearText();
    }

    VDP_drawText(labelScore, 10, 1);
    currentScore = 0;
    updateScoreDisplay();
    obstaclePositionX = 320;
}

void endGame()
{
    if (isGameOn == TRUE)
    {
        showText(MESSAGE_RESET);
        isGameOn = FALSE;
    }
}

void joystickHandler(u16 joystick, u16 wasChanged, u16 wasPressed)
{
    if (joystick == JOY_1)
    {
        // Inicializa jogo
        if (wasPressed & BUTTON_START)
        {
            if (isGameOn == FALSE)
            {
                startGame();
            }
        }

        // Pulo
        if (wasPressed & BUTTON_C)
        {
            if (isJumping == FALSE)
            {
                isJumping = TRUE;
                playerVelocityY = FIX16(-4);
                SPR_setAnim(player, ANIMATION_JUMP);
            }
        }
    }
}

//------------------------------------------------------------------//
// MAIN

int main()
{
    // Inicializa input
    JOY_init();
    JOY_setEventHandler(&joystickHandler);

    // Define o tamanho do plano dos tiles
    VDP_setPlanSize(32, 32);

    // Permite usar scrolling no plano horizonal e vertical
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    // Carrega tiles
    VDP_loadTileSet(floorImage.tileset, 1, DMA);
    VDP_loadTileSet(wallImage.tileset, 2, DMA);
    VDP_loadTileSet(lightPoleImage.tileset, 3, DMA);

    PAL_setPalette(PAL1, lightPoleImage.palette->data, DMA);
    PAL_setPalette(PAL2, runnerSprite.palette->data, DMA);

    // Define paleta de cores do background baseado numa cor de valor hexadecimal
    // VDP_setPaletteColor(0, RGB24_TO_VDPCOLOR(0x6dc2ca));
    PAL_setColor(0, 0x0844);

    showText(MESSAGE_START);

    // Adiciona linha de tiles
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), 0, 16, 32, 1);
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, TRUE, 2), 0, 17, 32, 14);

    // Parecido com fillTileMapRect, mas calcula quantos tiles serao necessarios
    VDP_fillTileMapRectInc(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 3), 15, 13, 2, 3);

    // Inicializa player
    SPR_init();
    player = SPR_addSprite(&runnerSprite, PLAYER_POSITION_X, playerPositionY, TILE_ATTR(PAL2, 0, FALSE, FALSE));
    SPR_setAnim(player, ANIMATION_RUN);

    // Inicializa obstaculo
    obstacle = SPR_addSprite(&rockSprite, obstaclePositionX, obstaclePositionY, TILE_ATTR(PAL2, 0, FALSE, FALSE));

    int offset = 0;

    // Loop do jogo
    while (1)
    {
        if (isGameOn == TRUE)
        {
            // Realiza um scroll horizontal no Plano B com base no valor offset de distancia de frame para frame
            VDP_setHorizontalScroll(BG_B, offset -= SCROLL_SPEED);

            if (offset <= -256)
            {
                offset = 0;
            }

            // Atualiza o sprite a cada frame
            SPR_update();

            // Movimenta obstaculo
            obstacleVelocityX = -SCROLL_SPEED;
            obstaclePositionX += obstacleVelocityX;
            if (obstaclePositionX < -8)
            {
                obstaclePositionX = 320;
            }

            // Aplica velocidade com resultado da soma
            playerPositionY = fix16Add(playerPositionY, playerVelocityY);

            // Aplica gravidade
            if (isJumping == TRUE)
            {
                playerVelocityY = fix16Add(playerVelocityY, gravity);
            }

            // Verifica se esta no chao
            if (isJumping == TRUE && fix16ToInt(playerPositionY) + playerHeight >= (FLOOR_HEIGHT))
            {
                isJumping = FALSE;
                wasScoreAdded = FALSE;
                playerVelocityY = FIX16(0);
                playerPositionY = intToFix16(FLOOR_HEIGHT - playerHeight);
                SPR_setAnim(player, ANIMATION_RUN);
            }

            // Verifica colisao com obstaculo
            if (PLAYER_POSITION_X < (obstaclePositionX + 8) && (PLAYER_POSITION_X + 8) > obstaclePositionX)
            {
                if (isJumping == FALSE)
                {
                    endGame();
                }
                else
                {
                    if (wasScoreAdded == FALSE)
                    {
                        currentScore++;
                        updateScoreDisplay();
                        wasScoreAdded = TRUE;
                    }
                }
            }

            // Atualiza posicoes dos objetos com base em x & y
            SPR_setPosition(obstacle, obstaclePositionX, 120);
            SPR_setPosition(player, PLAYER_POSITION_X, fix16ToInt(playerPositionY));
        }

        // VDP_waitVSync();
        SYS_doVBlankProcess();
    }

    return (0);
}
