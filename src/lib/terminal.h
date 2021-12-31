#pragma once
#ifndef H_TERMINAL_INCLUDED
#define H_TERMINAL_INCLUDED 

#include <stdint.h>
#include <stdbool.h>

void term_init();

void term_quit();

void term_clrscr();

void term_alt(bool enable);

void term_cursor(bool enable);

void term_refresh();

bool term_kbhit();

int term_getch();

void term_move(uint16_t x, uint16_t y);

bool term_size(uint16_t * cols, uint16_t * rows);

#endif
