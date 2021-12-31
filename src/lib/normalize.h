#pragma once
#ifndef H_NORMALIZE_INCLUDED
#define H_NORMALIZE_INCLUDED 

#include <stdint.h>

#include "lib/terminal.h"

#define ARROW_UP    0x1b5b41
#define ARROW_DOWN  0x1b5b42
#define ARROW_RIGHT 0x1b5b43
#define ARROW_LEFT  0x1b5b44
#define ESC         0x1b

#define move(x, y) term_move(x, y)

#define refresh() term_refresh()

#define clear() term_clrscr()

#define keypressed() term_kbhit()

#define altscron() term_alt(true)

#define altscroff() term_alt(false)

#define cursoron() term_cursor(true)

#define cursoroff() term_cursor(false)

#define getsize(cols, rows) term_size(&cols, &rows)

void print(const char * format, ...);

void mvprint(uint16_t x, uint16_t y, const char * format, ...);

int64_t getkey();

#endif
