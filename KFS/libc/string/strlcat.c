#include <string.h>

size_t strlcat(char *dst, const char *src, size_t size) {
  size_t i;
  size_t dstlen;

  dstlen = strlen(dst);
  i = 0;
  if (dstlen < size) {
    while (src[i] && (i + dstlen + 1) < size) {
      dst[dstlen + i] = src[i];
      i++;
    }
  }
  if (size > 0 && dstlen <= size)
    dst[i + dstlen] = '\0';
  if (dstlen < size)
    return (dstlen + strlen(src));
  else
    return (size + strlen(src));
}
