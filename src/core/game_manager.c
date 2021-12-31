#include "core/game_manager.h"

static inline uint16_t getIndexLeft(Grid * grid, uint8_t x, uint8_t y) {
  return x + y * grid->size;
}

static inline uint16_t getIndexRight(Grid * grid, uint8_t x, uint8_t y) {
  return grid->length - (x + y * grid->size);
}

static inline uint16_t getIndexUp(Grid * grid, uint8_t x, uint8_t y) {
  return y + x * grid->size;
}

static inline uint16_t getIndexDown(Grid * grid, uint8_t x, uint8_t y) {
  return grid->length - (y + x * grid->size);
}

typedef uint16_t (*IndexFN)(Grid *, uint8_t, uint8_t);

static const IndexFN indexfn[4] = {
  getIndexUp,
  getIndexRight,
  getIndexDown,
  getIndexLeft
};

bool gm_move(Grid * grid, Direction dir) {
  bool moved, merged;
  uint8_t x, y, i;
  uint16_t previous, index, next;
  IndexFN getIndex; 

  moved = merged = false;
  getIndex = indexfn[dir];
  for (y = 0; y < grid->size; ++y) {
    previous = getIndex(grid, 0, y);
    for (x = 1; x < grid->size; ++x) {
      index = getIndex(grid, x, y);
      if (grid->cells[index]) {
        if (grid->cells[index] == grid->cells[previous]) {
          merged = true;
          grid->cells[previous] <<= 1;
          grid->cells[index] = 0;
        }
        previous = index;
      }
    }

    for (x = 0; x < grid->size; ++x) {
      index = getIndex(grid, x, y);
      if (grid->cells[index] == 0) {
        for (i = x + 1; i < grid->size; ++i) {
          next = getIndex(grid, i, y);
          if (grid->cells[next]) {
            moved = true;
            grid->cells[index] = grid->cells[next];
            grid->cells[next] = 0;
            break;
          }
        }
      }
    }
  }

  return merged || moved;
}

bool gm_add_random_tile(Grid * grid) {
  bool added = false;
  cvector_vector_type(uint16_t) available = grid_get_available_cells(grid);
  if (cvector_size(available) == 0) {
    goto end;
  }

  uint16_t choose = available[rand() % cvector_size(available)];
  uint32_t value = (rand() / (float) RAND_MAX) >= 0.9 ? 4 : 2;
  grid->cells[choose] = value;
  added = true;

  end:;
  cvector_free(available);
  return added;
}

bool gm_add_random_tiles(Grid * grid, uint16_t n_tiles) {
  bool added = true;
  cvector_vector_type(uint16_t) available = grid_get_available_cells(grid);
  while (n_tiles--) {
    if (cvector_size(available) == 0) {
      added = false;
      goto end;
    }
    size_t index = rand() % cvector_size(available);
    uint16_t choose = available[index];
    cvector_erase(available, index);
    uint32_t value = (rand() / (float) RAND_MAX) >= 0.9 ? 4 : 2;
    grid->cells[choose] = value;
  }
  end:;
  cvector_free(available);
  return added;
}

bool gm_tile_matches_available(Grid * grid) {
  IndexFN getIndex;
  for (Direction dir = 0; dir < 2; ++dir) {
    getIndex = indexfn[dir];
    for (uint16_t y = 0; y < grid->size; ++y) {
      for (uint16_t x = 1; x < grid->size; ++x) {
        uint16_t index = getIndex(grid, x, y);
        if (grid->cells[index]) {
          uint16_t neighbor = getIndex(grid, x - 1, y);
          if (grid->cells[index] == grid->cells[neighbor]) {
            return true;
          }
        }
      }
    }
  }
  return false;
}
