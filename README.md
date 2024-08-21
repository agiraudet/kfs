# Kernel From Scratch (KFS)

KFS (Kernel From Scratch) is a personal project aimed at building a simple x86 kernel from scratch using assembly and C. This repository contains various directories corresponding to different milestones of the project.

## Milestones

| Directory | Description |
|-----------|-------------|
| kfs-1     | Hello World kernel booting with Grub. |
| kfs-2     | Adding GDT/IDT to the kernel |

## Details

### KFS-1

A "Hello world" kernel, bootable with grub.
I added basic keyboard handling by reading port 0x60. Later, I'll do that properly by handling interrupts, but I want to set up the GDT before implementing the IDT.
This basic keyboard management allows me to type, scroll, switch between different terminal with CTRL+1-9.
I also added some basic libc function implemented myself, and a bery simple printf() to simplify debug.

### KFS-2

Now working on adding the GDT.

## References

- [OSDev Wiki](https://wiki.osdev.org/Main_Page): A valuable resource for learning about operating system development.
- [*Operating Systems: Three Easy Pieces*](https://pages.cs.wisc.edu/~remzi/OSTEP/) by Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau (University of Wisconsin-Madison).
