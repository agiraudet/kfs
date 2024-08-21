.intel_syntax noprefix
.section .text
  .global gdt_set

gdt_set:
  mov eax, [esp + 4]
  lgdt [eax]
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  jmp 0x8:.flush
  ret

.flush:
  ret
