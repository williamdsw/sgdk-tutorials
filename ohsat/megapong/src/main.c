#include <genesis.h>
#include <string.h>
#include "../res/resources.h"

// CONSTS

// Edges of the play field

const int LEFT_EDGE = 0;
const int RIGHT_EDGE = 320;
const int TOP_EDGE = 0;
const int BOTTOM_EDGE = 224;

// Paddle / Player

const int PADDLE_POSITION_Y = 200;
const int PADDLE_WIDTH = 32;
const int PADDLE_HEIGHT = 8;

// FIELDS

int currentScore = 0;
char labelScore[6] = "SCORE\0";
char textScore[3] = "0";

bool isGameOn = FALSE;
char startMessage[22] = "PRESS START TO BEGIN!\0";
char resetMessage[37] = "GAME OVER! PRESS START TO PLAY AGAIN!";

Sprite *ball;
int ballPositionX = 100;
int ballPositionY = 100;
int ballVelocityX = 1;
int ballVelocityY = 1;
int ballWidth = 8;
int ballHeight = 8;

Sprite *paddle;
int paddlePositionX = 144;
int paddleVelocityX = 0;

// HELPER FUNCTIONS

// retorna o sinal de um numero
int sign(int x)
{
    return (x > 0) - (x < 0);
}

void updateScoreDisplay()
{
    // Formata a string para receber um valor numerico
    sprintf(textScore, "%d", currentScore);

    // Limpa o texto e desenha de novo
    VDP_clearText(1, 2, 3);
    VDP_drawText(textScore, 1, 2);
}

void showText(char text[])
{
    int x = (20 - strlen(text) / 2);
    VDP_drawText(text, x, 15);
}

void gameOver()
{
    showText(resetMessage);
    isGameOn = FALSE;
}

void startGame()
{
    currentScore = 0;
    updateScoreDisplay();

    ballPositionX = ballPositionY = 0;
    ballVelocityX = ballVelocityY = 1;

    paddlePositionX = 144;

    // Limpa uma area especifica de texto
    VDP_clearTextArea(0, 10, 40, 10);

    isGameOn = TRUE;
}

void moveBall()
{
    // Verifica limites horizontais
    if (ballPositionX < LEFT_EDGE)
    {
        ballPositionX = LEFT_EDGE;
        ballVelocityX = -ballVelocityX;
    }
    else if (ballPositionX + ballWidth > RIGHT_EDGE)
    {
        ballPositionX = RIGHT_EDGE - ballWidth;
        ballVelocityX = -ballVelocityX;
    }

    // Verifica limites verticais
    if (ballPositionY < TOP_EDGE)
    {
        ballPositionY = TOP_EDGE;
        ballVelocityY *= -1;
    }
    else if (ballPositionY + ballHeight > BOTTOM_EDGE)
    {
        gameOver();
    }

    // Verifica colisoes horizontais e verticais
    if (ballPositionX < (paddlePositionX + PADDLE_WIDTH) && (ballPositionX + ballWidth) > paddlePositionX)
    {
        if (ballPositionY < (PADDLE_POSITION_Y + PADDLE_HEIGHT) && (ballPositionY + ballHeight) >= PADDLE_POSITION_Y)
        {
            // Inverte a velocidade
            ballPositionY = PADDLE_POSITION_Y - ballHeight - 1;
            ballVelocityY *= -1;

            // Atualiza pontuacao
            currentScore++;
            updateScoreDisplay();

            // Aumenta velocidade a cada 10 colisoes
            if (currentScore % 10 == 0)
            {
                ballVelocityX += sign(ballVelocityX);
                ballVelocityY += sign(ballVelocityY);
            }
        }
    }

    ballPositionX += ballVelocityX;
    ballPositionY += ballVelocityY;

    // Define nova posicao do sprite baseada nas posicoes x e y
    SPR_setPosition(ball, ballPositionX, ballPositionY);
}

void inputHandler(u16 joystick, u16 wasChanged, u16 wasPressed)
{
    if (joystick == JOY_1)
    {
        // Start pressionado
        if (wasPressed & BUTTON_START)
        {
            if (!isGameOn)
            {
                startGame();
            }
        }

        if (wasPressed & BUTTON_RIGHT)
        {
            // direita
            paddleVelocityX = 3;
        }
        else if (wasPressed & BUTTON_LEFT)
        {
            // esquerda
            paddleVelocityX = -3;
        }
        else
        {
            // quando solta
            if ((wasChanged & BUTTON_RIGHT) | (wasChanged & BUTTON_LEFT))
            {
                paddleVelocityX = 0;
            }
        }
    }
}

void movePaddle()
{
    paddlePositionX += paddleVelocityX;

    // Verifica limites horizontais
    if (paddlePositionX < LEFT_EDGE)
    {
        paddlePositionX = LEFT_EDGE;
    }

    if (paddlePositionX + PADDLE_WIDTH > RIGHT_EDGE)
    {
        paddlePositionX = RIGHT_EDGE - PADDLE_WIDTH;
    }

    // Define nova posicao
    SPR_setPosition(paddle, paddlePositionX, PADDLE_POSITION_Y);
}

// MAIN

int main()
{
    // Inicializa sub sistema de Joystick
    // Define handler de input
    JOY_init();
    JOY_setEventHandler(&inputHandler);

    // Carrega um tileset baseado na imagem importada
    // 1 = posicao do tile na VRAM
    VDP_loadTileSet(bgtile.tileset, 1, DMA);

    // Extrai paleta de cores do 'bgtile', e adiciona ao 'PAL1'
    // VDP_setPalette(PAL1, bgtile.palette->data);
    PAL_setPalette(PAL1, bgtile.palette->data, DMA);

    // Exibe tileset no BG_A na posicao (2,2)
    // TILE_ATTR_FULL (...)
    // - PAL1 = paleta a ser usada pelo tile
    // - prio = permite sobreescrever prioridade de desenhar o tile (BG_A, BG_B)
    // - flipV = inverte o tile verticalmente
    // - flipX = inverte o tile horizontalmente
    // - index = indice do tile na VRAM
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), 2, 2);

    // Desenha uma mapa de tiles retangular aonde:
    // x, y = pontos de partida
    // w, h = dimensoes do retangulo
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), 0, 0, 40, 30);

    // Inicializa a Sprite Engine com parametros default
    // SPR_init (max_sprites, VRAM_size, unpack_buffer_size)
    SPR_init();

    // Adiciona sprite ao objeto
    // spriteDef* = Endereco na memoria do sprite compilado no resources
    // x, y = coordenadas do sprite em pixels
    // TILE_ATRR = atributos do sprite, necessario para setar a paleta
    ball = SPR_addSprite(&ballSprite, 100, 100, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    paddle = SPR_addSprite(&paddleSprite, paddlePositionX, PADDLE_POSITION_Y, TILE_ATTR(PAL1, 0, FALSE, FALSE));

    // Desenha a HUD de score
    VDP_setTextPlane(BG_A);
    VDP_drawText(labelScore, 1, 1);
    updateScoreDisplay();

    showText(startMessage);

    // Loop do jogo
    while (1)
    {
        if (isGameOn == TRUE)
        {
            moveBall();
            movePaddle();
        }

        // Exibe lista atual de sprites
        SPR_update();

        // Espera atualizacao da tela
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}
