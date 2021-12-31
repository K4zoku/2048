#pragma once
#ifndef H_GRID_INCLUDED
#define H_GRID_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "lib/cvector.h"

typedef struct {
    uint8_t size;
    uint16_t length;
    uint32_t * cells;
} Grid;

void grid_init(Grid ** gridptr, uint8_t size);

bool grid_is_cell_available(Grid * grid, uint16_t index);

bool grid_any_cell_available(Grid * grid);

/**
 * @return vector that contains index of all available cells 
 **/
cvector_vector_type(uint16_t) grid_get_available_cells(Grid * grid);

void grid_serialize(Grid * grid, FILE * out);

Grid * grid_deserialize(FILE * in);

void grid_free(Grid * grid);

#endif
