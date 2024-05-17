#include <string.h>

char *strnstr(const char *big, const char *little, size_t len) {
  size_t i;

  if (!(*little))
    return ((char *)big);
  while (*big && len > 0) {
    if (*big == *little) {
      i = 0;
      while (little[i] && big[i] == little[i] && i < len)
        i++;
      if (little[i] == '\0')
        return ((char *)big);
    }
    big++;
    len--;
  }
  return (0);
}
