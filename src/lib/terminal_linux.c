#ifdef __unix__
#define _BSD_SOURCE
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <inttypes.h>
#include <unistd.h>
#include <termios.h>

#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/select.h>

#include "lib/terminal.h"

#define CSI "\x1b["

#define SAVE_CURSOR_POSITION CSI "s"
#define RESTORE_CURSOR_POSITION CSI "u"

void term_clrscr() {
  puts(CSI "2J");
}

static struct termios orig_termios;

void term_init() {
  struct termios new_termios;
  tcgetattr(0, &orig_termios);
  tcgetattr(0, &new_termios);
  cfmakeraw(&new_termios);
  new_termios.c_lflag &= (~(ICANON | ECHO));
  new_termios.c_cc[VTIME] = 0;
  new_termios.c_cc[VMIN] = 1;
  tcsetattr(0, TCSANOW, &new_termios);
  atexit(term_quit);
}

void term_quit() {
  tcsetattr(0, TCSANOW, &orig_termios);
}

void term_alt(bool enable) {
  if (enable) {
    printf(CSI "?1049h");
  } else {
    printf(CSI "?1049l");
  }
}

void term_cursor(bool enable) {
  if (enable) {
    printf(CSI "?25h");
  } else {
    printf(CSI "?25l");
  }
}

bool term_kbhit() {
  struct timeval tv = {0, 0};
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(0, &fds);
  return select(1, &fds, NULL, NULL, &tv) > 0;
}

int term_getch() {
  char c;
  int r;
  r = read(0, &c, sizeof(char));
  return r < 0 ? r : c;
}

void term_move(uint16_t x, uint16_t y) {
  printf(CSI "%" PRIu16 ";%" PRIu16 "H", y, x);
}

void term_refresh() {
  putchar('\n');
}

static uint16_t c, r;

bool term_size(uint16_t * cols, uint16_t * rows) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  *cols = w.ws_col;
  *rows = w.ws_row;
  if (c == *cols && r == *rows) {
    return false;
  }
  c = *cols; 
  r = *rows;
  return true;
}

#endif
