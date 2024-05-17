#include <string.h>

void *memcpy(void *dest, const void *src, size_t n) {
  unsigned char *d;
  const unsigned char *s;
  size_t i;

  d = (unsigned char *)dest;
  s = (unsigned char *)src;
  if (!n || d == s)
    return (dest);
  i = 0;
  while (i < n) {
    d[i] = s[i];
    i++;
  }
  return (dest);
}
