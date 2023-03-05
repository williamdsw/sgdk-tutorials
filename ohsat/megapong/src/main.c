#include <genesis.h>
#include <string.h>
#include <resources.h>
#include "screen_edges.h"
#include "messages.h"
#include "paddle.h"
#include "ball_props.h"

// FIELDS

int currentScore = 0;
char textScore[3] = "0";

bool isGameOn = FALSE;

Sprite *ball;
BallProps ballProps;

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
    showText(RESET_MESSAGE);
    isGameOn = FALSE;
}

void startGame()
{
    currentScore = 0;
    updateScoreDisplay();

    ballProps.position.x = ballProps.position.y = 0;
    ballProps.velocity.x = ballProps.velocity.y = 1;
    ballProps.frames = 0;
    ballProps.isFlashing = FALSE;

    paddlePositionX = 144;

    // Limpa uma area especifica de texto
    VDP_clearTextArea(0, 10, 40, 10);

    isGameOn = TRUE;
}

void moveBall()
{
    // Verifica limites horizontais
    if (ballProps.position.x < SCREEN_LEFT_EDGE)
    {
        ballProps.position.x = SCREEN_LEFT_EDGE;
        ballProps.velocity.x = -ballProps.velocity.x;
    }
    else if (ballProps.position.x + BALL_WIDTH > SCREEN_RIGHT_EDGE)
    {
        ballProps.position.x = SCREEN_RIGHT_EDGE - BALL_WIDTH;
        ballProps.velocity.x = -ballProps.velocity.x;
    }

    // Verifica limites verticais
    if (ballProps.position.y < SCREEN_TOP_EDGE)
    {
        ballProps.position.y = SCREEN_TOP_EDGE;
        ballProps.velocity.y *= -1;
    }
    else if (ballProps.position.y + BALL_HEIGHT > SCREEN_BOTTOM_EDGE)
    {
        gameOver();
    }

    // Verifica colisoes horizontais e verticais
    if (ballProps.position.x < (paddlePositionX + PADDLE_WIDTH) && (ballProps.position.x + BALL_WIDTH) > paddlePositionX)
    {
        if (ballProps.position.y < (PADDLE_POSITION_Y + PADDLE_HEIGHT) && (ballProps.position.y + BALL_HEIGHT) >= PADDLE_POSITION_Y)
        {
            // Inverte a velocidade
            ballProps.position.y = PADDLE_POSITION_Y - BALL_HEIGHT - 1;
            ballProps.velocity.y *= -1;

            // Atualiza pontuacao
            currentScore++;
            updateScoreDisplay();
            ballProps.isFlashing = TRUE;

            // Aumenta velocidade a cada 10 colisoes
            if (currentScore % 10 == 0)
            {
                ballProps.velocity.x += sign(ballProps.velocity.x);
                ballProps.velocity.y += sign(ballProps.velocity.y);
            }
        }
    }

    ballProps.position.x += ballProps.velocity.x;
    ballProps.position.y += ballProps.velocity.y;

    // Define nova posicao do sprite baseada nas posicoes x e y
    SPR_setPosition(ball, ballProps.position.x, ballProps.position.y);
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
    if (paddlePositionX < SCREEN_LEFT_EDGE)
    {
        paddlePositionX = SCREEN_LEFT_EDGE;
    }

    if (paddlePositionX + PADDLE_WIDTH > SCREEN_RIGHT_EDGE)
    {
        paddlePositionX = SCREEN_RIGHT_EDGE - PADDLE_WIDTH;
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

    // Recupera cor da bola
    ballProps.color = PAL_getColor(22);

    // Desenha a HUD de score
    VDP_setTextPlane(BG_A);
    VDP_drawText(LABEL_SCORE, 1, 1);
    updateScoreDisplay();

    showText(START_MESSAGE);

    // Loop do jogo
    while (1)
    {
        if (isGameOn == TRUE)
        {
            moveBall();
            movePaddle();

            if (ballProps.isFlashing)
            {
                ballProps.frames++;

                // A cada 4 frames
                if (ballProps.frames % 4 == 0)
                {
                    PAL_setColor(22, ballProps.color);
                }
                else if (ballProps.frames % 2 == 0) // A cada 2 frames
                {
                    PAL_setColor(22, RGB24_TO_VDPCOLOR(0xffffff));
                }

                // Reseta cor depois de 30 frames
                if (ballProps.frames > 30)
                {
                    ballProps.isFlashing = FALSE;
                    ballProps.frames = 0;
                    PAL_setColor(22, ballProps.color);
                }
            }
        }

        // Exibe lista atual de sprites
        SPR_update();

        // Espera atualizacao da tela
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }

    return (0);
}
