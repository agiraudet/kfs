#include <string.h>

void *memmove(void *dest, const void *src, size_t n) {
  unsigned char *d;
  const unsigned char *s;

  d = (unsigned char *)dest;
  s = (const unsigned char *)src;
  if (!d && !s)
    return (0);
  if (d >= s)
    while (n--)
      d[n] = s[n];
  else
    memcpy(d, s, n);
  return (dest);
}
