#include <string.h>

char *strchr(const char *s, int c) {
  while (*s && *s != c)
    s++;
  if (*s != c)
    s = 0;
  return ((char *)s);
}
