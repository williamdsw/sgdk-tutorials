
#include <genesis.h>
#include <resources.h>

u16 ind = TILE_USER_INDEX;
Map *level_map;

Sprite *spr_dog;
fix32 dog_x = FIX32(0);
fix32 dog_y = FIX32(0);
fix32 dog_vel = FIX32(3.5);

s16 current_camera_x = 0;
s16 current_camera_y = 0;

// buggy
#define HOW_FAR_TO_LEFT_BEFORE_CAMERA_MOVES 150
#define HOW_FAR_TO_RIGHT_BEFORE_CAMERA_MOVES 151
#define HOW_FAR_TO_TOP_BEFORE_CAMERA_MOVES 115
#define HOW_FAR_TO_BOTTOM_BEFORE_CAMERA_MOVES 116

#define HORIZONTAL_RESOLUTION 320
#define VERTICAL_RESOLUTION 224

#define MAP_WIDTH 896
#define MAP_HEIGHT 512

#define PLAYER_WIDTH 48
#define PLAYER_HEIGHT 40

// functions prototypes
static void handleInput();
static void handleCamera();

int main()
{
    SPR_init();

    PAL_setPalette(PAL0, village_pal0.data, DMA);
    PAL_setPalette(PAL1, village_pal1.data, DMA);
    PAL_setPalette(PAL2, dog_img.palette->data, DMA);

    VDP_loadTileSet(&village_tileset, ind, DMA);
    level_map = MAP_create(&village_map, BG_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind));
    ind += village_tileset.numTile;

    MAP_scrollTo(level_map, 0, 0);

    spr_dog = SPR_addSprite(&dog_img, F32_toInt(dog_x), F32_toInt(dog_y), TILE_ATTR(PAL2, FALSE, FALSE, FALSE));

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
        dog_x -= dog_vel;
        SPR_setHFlip(spr_dog, TRUE);
    }
    else if (value & BUTTON_RIGHT)
    {
        dog_x += dog_vel;
        SPR_setHFlip(spr_dog, FALSE);
    }

    if (value & BUTTON_UP)
    {
        dog_y -= dog_vel;
    }
    else if (value & BUTTON_DOWN)
    {
        dog_y += dog_vel;
    }
}

static void handleCamera()
{
    // stop player from leaving map
    if (dog_x < FIX32(0))
    {
        dog_x = FIX32(0);
    }
    else if (dog_x > FIX32(MAP_WIDTH - PLAYER_WIDTH))
    {
        dog_x = FIX32(MAP_WIDTH - PLAYER_WIDTH);
    }

    if (dog_y < FIX32(0))
    {
        dog_y = FIX32(0);
    }
    else if (dog_y > FIX32(MAP_HEIGHT - PLAYER_HEIGHT))
    {
        dog_y = FIX32(MAP_HEIGHT - PLAYER_HEIGHT);
    }

    // position of player on map as a whole number
    s16 player_x_map = F32_toInt(dog_x);
    s16 player_y_map = F32_toInt(dog_y);

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

    SPR_setPosition(spr_dog, F32_toInt(dog_x) - new_camera_x, F32_toInt(dog_y) - new_camera_y);
}