# RetOS

# IMP NOTICE: THE MAKEFILE IS NOT FUNCTIONAL AND IS STILL IN DEVLOPEMENT!

RetOS is a hobby x86 operating system built **from scratch** using C and x86 Assembly.
No libc. No hand-holding. GRUB, and raw VGA memory.

> Built for learning OS development the hard (and fun) way.

---

## Features
- Boots using **GRUB (BIOS)**
- Custom **32-bit kernel**
- VGA text mode driver
- Minimal `printf` implementation
- Clean project structure
- Runs on QEMU

---

## 📁 Project Structure
RetOS/
├── boot/
│ └── grub/
│ └── grub.cfg
├── kernel/
│ ├── boot.asm
│ ├── kernel.c
│ ├── printf.c
│ └── printf.h
├── build/ # generated (ignored)
├── iso/ # generated (ignored)
└── README.md


---

## Building RetOS

### Requirements
- `nasm`
- `gcc` (with multilib support)
- `grub-pc-bin`
- `xorriso`
- `qemu-system-x86`

### Build kernel
```bash
nasm -f elf32 kernel/boot.asm -o build/boot.o
gcc -m32 -ffreestanding -c kernel/kernel.c -o build/kernel.o
gcc -m32 -ffreestanding -c kernel/printf.c -o build/printf.o
ld -m elf_i386 -T kernel/linker.ld -o build/kernel.bin \
   build/boot.o build/kernel.o build/printf.o
