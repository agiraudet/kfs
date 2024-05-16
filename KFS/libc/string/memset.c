#include <string.h>

void *memset(void *s, int c, size_t n) {
  unsigned char *cursor;

  cursor = s;
  while (n-- > 0)
    *cursor++ = c;
  return (s);
}
