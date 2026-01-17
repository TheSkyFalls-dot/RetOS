BITS 32

section .multiboot
align 8
mb2_start:
    dd 0xe85250d6          ; multiboot2 magic
    dd 0                  ; architecture (i386)
    dd mb2_end - mb2_start
    dd -(0xe85250d6 + 0 + (mb2_end - mb2_start))

    dw 0
    dw 0
    dd 8
mb2_end:

section .text
global _start
extern kernel_main

_start:
    call kernel_main
.hang:
    cli
    hlt
    jmp .hang
