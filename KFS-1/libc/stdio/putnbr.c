#include <stdio.h>

int putnbr(int n) {
  int ret = 0;

  // TODO handle max_int
  if (n < 0) {
    putchar('-');
    n *= -1;
    ret++;
  }
  if (n > 9)
    ret += putnbr(n / 10);
  putchar(n % 10 + '0');
  ret++;
  return ret;
}
