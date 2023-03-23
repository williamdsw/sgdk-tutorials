#include <genesis.h>
#include <string.h>
#include <resources.h>
#include "messages.h"
#include "player_props.h"
#include "obstacle_props.h"

// FIELDS

const int SCROLL_SPEED = 2;
const int FLOOR_HEIGHT = 128; // altura do chao
fix16 gravity = FIX16(0.2);

// Score
int currentScore = 0;
char textScore[3] = "0";

// Player
Sprite *player;
PlayerProps playerProps;

// Obstacle
Sprite *obstacle;
ObstacleProps obstacleProps;

// State
bool isGameOn = FALSE;
bool isJumping = FALSE;
bool wasScoreAdded = FALSE;

// HELPER FUNCTIONS

void initProps()
{
    // fix16 e tipo para disfarcar floats
    playerProps.positionY = FIX16(112);
    playerProps.velocityY = FIX16(0);
    playerProps.height = 16;

    obstacleProps.position.x = 320;
    obstacleProps.position.y = 128;
    obstacleProps.velocity.x = 0;
}

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
    if (!isGameOn)
    {
        isGameOn = TRUE;
        clearText();
    }

    VDP_drawText(LABEL_SCORE, 10, 1);
    currentScore = 0;
    updateScoreDisplay();
    obstacleProps.position.x = 320;
}

void endGame()
{
    if (isGameOn)
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
            if (!isGameOn)
            {
                startGame();
            }
        }

        // Pulo
        if (wasPressed & BUTTON_C)
        {
            if (!isJumping)
            {
                isJumping = TRUE;
                playerProps.velocityY = FIX16(-4);
                SPR_setAnim(player, PLAYER_ANIMATION_JUMP);
            }
        }
    }
}

int main()
{
    initProps();

    // Inicializa input
    JOY_init();
    JOY_setEventHandler(&joystickHandler);

    // Define o tamanho do plano dos tiles
    VDP_setPlaneSize(32, 32, TRUE);

    // Permite usar scrolling no plano horizonal e vertical
    VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);

    // Carrega tiles
    VDP_loadTileSet(floorImage.tileset, 1, DMA);
    VDP_loadTileSet(wallImage.tileset, 2, DMA);
    VDP_loadTileSet(lightPoleImage.tileset, 3, DMA);

    PAL_setPalette(PAL1, lightPoleImage.palette->data, DMA);
    PAL_setPalette(PAL2, runnerSprite.palette->data, DMA);

    // Define paleta de cores do background baseado numa cor de valor hexadecimal
    PAL_setColor(0, RGB24_TO_VDPCOLOR(0x6dc2ca));

    showText(MESSAGE_START);

    // Adiciona linha de tiles
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), 0, 16, 32, 1); // Chao
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, TRUE, 2), 0, 17, 32, 2);  // Parede

    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), 0, 19, 32, 1); // Chao na frente
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, TRUE, 2), 0, 20, 32, 8);  // Parede na frente

    // Parecido com fillTileMapRect, mas calcula quantos tiles serao necessarios
    VDP_fillTileMapRectInc(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 3), 15, 13, 2, 3); // Luzes

    // Inicializa player
    SPR_init();
    player = SPR_addSprite(&runnerSprite, PLAYER_POSITION_X, playerProps.positionY, TILE_ATTR(PAL2, 0, FALSE, FALSE));
    SPR_setAnim(player, PLAYER_ANIMATION_RUN);

    // Inicializa obstaculo
    obstacle = SPR_addSprite(&rockSprite, obstacleProps.position.x, obstacleProps.position.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));

    // Numero de 15 linhas com valores do scroll: 3 linhas para luzes, 2 para chao e 10 para paredes
    s16 scrollValues[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Loop do jogo
    while (1)
    {
        if (isGameOn)
        {
            // Definiindo qual tile utilizar para scroll horizontal
            VDP_setHorizontalScrollTile(BG_B, 13, scrollValues, 15, CPU);

            // Movemento os tiles por velocidades diferentes
            for (int scrollIndex = 0; scrollIndex < 15; scrollIndex++)
            {
                if (scrollIndex <= 5)
                {
                    scrollValues[scrollIndex] -= SCROLL_SPEED;
                }
                else
                {
                    scrollValues[scrollIndex] -= SCROLL_SPEED + 1;
                }

                if (scrollValues[scrollIndex] <= -256)
                {
                    scrollValues[scrollIndex] = 0;
                }
            }

            // Atualiza o sprite a cada frame
            SPR_update();

            // Movimenta obstaculo
            obstacleProps.velocity.x = -SCROLL_SPEED;
            obstacleProps.position.x += obstacleProps.velocity.x;
            if (obstacleProps.position.x < -8)
            {
                obstacleProps.position.x = 320;
            }

            // Aplica velocidade com resultado da soma
            playerProps.positionY = fix16Add(playerProps.positionY, playerProps.velocityY);

            // Aplica gravidade
            if (isJumping)
            {
                playerProps.velocityY = fix16Add(playerProps.velocityY, gravity);
            }

            // Verifica se esta no chao
            if (isJumping && fix16ToInt(playerProps.positionY) + playerProps.height >= (FLOOR_HEIGHT))
            {
                isJumping = FALSE;
                wasScoreAdded = FALSE;
                playerProps.velocityY = FIX16(0);
                playerProps.positionY = intToFix16(FLOOR_HEIGHT - playerProps.height);
                SPR_setAnim(player, PLAYER_ANIMATION_RUN);
            }

            // Verifica colisao com obstaculo
            if (PLAYER_POSITION_X < (obstacleProps.position.x + 8) && (PLAYER_POSITION_X + 8) > obstacleProps.position.x)
            {
                if (!isJumping)
                {
                    endGame();
                }
                else
                {
                    if (!wasScoreAdded)
                    {
                        currentScore++;
                        updateScoreDisplay();
                        wasScoreAdded = TRUE;
                    }
                }
            }

            // Atualiza posicoes dos objetos com base em x & y
            SPR_setPosition(obstacle, obstacleProps.position.x, 120);
            SPR_setPosition(player, PLAYER_POSITION_X, fix16ToInt(playerProps.positionY));
        }

        SYS_doVBlankProcess();
    }

    return (0);
}
