#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

#define KEY_UP_ARROW 0xE048
#define KEY_DOWN_ARROW 0xE050
#define KEY_LEFT_ARROW 0xE04B
#define KEY_RIGHT_ARROW 0xE04D
#define KEY_LEFT_CTRL_PRESS 0x1D
#define KEY_LEFT_CTRL_RELEASE 0x9D

uint16_t keyboard_poll();
char handle_key(uint16_t keycode);
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char *data, size_t size);
void terminal_writestring(const char *data);
void terminal_linebreak(void);
void terminal_setcolor(uint8_t color);

struct term {
  size_t row;
  size_t col;
  char buffer[2000];
  uint8_t init;
};

#endif
