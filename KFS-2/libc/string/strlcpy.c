#include <string.h>

size_t strlcpy(char *dst, const char *src, size_t size) {
  size_t srclen;

  if (!src)
    return (0);
  srclen = strlen(src);
  if (!size)
    return (srclen);
  while (--size && *src)
    *dst++ = *src++;
  *dst = '\0';
  return (srclen);
}
