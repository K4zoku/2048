#include "lib/ticks.h"

#include <stddef.h>

#ifdef __unix__
#include <sys/time.h>
#else

typedef struct timeval {
    long tv_sec;
    long tv_usec;
} timeval;

int gettimeofday(struct timeval * tp, struct timezone * tzp) {
  // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
  // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
  // until 00:00:00 January 1, 1970 
  static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

  SYSTEMTIME system_time;
  FILETIME file_time;
  uint64_t time;
  GetSystemTime(&system_time);
  SystemTimeToFileTime(&system_time, &file_time);
  time = ((uint64_t) file_time.dwLowDateTime);
  time += ((uint64_t) file_time.dwHighDateTime) << 32;
  tp->tv_sec = (long) ((time - EPOCH) / 10000000L);
  tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
  return 0;
}

#endif

static struct timeval starttime;

void ticks_init() {
  gettimeofday(&starttime, NULL);
}

uint32_t ticks() {
  struct timeval now;
  gettimeofday(&now, NULL);
  return ((now.tv_sec - starttime.tv_sec) * 1000000 + (now.tv_usec - starttime.tv_usec) / 1000);
}
