
#include <genesis.h>
#include <resources.h>
#include "defines.h"
#include "entity.h"
#include "coin.h"
#include "levels.h"

typedef u8 map[MAP_HEIGHT][MAP_WIDTH];

Entity player = {{0, 0}, {0, 0}, 8, 8, 0, FALSE, NONE, NULL, "PLAYER"};
Coin coins[MAX_COINS];
Point exitLocation = {0, 0};

u8 numberOfCoinsCollected = 0;
char hudString[10] = "";
bool isExitUnlocked = FALSE;

u8* currentLevel;
static u8 currentLevelIndex = 0;
map *levelList[3];

void initGraphics()
{
    // Tilesheet
    VDP_loadTileSet(imgFloorTiles.tileset, 1, DMA);
    PAL_setPalette(PAL1, imgFloorTiles.palette->data, DMA);

    // Player
    PAL_setPalette(PAL2, sprPlayer.palette->data, DMA);
}

void initAudios()
{
    XGM_setPCM(SFX_COIN, sfxCoin, sizeof(sfxCoin));
    XGM_setPCM(SFX_UNLOCK, sfxUnlock, sizeof(sfxUnlock));
}

void placePlayer(u16 x, u16 y)
{
    player.tilePosition.x = x;
    player.tilePosition.y = y;
    player.position.x = player.tilePosition.x * LEVEL_TILE_SIZE;
    player.position.y = player.tilePosition.y * LEVEL_TILE_SIZE;
    player.sprite = SPR_addSprite(&sprPlayer, player.position.x, player.position.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
}

void placeCoin(Coin *coin, u16 x, u16 y)
{
    coin->position.x = x * LEVEL_TILE_SIZE;
    coin->position.y = y * LEVEL_TILE_SIZE;
    coin->size.height = 8;
    coin->size.width = 8;
    coin->health = 1;
    coin->sprite = SPR_addSprite(&sprCoin, coin->position.x, coin->position.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
}

int getTileAtXY(u16 x, u16 y)
{
    return *(currentLevel + (y * MAP_WIDTH + x));
}

void updateScoreDisplay()
{
    sprintf(hudString, "SCORE: %d", numberOfCoinsCollected);
    VDP_clearText(0, 0, 10);
    VDP_drawText(hudString, 8, 0);
}

void unlockExit()
{
    isExitUnlocked = TRUE;
    VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, 3), exitLocation.x, exitLocation.y);
    XGM_startPlayPCM(SFX_UNLOCK, 1, SOUND_PCM_CH2);
}

void movePlayerInTile(MoveDirection nextDirection)
{
    if (!player.isMoving)
    {
        switch (nextDirection)
        {
        case UP:
        {
            if (player.tilePosition.y > 0 && getTileAtXY(player.tilePosition.x, player.tilePosition.y - 1) != SOLID_TILE)
            {
                player.tilePosition.y -= 1;
                player.isMoving = TRUE;
                player.moveDirection = nextDirection;
                SPR_setAnim(player.sprite, ANIMATION_UP);
            }

            break;
        }

        case DOWN:
        {
            if (player.tilePosition.y < MAP_HEIGHT - 1 && getTileAtXY(player.tilePosition.x, player.tilePosition.y + 1) != SOLID_TILE)
            {
                player.tilePosition.y += 1;
                player.isMoving = TRUE;
                player.moveDirection = nextDirection;
                SPR_setAnim(player.sprite, ANIMATION_DOWN);
            }

            break;
        }

        case LEFT:
        {
            if (player.tilePosition.x > 0 && getTileAtXY(player.tilePosition.x - 1, player.tilePosition.y) != SOLID_TILE)
            {
                player.tilePosition.x -= 1;
                player.isMoving = TRUE;
                player.moveDirection = nextDirection;
                SPR_setAnim(player.sprite, ANIMATION_SIDE);
                SPR_setHFlip(player.sprite, TRUE);
            }

            break;
        }

        case RIGHT:
        {
            if (player.tilePosition.x < MAP_HEIGHT - 1 && getTileAtXY(player.tilePosition.x + 1, player.tilePosition.y) != SOLID_TILE)
            {
                player.tilePosition.x += 1;
                player.isMoving = TRUE;
                player.moveDirection = nextDirection;
                SPR_setAnim(player.sprite, ANIMATION_SIDE);
                SPR_setHFlip(player.sprite, FALSE);
            }

            break;
        }

        default:
            break;
        }
    }
}

void movePlayerOnPosition()
{
    if (player.isMoving)
    {
        switch (player.moveDirection)
        {
        case UP:
            player.position.y -= 1;
            break;
        case DOWN:
            player.position.y += 1;
            break;
        case LEFT:
            player.position.x -= 1;
            break;
        case RIGHT:
            player.position.x += 1;
            break;
        default:
            break;
        }
    }
}

void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if (state & BUTTON_UP)
            movePlayerInTile(UP);
        else if (state & BUTTON_DOWN)
            movePlayerInTile(DOWN);
        else if (state & BUTTON_LEFT)
            movePlayerInTile(LEFT);
        else if (state & BUTTON_RIGHT)
            movePlayerInTile(RIGHT);
    }
}

void clearLevel()
{
    VDP_clearPlane(BG_B, TRUE);
    VDP_clearSprites();
    numberOfCoinsCollected = 0;
    updateScoreDisplay();
    isExitUnlocked = FALSE;
}

void loadLevel()
{
    clearLevel();
    currentLevel = levelList[currentLevelIndex];

    u8 x = 0;
    u8 y = 0;
    u8 i = 0;
    u8 total = MAP_HEIGHT * MAP_WIDTH;
    u8 tile = 0;
    u8 coinIndex = 0;
    Coin *currentCoin = coins;

    SPR_init();

    for (i = 0; i < total; i++)
    {
        tile = *(currentLevel + i);

        if (tile == SPAWN_TILE)
        {
            placePlayer(x, y);
            VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), x, y);
        }
        else if (tile == COIN_TILE)
        {
            if (coinIndex < MAX_COINS)
            {
                currentCoin = &coins[coinIndex];
                placeCoin(currentCoin, x, y);
                coinIndex++;
            }

            VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), x, y);
        }
        else if (tile == EXIT_TILE)
        {
            exitLocation.x = x;
            exitLocation.y = y;
            VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), x, y);
        }
        else
        {
            VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, tile + 1), x, y);
        }

        x++;
        if (x >= MAP_WIDTH)
        {
            y++;
            x = 0;
        }
    }
}

int main()
{
    levelList[0] = level1TilesIndexes;
    levelList[1] = level2TilesIndexes;
    levelList[2] = level3TilesIndexes;

    initGraphics();
    loadLevel();

    JOY_init();
    JOY_setEventHandler(&myJoyHandler);

    Coin *coinToCheck;

    while (1)
    {
        movePlayerOnPosition();

        if (player.position.x % LEVEL_TILE_SIZE == 0 && player.position.y % LEVEL_TILE_SIZE == 0)
        {
            player.isMoving = FALSE;

            if (isExitUnlocked && player.tilePosition.x == exitLocation.x && player.tilePosition.y == exitLocation.y)
            {
                currentLevelIndex++;
                if (currentLevelIndex >= NUMBER_OF_LEVELS)
                {
                    currentLevelIndex = 0;
                }

                loadLevel();
            }
        }

        u8 i = 0;
        for (i = 0; i < MAX_COINS; i++)
        {
            coinToCheck = &coins[i];

            // Regular AABB check
            bool playerSmallerThanCoinInX = (player.position.x < coinToCheck->position.x + coinToCheck->size.width);
            bool playerBiggerThanCoinInX = (player.position.x + player.size.width > coinToCheck->position.x);
            bool playerSmallerThanCoinInY = (player.position.y < coinToCheck->position.y + coinToCheck->size.height);
            bool playerBiggerThanCoinInY = (player.position.y + player.size.height > coinToCheck->position.y);
            if (playerSmallerThanCoinInX && playerBiggerThanCoinInX && playerSmallerThanCoinInY && playerBiggerThanCoinInY)
            {
                if (coinToCheck->health > 0)
                {
                    coinToCheck->health = 0;
                    SPR_setVisibility(coinToCheck->sprite, HIDDEN);
                    numberOfCoinsCollected++;
                    XGM_startPlayPCM(SFX_COIN, 1, SOUND_PCM_CH2);
                    updateScoreDisplay();

                    if (numberOfCoinsCollected == MAX_COINS)
                    {
                        unlockExit();
                    }
                }
            }
        }

        SPR_update();
        SPR_setPosition(player.sprite, player.position.x, player.position.y);
        SYS_doVBlankProcess();
    }

    return (0);
}