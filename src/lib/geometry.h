#pragma once
#ifndef H_GEOMETRY_INCLUDED
#define H_GEOMETRY_INCLUDED 

#include <stdint.h>

typedef struct {
  uint16_t x, y, w, h;
} Rect;

// draw a box around the retangle
void box(const Rect rect);

// fill rectangle with space
void fill(const Rect rect);

// returns rectangle which has position relative with parent
Rect relative(const Rect parent, const Rect rect);

// relative move
void rmove(const Rect parent, uint16_t x, uint16_t y);

// relative move and print
void rmvprint(const Rect parent, uint16_t x, uint16_t y, const char * format, ...);

void hline(uint16_t x, uint16_t y, uint16_t len);

void vline(uint16_t x, uint16_t y, uint16_t len);

#endif
