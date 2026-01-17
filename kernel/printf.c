
#include "printf.h"
#include <stdarg.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile unsigned char* const VGA_MEMORY =
    (volatile unsigned char*)0xB8000;


static int cursor_x = 0;
static int cursor_y = 0;
static char color = 0x0F; // white on black

static void vga_putc(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }

    int index = (cursor_y * VGA_WIDTH + cursor_x) * 2;
    VGA_MEMORY[index] = c;
    VGA_MEMORY[index + 1] = color;

    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
}

void clear_screen(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            int i = (y * VGA_WIDTH + x) * 2;
            VGA_MEMORY[i] = ' ';
            VGA_MEMORY[i + 1] = color;
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

static void print_dec(int num) {
    if (num == 0) {
        vga_putc('0');
        return;
    }

    char buf[16];
    int i = 0;

    while (num > 0) {
        buf[i++] = '0' + (num % 10);
        num /= 10;
    }

    for (int j = i - 1; j >= 0; j--) {
        vga_putc(buf[j]);
    }
}

void printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    for (int i = 0; fmt[i]; i++) {
        if (fmt[i] == '%' && fmt[i + 1]) {
            i++;
            if (fmt[i] == 'd') {
                int val = va_arg(args, int);
                print_dec(val);
            } else if (fmt[i] == 's') {
                char* str = va_arg(args, char*);
                while (*str) vga_putc(*str++);
            }
        } else {
            vga_putc(fmt[i]);
        }
    }

    va_end(args);
}
