#include <kernel/tty.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "com.h"
#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static const uint8_t VGA_COMMAND_HIGH_BYTE = 14;
static const uint8_t VGA_COMMAND_LOW_BYTE = 15;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;
static uint16_t const VGA_PORT_COMMAND = (uint16_t)0x3D4;
static uint16_t const VGA_PORT_DATA = (uint16_t)0x3D5;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;
char keycode_to_ascii[] = {
    0,   0,   '1',  '2', '3', '4',  '5',  '6',
    '7', '8', '9',  '0', '-', '=',  '\b', // 0x00 - 0x0F
    0,   'q', 'w',  'e', 'r', 't',  'y',  'u',
    'i', 'o', 'p',  '[', ']', '\n', 0, // 0x10 - 0x1F
    'a', 's', 'd',  'f', 'g', 'h',  'j',  'k',
    'l', ';', '\'', '`', 0,   '\\', // 0x20 - 0x2F
    'z', 'x', 'c',  'v', 'b', 'n',  'm',  ',',
    '.', '/', 0,    0,   0,   ' ' // 0x30 - 0x3F
};

void terminal_setcolor(uint8_t color) { terminal_color = color; }

void terminal_setcursor(void) {
  uint16_t position = (terminal_row * VGA_WIDTH) + terminal_column;
  outb(VGA_PORT_COMMAND, VGA_COMMAND_HIGH_BYTE);
  outb(VGA_PORT_DATA, (uint8_t)(position >> 8));
  outb(VGA_PORT_COMMAND, VGA_COMMAND_LOW_BYTE);
  outb(VGA_PORT_DATA, (uint8_t)(position & 0xFF));
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void terminal_linebreak(void) {
  if (++terminal_row == VGA_HEIGHT)
    terminal_row = 0;
  terminal_column = 0;
}

void terminal_putchar(char c) {
  if (c == '\n') {
    terminal_linebreak();
  } else if (c == '\b') {
    if (terminal_column > 0)
      terminal_column--;
    terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
  } else {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
      terminal_column = 0;
      if (++terminal_row == VGA_HEIGHT)
        terminal_row = 0;
    }
  }
  terminal_setcursor();
}

void terminal_write(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++)
    terminal_putchar(data[i]);
}

void terminal_writestring(const char *str) { terminal_write(str, strlen(str)); }

void terminal_initialize(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
  terminal_buffer = VGA_MEMORY;
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      terminal_putentryat(' ', terminal_color, x, y);
    }
  }
}

uint16_t keyboard_poll() {
  uint8_t byte1 = 0, byte2 = 0;
  while (!(inb(KBD_STATUS_PORT) & KBD_STATUS_OBF))
    ;
  byte1 = inb(KBD_DATA_PORT);
  if (byte1 == 0xE0) {
    while (!(inb(KBD_STATUS_PORT) & KBD_STATUS_OBF))
      ;
    byte2 = inb(KBD_DATA_PORT);
    return (byte1 << 8) | byte2;
  } else {
    return byte1;
  }
}

char handle_key(uint16_t keycode) {
  switch (keycode) {
  case KEY_UP_ARROW:
    break;
  case KEY_DOWN_ARROW:
    break;
  case KEY_LEFT_ARROW:
    if (terminal_column > 0) {
      terminal_column--;
      terminal_setcursor();
    }
    break;
  case KEY_RIGHT_ARROW:
    break;
  default:
    if (keycode < 0x100 && keycode < sizeof(keycode_to_ascii))
      return keycode_to_ascii[keycode];
    break;
  }
  return 0;
}
