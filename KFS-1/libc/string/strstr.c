#include <string.h>

char *strstr(const char *haystack, const char *needle) {
  size_t i;

  if (!(*needle))
    return ((char *)haystack);
  while (*haystack) {
    if (*haystack == *needle) {
      i = 0;
      while (needle[i] && haystack[i] == needle[i])
        i++;
      if (needle[i] == 0)
        return ((char *)haystack);
    }
    haystack++;
  }
  return (0);
}
