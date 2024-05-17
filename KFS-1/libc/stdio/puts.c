#include <stdio.h>

int puts(const char *str) {
  int len = putstr(str);
  putchar('\n');
  return len + 1;
}
