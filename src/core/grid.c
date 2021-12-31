#include "core/grid.h"

#include <stdlib.h>
#include <inttypes.h>

void grid_init(Grid ** gridptr, uint8_t size) {
  if (gridptr == NULL) {
    return;
  }
  Grid * grid = *gridptr;
  if (grid == NULL) {
    grid = (Grid *) malloc(sizeof(Grid));
  }
  grid->size = size;
  grid->length = size * size;
  grid->cells = (uint32_t *) calloc(grid->length, sizeof(uint32_t));
  *gridptr = grid;
}

bool grid_is_cell_available(Grid * grid, uint16_t index) {
  return grid->cells[index] == 0;
}

bool grid_any_cell_available(Grid * grid) {
  for (uint16_t i = 0; i < grid->length; ++i) {
    if (grid_is_cell_available(grid, i)) {
      return true;
    }
  }
  return false;
}

cvector_vector_type(uint16_t) grid_get_available_cells(Grid * grid) {
  cvector_vector_type(uint16_t) result = NULL;
  for (uint16_t i = 0; i < grid->length; ++i) {
    if (grid_is_cell_available(grid, i)) {
      cvector_push_back(result, i);
    }
  }
  return result;
}

void grid_serialize(Grid * grid, FILE * out) {
  fprintf(out, "%" PRIu8, grid->size);
  for (uint16_t i = 0; i < grid->length; ++i) {
    fprintf(out, " %" PRIu32, grid->cells[i]);
  }
  fputc('\n', out);
}

Grid * grid_deserialize(FILE * in) {
  Grid * grid = (Grid *) malloc(sizeof(Grid));
  fscanf(in, "%" SCNu8, &grid->size);
  grid->length = grid->size * grid->size;
  grid->cells = (uint32_t *) calloc(grid->length, sizeof(uint32_t));
  for (uint16_t i = 0; i < grid->length; ++i) {
    if (fscanf(in, "%" SCNu32, grid->cells + i) == EOF) {
      break;
    }
  }
  return grid;
}

void grid_free(Grid * grid) {
  free(grid->cells);
  free(grid);
}
