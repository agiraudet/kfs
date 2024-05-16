#include <string.h>

size_t strlen(const char *s) {
  size_t i;

  if (!s)
    return (0);
  i = 0;
  while (s[i])
    i++;
  return (i);
}
