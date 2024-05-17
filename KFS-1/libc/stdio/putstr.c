#include <stdio.h>

int putstr(const char *str) {
  int ret = 0;

  while (str && *str) {
    putchar(*str++);
    ret++;
  }
  return ret;
}
