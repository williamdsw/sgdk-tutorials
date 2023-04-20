
#include <genesis.h>
#include <resources.h>

u16 ind = TILE_USER_INDEX;
Map *level_1_map;
int x = 0;
int y = 768;

Sprite *spr_player;
fix32 player_x = FIX32(10);
fix32 player_y = FIX32(160);
fix32 player_vel = FIX32(2);

int current_camera_x = 0;
int current_camera_y = 0;

// buggy
#define HOW_FAR_TO_LEFT_BEFORE_CAMERA_MOVES 121
#define HOW_FAR_TO_RIGHT_BEFORE_CAMERA_MOVES 122
#define HOW_FAR_TO_TOP_BEFORE_CAMERA_MOVES 115
#define HOW_FAR_TO_BOTTOM_BEFORE_CAMERA_MOVES 116

#define HORIZONTAL_RESOLUTION 256
#define VERTICAL_RESOLUTION 224

#define MAP_WIDTH 10240
#define MAP_HEIGHT 1280

#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 32

// functions prototypes
static void handleInput();
static void handleCamera();

int main()
{
    VDP_setScreenWidth256();
    SPR_init();

    PAL_setPalette(PAL0, our_palette.data, DMA);
    PAL_setPalette(PAL1, obj_mario.palette->data, DMA);

    VDP_loadTileSet(&our_tileset, ind, DMA);
    level_1_map = MAP_create(&our_level_map, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind));
    ind += our_tileset.numTile;
    // MAP_scrollTo(level_1_map, x, y);

    spr_player = SPR_addSprite(&obj_mario, fix32ToInt(player_x), fix32ToInt(player_y), TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind));
    SPR_setAnim(spr_player, 0);
    SPR_update();

    while (1)
    {
        handleInput();
        handleCamera();

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
        player_x -= player_vel;
        SPR_setAnim(spr_player, 1);
        SPR_setHFlip(spr_player, TRUE);
    }
    else if (value & BUTTON_RIGHT)
    {
        player_x += player_vel;
        SPR_setAnim(spr_player, 1);
        SPR_setHFlip(spr_player, FALSE);
    }
    else if (value & BUTTON_DOWN)
    {
        SPR_setAnim(spr_player, 3);
    }

    if (!value)
    {
        SPR_setAnim(spr_player, 0);
    }
}

static void handleCamera()
{
    // stop player from leaving map
    if (player_x < FIX32(0))
    {
        player_x = FIX32(0);
    }
    else if (player_x > FIX32(MAP_WIDTH - PLAYER_WIDTH))
    {
        player_x = FIX32(MAP_WIDTH - PLAYER_WIDTH);
    }

    if (player_y < FIX32(0))
    {
        player_y = FIX32(0);
    }
    else if (player_y > FIX32(MAP_HEIGHT - PLAYER_HEIGHT))
    {
        player_y = FIX32(MAP_HEIGHT - PLAYER_HEIGHT);
    }

    // position of player on map as a whole number
    int player_x_map = fix32ToInt(player_x);
    int player_y_map = fix32ToInt(player_y);

    // player position on screen
    int player_x_position_on_screen = player_x_map - current_camera_x;
    int player_y_position_on_screen = player_y_map - current_camera_y;

    // new camera position
    int new_camera_x;
    int new_camera_y;

    // calculate new camera position in x
    if (player_x_position_on_screen > HOW_FAR_TO_RIGHT_BEFORE_CAMERA_MOVES)
    {
        new_camera_x = player_x_map - HOW_FAR_TO_RIGHT_BEFORE_CAMERA_MOVES;
    }
    else if (player_x_position_on_screen < HOW_FAR_TO_LEFT_BEFORE_CAMERA_MOVES)
    {
        new_camera_x = player_x_map - HOW_FAR_TO_LEFT_BEFORE_CAMERA_MOVES;
    }
    else
    {
        new_camera_x = current_camera_x;
    }

    // calculate new camera position in y
    if (player_y_position_on_screen > HOW_FAR_TO_BOTTOM_BEFORE_CAMERA_MOVES)
    {
        new_camera_y = player_y_map - HOW_FAR_TO_BOTTOM_BEFORE_CAMERA_MOVES;
    }
    else if (player_y_position_on_screen < HOW_FAR_TO_TOP_BEFORE_CAMERA_MOVES)
    {
        new_camera_y = player_y_map - HOW_FAR_TO_TOP_BEFORE_CAMERA_MOVES;
    }
    else
    {
        new_camera_y = current_camera_y;
    }

    // stop camera from going beyong boundaries of map
    if (new_camera_x < 0)
    {
        new_camera_x = 0;
    }
    else if (new_camera_x > (MAP_WIDTH - HORIZONTAL_RESOLUTION))
    {
        new_camera_x = MAP_WIDTH - HORIZONTAL_RESOLUTION;
    }

    if (new_camera_y < 0)
    {
        new_camera_y = 0;
    }
    else if (new_camera_y > (MAP_HEIGHT - VERTICAL_RESOLUTION))
    {
        new_camera_y = MAP_HEIGHT - VERTICAL_RESOLUTION;
    }

    // check if camera needs to scroll and do the scroll
    if ((current_camera_x != new_camera_x) || (current_camera_y != new_camera_y))
    {
        current_camera_x = new_camera_x;
        current_camera_y = new_camera_y;
        MAP_scrollTo(level_1_map, current_camera_x, current_camera_y);
        kprintf("current_camera_x: %d, current_camera_y: %d\0", current_camera_x, current_camera_y);
    }

    SPR_setPosition(spr_player, fix32ToInt(player_x) - new_camera_x, fix32ToInt(player_y) - new_camera_y);
}