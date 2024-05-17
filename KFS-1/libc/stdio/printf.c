#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int printf(const char *restrict format, ...) {
  va_list parameters;
  va_start(parameters, format);

  int written = 0;
  while (*format) {
    size_t maxrem = INT_MAX - written; // TODO check overflow
    if (*format == '%') {
      format++;
      if (*format == '%') {
        putchar('%');
        written++;
      } else if (*format == 'd') {
        written += putnbr(va_arg(parameters, int));
      } else if (*format == 'c') {
        putchar(va_arg(parameters, int));
        written++;
      } else if (*format == 's') {
        written += putstr(va_arg(parameters, const char *));
      } else {
        return -1;
      }
      format++;
      continue;
    } else {
      putchar(*format++);
      written++;
    }
  }
  va_end(parameters);
  return written;
}
