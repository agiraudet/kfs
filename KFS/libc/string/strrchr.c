#include <string.h>

char *strrchr(const char *s, int c) {
  char *occurence;

  occurence = 0;
  while (*s) {
    if (*s == c)
      occurence = (char *)s;
    s++;
  }
  if (c == '\0')
    return ((char *)s);
  return (occurence);
}
