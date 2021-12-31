
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "lib/fast_term.h"
#include "lib/geometry.h"
#include "lib/string_ext.h"

void box(const Rect rect) {
  char * line = strrep("─", rect.w - 2);
  move(rect.x, rect.y);
  print("┌");
  print(line);
  print("┐");
  uint16_t i;
  for (i = 1; i < rect.h - 1; ++i) {
    uint16_t y = rect.y + i;
    mvprint(rect.x, y, "│");
    mvprint(rect.x + rect.w - 1, y, "│");
  }
  move(rect.x, rect.y + i);
  print("└");
  print(line);
  print("┘");
  free(line);
}


void fill(const Rect rect) {
  char * space = chrrep(' ', rect.w);
  for (uint16_t i = 0; i < rect.h; ++i) {
    mvprint(rect.x, rect.y + i, space);
  }
  free(space);
}

Rect relative(const Rect parent, const Rect rect) {
  return (Rect) { 
    .x = parent.x + rect.x, 
    .y = parent.y + rect.y, 
    .w = rect.w, 
    .h = rect.h 
  };
}

void rmove(const Rect parent, uint16_t x, uint16_t y) {
  move(parent.x + x, parent.y + y);
}

void rmvprint(const Rect parent, uint16_t x, uint16_t y, const char * format, ...) {
  va_list list;
  va_start(list, format);
  rmove(parent, x, y);
  vprintf(format, list);
  va_end(list);
}

void hline(uint16_t x, uint16_t y, uint16_t len) {
  move(x, y);
  for (uint16_t i = 0; i < len; ++i) print("─");
}

void vline(uint16_t x, uint16_t y, uint16_t len) {
  for (uint16_t i = 0; i < len; ++i) mvprint(x, y + i, "│");
}
