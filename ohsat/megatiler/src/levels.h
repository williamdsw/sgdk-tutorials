#include <genesis.h>

#ifndef _LEVELS_H_
#define _LEVELS_H_

/*
 * 0: grass
 * 1: walls
 * 2: doors
 * 4: player spawn position
 * 5: exit tile
 * 6: coin tile
*/
u8 level1TilesIndexes[8][8] = 
{
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 4, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 6, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 6, 0, 0, 1, 6, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 5 },
};

/*
 * 0: grass
 * 1: walls
 * 2: doors
 * 4: player spawn position
 * 5: exit tile
 * 6: coin tile
*/
u8 level2TilesIndexes[8][8] = 
{
    { 0, 0, 0, 6, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 4, 0, 1, 1, 1, 0, 0 },
    { 0, 0, 0, 6, 0, 1, 0, 0 },
    { 0, 0, 0, 1, 1, 1, 6, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 6, 0, 1, 1, 1, 5, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
};

/*
 * 0: grass
 * 1: walls
 * 2: doors
 * 4: player spawn position
 * 5: exit tile
 * 6: coin tile
*/
u8 level3TilesIndexes[8][8] = 
{
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 0, 0, 0, 6, 1, 0, 0 },
    { 0, 0, 0, 1, 1, 1, 6, 0 },
    { 0, 0, 0, 0, 0, 1, 0, 0 },
    { 0, 6, 1, 1, 1, 1, 0, 0 },
    { 0, 4, 0, 0, 0, 0, 5, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
};

#endif // _LEVELS_H_