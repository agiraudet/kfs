#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

uint8_t keyboard_poll();
char keycode_to_char(uint8_t keycode);
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char *data, size_t size);
void terminal_writestring(const char *data);
void terminal_linebreak(void);
void terminal_setcolor(uint8_t color);

#endif
