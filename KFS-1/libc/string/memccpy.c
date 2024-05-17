#include <string.h>

void *memccpy(void *dest, const void *src, int c, size_t n) {
  unsigned char *d;
  const unsigned char *s;
  size_t i;

  d = (unsigned char *)dest;
  s = (const unsigned char *)src;
  i = 0;
  while (i < n) {
    d[i] = s[i];
    if (s[i] == (unsigned char)c)
      return ((void *)(d + i + 1));
    i++;
  }
  return (0);
}
