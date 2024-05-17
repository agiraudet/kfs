#include <string.h>

void bzero(void *s, size_t n) {
  unsigned char *cursor;

  cursor = s;
  while (n-- > 0)
    *cursor++ = '\0';
}
