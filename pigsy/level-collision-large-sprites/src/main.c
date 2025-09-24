#include <genesis.h>
#include <resources.h>

// Tilemap
// --------------------------------------------------
const u16 LEVEL_COLLISION[2232] =
    {
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

// MAP_WIDTH / 16
const u16 LENGTH_OF_LEVEL_COLLISION_ARRAY = 72;

u16 ind = TILE_USER_INDEX;
Map *level_map;

Sprite *spr_player;
fix32 player_x = FIX32(300);
fix32 player_y = FIX32(150);
fix32 player_x_velocity = FIX32(1.5);
fix32 player_y_velocity = FIX32(0);
bool is_player_moving_left = FALSE;
bool is_player_moving_right = FALSE;
bool is_player_jumping = FALSE;

s16 current_camera_x = 0;
s16 current_camera_y = 0;

fix32 gravity = FIX32(0.8);
fix32 jump_velocity = FIX32(14);
fix32 terminal_velocity = FIX32(13);

// buggy
#define HOW_FAR_TO_LEFT_BEFORE_CAMERA_MOVES 150
#define HOW_FAR_TO_RIGHT_BEFORE_CAMERA_MOVES 151
#define HOW_FAR_TO_TOP_BEFORE_CAMERA_MOVES 115
#define HOW_FAR_TO_BOTTOM_BEFORE_CAMERA_MOVES 116

#define HORIZONTAL_RESOLUTION 320
#define VERTICAL_RESOLUTION 224

#define MAP_WIDTH 1152
#define MAP_HEIGHT 496

#define PLAYER_WIDTH 48
#define PLAYER_HEIGHT 64
#define PLAYER_COLLISION_BOX_LEFT 1;
#define PLAYER_COLLISION_BOX_RIGHT 32;
#define PLAYER_COLLISION_BOX_TOP 5;
#define PLAYER_COLLISION_BOX_BOTTOM 64;

#define SOLID_TILE 1
#define EMPTY_TILE 0

// functions prototypes
static void handleInput();
static void handleCamera();
static void collisionDetection();
static void joyEventHandler(u16 joy, u16 changed, u16 state);

int main()
{
    SPR_init();
    JOY_setEventHandler(joyEventHandler);

    PAL_setPalette(PAL0, background_pal.data, DMA);
    PAL_setPalette(PAL2, player_img.palette->data, DMA);

    VDP_loadTileSet(&background_tileset, ind, DMA);
    level_map = MAP_create(&background_map, BG_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind));
    ind += background_tileset.numTile;

    MAP_scrollTo(level_map, 0, 0);

    spr_player = SPR_addSprite(&player_img, F32_toInt(player_x), F32_toInt(player_y), TILE_ATTR(PAL2, FALSE, FALSE, FALSE));

    while (1)
    {
        handleInput();
        collisionDetection();
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
        is_player_moving_left = TRUE;
        is_player_moving_right = FALSE;
    }
    else if (value & BUTTON_RIGHT)
    {
        is_player_moving_left = FALSE;
        is_player_moving_right = TRUE;
    }
    else
    {
        is_player_moving_left = FALSE;
        is_player_moving_right = FALSE;
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
    s16 player_x_map = F32_toInt(player_x);
    s16 player_y_map = F32_toInt(player_y);

    // player position on screen
    s16 player_x_position_on_screen = player_x_map - current_camera_x;
    s16 player_y_position_on_screen = player_y_map - current_camera_y;

    // new camera position
    s16 new_camera_x;
    s16 new_camera_y;

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

        MAP_scrollTo(level_map, current_camera_x, current_camera_y);
    }

    SPR_setPosition(spr_player, F32_toInt(player_x) - new_camera_x, F32_toInt(player_y) - new_camera_y);
}

static void collisionDetection()
{
    s16 player_left_collision_coordinate;
    s16 player_right_collision_coordinate;
    s16 player_top_collision_coordinate = F32_toInt(player_y) + PLAYER_COLLISION_BOX_TOP;
    s16 player_bottom_collision_coordinate = F32_toInt(player_y) + PLAYER_COLLISION_BOX_BOTTOM;

    s16 x_tile_coordinate_left_collision_player;
    s16 x_tile_coordinate_right_collision_player;
    s16 y_tile_coordinate_top_collision_player = player_top_collision_coordinate >> 4;
    s16 y_tile_coordinate_bottom_collision_player = player_bottom_collision_coordinate >> 4;
    s16 y_tile_coordinate_middle_upper_collision_player = y_tile_coordinate_top_collision_player + 1;
    s16 y_tile_coordinate_middle_lower_collision_player = y_tile_coordinate_top_collision_player + 2;
    s16 y_tile_coordinate_middle_lower2_collision_player = y_tile_coordinate_top_collision_player + 3;

    u16 array_index_top_left_collision_box;
    u16 array_index_top_right_collision_box;
    u16 array_index_bottom_left_collision_box;
    u16 array_index_bottom_right_collision_box;
    u16 array_index_middle_upper_right_collision_box;
    u16 array_index_middle_lower_right_collision_box;
    u16 array_index_middle_lower_right2_collision_box;
    u16 array_index_middle_upper_left_collision_box;
    u16 array_index_middle_lower_left_collision_box;
    u16 array_index_middle_lower_left2_collision_box;

    u8 tile_collision_type_top_left;
    u8 tile_collision_type_top_right;
    u8 tile_collision_type_bottom_left;
    u8 tile_collision_type_bottom_right;
    u8 tile_collision_type_middle_upper_right;
    u8 tile_collision_type_middle_lower_right;
    u8 tile_collision_type_middle_lower2_right;
    u8 tile_collision_type_middle_upper_left;
    u8 tile_collision_type_middle_lower_left;
    u8 tile_collision_type_middle_lower2_left;

    s16 blocked_coordinate;

    if (is_player_moving_left)
    {
        player_x -= player_x_velocity;

        player_left_collision_coordinate = F32_toInt(player_x) + PLAYER_COLLISION_BOX_LEFT;
        x_tile_coordinate_left_collision_player = player_left_collision_coordinate >> 4;
        array_index_top_left_collision_box = x_tile_coordinate_left_collision_player + (y_tile_coordinate_top_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
        array_index_bottom_left_collision_box = x_tile_coordinate_left_collision_player + (y_tile_coordinate_bottom_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
        tile_collision_type_top_left = LEVEL_COLLISION[array_index_top_left_collision_box];
        tile_collision_type_bottom_left = LEVEL_COLLISION[array_index_bottom_left_collision_box];

        array_index_middle_upper_left_collision_box = x_tile_coordinate_left_collision_player + (y_tile_coordinate_middle_upper_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
        tile_collision_type_middle_upper_left = LEVEL_COLLISION[array_index_middle_upper_left_collision_box];

        array_index_middle_lower_left_collision_box = x_tile_coordinate_left_collision_player + (y_tile_coordinate_middle_lower_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
        tile_collision_type_middle_lower_left = LEVEL_COLLISION[array_index_middle_lower_left_collision_box];

        array_index_middle_lower_left2_collision_box = x_tile_coordinate_left_collision_player + (y_tile_coordinate_middle_lower2_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
        tile_collision_type_middle_lower2_left = LEVEL_COLLISION[array_index_middle_lower_left2_collision_box];

        if (tile_collision_type_top_left == SOLID_TILE ||
            tile_collision_type_bottom_left == SOLID_TILE ||
            tile_collision_type_middle_upper_left == SOLID_TILE ||
            tile_collision_type_middle_lower_left == SOLID_TILE ||
            tile_collision_type_middle_lower2_left == SOLID_TILE)
        {
            blocked_coordinate = (x_tile_coordinate_left_collision_player << 4) + 16 - PLAYER_COLLISION_BOX_LEFT;
            player_x = FIX32(blocked_coordinate);
        }
    }
    else if (is_player_moving_right)
    {
        player_x += player_x_velocity;

        player_right_collision_coordinate = F32_toInt(player_x) + PLAYER_COLLISION_BOX_RIGHT;
        x_tile_coordinate_right_collision_player = player_right_collision_coordinate >> 4;
        array_index_top_right_collision_box = x_tile_coordinate_right_collision_player + (y_tile_coordinate_top_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
        array_index_bottom_right_collision_box = x_tile_coordinate_right_collision_player + (y_tile_coordinate_bottom_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
        tile_collision_type_top_right = LEVEL_COLLISION[array_index_top_right_collision_box];
        tile_collision_type_bottom_right = LEVEL_COLLISION[array_index_bottom_right_collision_box];

        array_index_middle_upper_right_collision_box = x_tile_coordinate_right_collision_player + (y_tile_coordinate_middle_upper_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
        tile_collision_type_middle_upper_right = LEVEL_COLLISION[array_index_middle_upper_right_collision_box];

        array_index_middle_lower_right_collision_box = x_tile_coordinate_right_collision_player + (y_tile_coordinate_middle_lower_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
        tile_collision_type_middle_lower_right = LEVEL_COLLISION[array_index_middle_lower_right_collision_box];

        array_index_middle_lower_right2_collision_box = x_tile_coordinate_right_collision_player + (y_tile_coordinate_middle_lower2_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
        tile_collision_type_middle_lower2_right = LEVEL_COLLISION[array_index_middle_lower_right2_collision_box];

        if (tile_collision_type_top_right == SOLID_TILE ||
            tile_collision_type_bottom_right == SOLID_TILE ||
            tile_collision_type_middle_upper_right == SOLID_TILE ||
            tile_collision_type_middle_lower_right == SOLID_TILE ||
            tile_collision_type_middle_lower2_right == SOLID_TILE)
        {
            blocked_coordinate = (x_tile_coordinate_right_collision_player << 4) - PLAYER_COLLISION_BOX_RIGHT;
            player_x = FIX32(blocked_coordinate);
            player_x -= FIX32(0.1); // to prevent getting stuck on corner
        }
    }

    // if (is_player_moving_up)
    // {
    //     player_y -= player_vel;
    //     player_top_collision_coordinate = F32_toInt(player_y) + PLAYER_COLLISION_BOX_TOP;
    //     y_tile_coordinate_top_collision_player = player_top_collision_coordinate >> 4;

    //     player_left_collision_coordinate = F32_toInt(player_x) + PLAYER_COLLISION_BOX_LEFT;
    //     x_tile_coordinate_left_collision_player = player_left_collision_coordinate >> 4;
    //     array_index_top_left_collision_box = x_tile_coordinate_left_collision_player + (y_tile_coordinate_top_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
    //     tile_collision_type_top_left = LEVEL_COLLISION[array_index_top_left_collision_box];

    //     player_right_collision_coordinate = F32_toInt(player_x) + PLAYER_COLLISION_BOX_RIGHT;
    //     x_tile_coordinate_right_collision_player = player_right_collision_coordinate >> 4;
    //     array_index_top_right_collision_box = x_tile_coordinate_right_collision_player + (y_tile_coordinate_top_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
    //     tile_collision_type_top_right = LEVEL_COLLISION[array_index_top_right_collision_box];

    //     if (tile_collision_type_top_left == SOLID_TILE || tile_collision_type_top_right == SOLID_TILE)
    //     {
    //         blocked_coordinate = (y_tile_coordinate_top_collision_player << 4) + 16 - PLAYER_COLLISION_BOX_TOP;
    //         player_y = FIX32(blocked_coordinate);
    //     }
    // }

    player_y_velocity += gravity;

    if (player_y_velocity > terminal_velocity)
    {
        player_y_velocity = terminal_velocity;
    }

    player_y += player_y_velocity;

    player_top_collision_coordinate = F32_toInt(player_y) + PLAYER_COLLISION_BOX_TOP;
    y_tile_coordinate_top_collision_player = player_top_collision_coordinate >> 4;

    player_bottom_collision_coordinate = F32_toInt(player_y) + PLAYER_COLLISION_BOX_BOTTOM;
    y_tile_coordinate_bottom_collision_player = player_bottom_collision_coordinate >> 4;

    player_left_collision_coordinate = F32_toInt(player_x) + PLAYER_COLLISION_BOX_LEFT;
    x_tile_coordinate_left_collision_player = player_left_collision_coordinate >> 4;

    player_right_collision_coordinate = F32_toInt(player_x) + PLAYER_COLLISION_BOX_RIGHT;
    x_tile_coordinate_right_collision_player = player_right_collision_coordinate >> 4;

    array_index_top_left_collision_box = x_tile_coordinate_left_collision_player + (y_tile_coordinate_top_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
    tile_collision_type_top_left = LEVEL_COLLISION[array_index_top_left_collision_box];

    array_index_top_right_collision_box = x_tile_coordinate_right_collision_player + (y_tile_coordinate_top_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
    tile_collision_type_top_right = LEVEL_COLLISION[array_index_top_right_collision_box];

    array_index_bottom_left_collision_box = x_tile_coordinate_left_collision_player + (y_tile_coordinate_bottom_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
    tile_collision_type_bottom_left = LEVEL_COLLISION[array_index_bottom_left_collision_box];

    array_index_bottom_right_collision_box = x_tile_coordinate_right_collision_player + (y_tile_coordinate_bottom_collision_player * LENGTH_OF_LEVEL_COLLISION_ARRAY);
    tile_collision_type_bottom_right = LEVEL_COLLISION[array_index_bottom_right_collision_box];

    if (tile_collision_type_bottom_left == SOLID_TILE || tile_collision_type_bottom_right == SOLID_TILE)
    {
        blocked_coordinate = (y_tile_coordinate_bottom_collision_player << 4) - PLAYER_COLLISION_BOX_BOTTOM;
        player_y = FIX32(blocked_coordinate);
        player_y -= FIX32(0.1); // to prevent getting stuck on corner
        player_y_velocity = FIX32(0);
        is_player_jumping = FALSE;
    }
    else if (tile_collision_type_top_left == SOLID_TILE || tile_collision_type_top_right == SOLID_TILE)
    {
        blocked_coordinate = (y_tile_coordinate_top_collision_player << 4) + 16 - PLAYER_COLLISION_BOX_TOP;
        player_y = FIX32(blocked_coordinate);
        player_y_velocity = FIX32(0);
    }
}

static void joyEventHandler(u16 joy, u16 changed, u16 state)
{
    if ((changed & state & BUTTON_C) && !is_player_jumping && player_y_velocity <= 0)
    {
        player_y_velocity -= jump_velocity;
        is_player_jumping = TRUE;
    }
}