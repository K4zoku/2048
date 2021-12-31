#include <stdio.h>
#include <stdarg.h>

#include "lib/normalize.h"

void print(const char * format, ...) {
  va_list list;
  va_start(list, format);
  vprintf(format, list);
  va_end(list);
}

void mvprint(uint16_t x, uint16_t y, const char * format, ...) {
  va_list list;
  va_start(list, format);
  move(x, y);
  vprintf(format, list);
  va_end(list);
}

int64_t getkey() {
  int64_t key = term_getch();
  while (term_kbhit()) {
    key <<= 8;
    key |= term_getch();
  }
  return key;
}
