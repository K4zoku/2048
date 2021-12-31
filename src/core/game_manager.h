#pragma once
#ifndef H_GAME_MANAGER_INCLUDED
#define H_GAME_MANAGER_INCLUDED

#include <stdint.h>
#include <stdbool.h>

#include "core/grid.h"

typedef enum {
    DIR_UP, 
    DIR_RIGHT, 
    DIR_DOWN, 
    DIR_LEFT
} Direction;

bool gm_move(Grid * grid, Direction dir);

bool gm_add_random_tile(Grid * grid);

bool gm_add_random_tiles(Grid * grid, uint16_t n_tiles);

bool gm_tile_matches_available(Grid * grid);

#endif

