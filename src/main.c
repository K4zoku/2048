#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "lib/ticks.h"
#include "lib/geometry.h"
#include "lib/normalize.h"

// 33 x 6
const char * banner[2][6] = {
  {
    "██████╗  ██████╗ ██╗  ██╗ █████╗ ",
    "╚════██╗██╔═████╗██║  ██║██╔══██╗",
    " █████╔╝██║██╔██║███████║╚█████╔╝",
    "██╔═══╝ ████╔╝██║╚════██║██╔══██╗",
    "███████╗╚██████╔╝     ██║╚█████╔╝",
    "╚══════╝ ╚═════╝      ╚═╝ ╚════╝ "
  },
  {
    "\x1b[91m██████\x1b[0m╗  \x1b[32m██████\x1b[0m╗ \x1b[93m██\x1b[0m╗  \x1b[93m██\x1b[0m╗ \x1b[94m█████\x1b[0m╗ ",
    "╚════\x1b[91m██\x1b[0m╗\x1b[32m██\x1b[0m╔═\x1b[32m████\x1b[0m╗\x1b[93m██\x1b[0m║  \x1b[93m██\x1b[0m║\x1b[94m██\x1b[0m╔══\x1b[94m██\x1b[0m╗",
    "\x1b[91m █████\x1b[0m╔╝\x1b[32m██\x1b[0m║\x1b[32m██\x1b[0m╔\x1b[32m██\x1b[0m║\x1b[93m███████\x1b[0m║╚\x1b[94m█████\x1b[0m╔╝",
    "\x1b[91m██\x1b[0m╔═══╝ \x1b[32m████\x1b[0m╔╝\x1b[32m██\x1b[0m║╚════\x1b[93m██\x1b[0m║\x1b[94m██\x1b[0m╔══\x1b[94m██\x1b[0m╗",
    "\x1b[91m███████\x1b[0m╗╚\x1b[32m██████\x1b[0m╔╝     \x1b[93m██\x1b[0m║╚\x1b[94m█████\x1b[0m╔╝",
    "╚══════╝ ╚═════╝      ╚═╝ ╚════╝ "
  }
};

uint16_t cols;
uint16_t rows;

int main(int argc, const char ** argv) {
  (void) argc;
  (void) argv;

  term_init();
  ticks_init();

  altscron();
  cursoroff();
  refresh();

  double fps_cap = 60.0F; // FPS 
  uint32_t interval = floor(1000.0F / fps_cap); // ms

  int64_t key = 0;
  uint32_t last_updated, now;
  bool update = false;

  last_updated = now = ticks();
  srand(now);
  while (true) {
    now = ticks();
    update |= getsize(cols, rows); // update when size changed
    update |= now - last_updated >= interval; // update by render tick
    if (update) {
      last_updated = now;
      update = false;
      clear();
      // TODO: render here
      refresh();
    }
    if (keypressed()) {
      key = getkey();
      // TODO: key handler here
      if (key == ESC) break;
    }
  }

  altscroff();
  cursoron();
  refresh();

  return 0;
}
