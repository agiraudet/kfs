/* Multiboot header */
.set ALIGN,     1<<0              /* align loaded modules on page boundaries */
.set MEMINFO,   1<<1              /* provide memory map */
.set FLAGS,     ALIGN | MEMINFO   /* Multiboot 'flag' field */
.set MAGIC,     0x1BADB002        /* bootloader magic tag */
.set CHECKSUM,  -(MAGIC + FLAGS)  /* checksum to prove we are Multiboot */

/* 
Declare a multiboot header that marks the program as a kernel
*/
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/*
Multiboot standard does not define the value of esp, we have to make our own stack by:
- create a symbol at the bottom of it
- allocate 16384 bytes for it
- create a symbol at the top
On x86, stack grow downard and must be 16-byte aligned (System V ABI standard)
*/
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

/*
The linker script specifies _start as the entry point to the kernel
*/
.section .text
.global _start
.type _start, @function

_start:
	  mov $stack_top, %esp     /* setup stack by setting esp */
    call kernel_main 
    /* infinite loop */
    cli                      /* clear interrupt enable flag */
1:  hlt
    jmp 1b

.size _start, . - _start
