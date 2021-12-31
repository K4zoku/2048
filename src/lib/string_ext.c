#include "lib/string_ext.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char * strrep(const char * str, size_t n) {
  size_t str_len = strlen(str);
  size_t len = 1 + n * str_len;
  char * rep = (char *) malloc(len * sizeof(char));
  assert(rep);
  for (size_t i = 0; i < n; ++i) memcpy(rep + i * str_len, str, str_len * sizeof(char));
  rep[len] = '\0';
  return rep;
}

char * chrrep(const char c, size_t n) {
  char * rep = (char *) malloc((1 + n) * sizeof(char));
  assert(rep);
  memset(rep, c, n * sizeof(char));
  rep[n] = '\0';
  return rep;
}

char * strdup(const char * str) {
  size_t len = strlen(str);
  char * dup = (char *) malloc((1 + len) * sizeof(char));
  assert(dup);
  memcpy(dup, str, len * sizeof(char));
  dup[len] = '\0';
  return dup;
}

char * trim(char * str) {
  size_t len = strlen(str);
  size_t st = 0;
  while ((st < len) && isspace(str[st])) ++st;
  while ((st < len) && isspace(str[len - 1])) --len;
  str += st;
  len -= st;
  str[len] = '\0';
  return str;
}
