#include <stdlib.h>

int atoi(const char *nptr) {
  int result;
  int sign;

  if (!nptr)
    return (0);
  result = 0;
  sign = 1;
  while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
    nptr++;
  if (*nptr == '+' || *nptr == '-')
    if (*nptr++ == '-')
      sign = -1;
  while (*nptr >= '0' && *nptr <= '9')
    result = (*nptr++ - '0') + result * 10;
  return (result * sign);
}
