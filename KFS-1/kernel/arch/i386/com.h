#ifndef ARCH_I386_COM_H
#define ARCH_I386_COM_H

#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
  uint8_t result;
  __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
  return result;
}

static inline void outb(uint16_t port, uint8_t data) {
  __asm__ volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

#endif
