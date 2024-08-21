#include <stdio.h>

#include "../arch/i386/vga.h"
#include <kernel/gdt.h>
#include <kernel/tty.h>

void kernel_main(void) {
  terminal_initialize();
  terminal_setcolor(vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK));
  init_gdt();
  printf("%d\n%s\n", 42, "Hello kernel world!");
  terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
  while (1) {
    uint16_t keycode = keyboard_poll();
    char ch = handle_key(keycode);
    if (ch != 0) {
      putchar(ch);
    }
  }
}
