#include <string.h>

void *memchr(const void *s, int c, size_t n) {
  unsigned char *cursor;

  cursor = (unsigned char *)s;
  while (n--) {
    if (*cursor == (unsigned char)c)
      return (cursor);
    cursor++;
  }
  return (0);
}
