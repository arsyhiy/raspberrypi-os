#include "fb.h"
#include "font8x8.h"
#include "mbox.h"
#include "pi_config.h"

volatile unsigned int __attribute__((aligned(16))) mbox[36];

unsigned int width, height, pitch, depth;
unsigned char *fb;

int fb_init() {
    mbox[0] = 35 * 4;
    mbox[1] = 0;
    mbox[2] = 0x00048003; mbox[3] = 8; mbox[4] = 8; mbox[5] = 320; mbox[6] = 240;
    mbox[7] = 0x00048004; mbox[8] = 8; mbox[9] = 8; mbox[10] = 320; mbox[11] = 240;
    mbox[12] = 0x00048005; mbox[13] = 4; mbox[14] = 4; mbox[15] = 32;
    mbox[16] = 0x00040001; mbox[17] = 8; mbox[18] = 8; mbox[19] = 16; mbox[20] = 0;
    mbox[21] = 0x00040008; mbox[22] = 8; mbox[23] = 8; mbox[24] = 0; mbox[25] = 0;
    mbox[26] = 0;
    if (mbox_call(8)) {
        width = mbox[5];
        height = mbox[6];
        pitch = mbox[10];
        depth = mbox[15];
        fb = (unsigned char*)(mbox[19] & 0x3FFFFFFF); // ВАЖНО для реального железа
        return 0;
    } else {
        return -1;
    }
}

void fb_clear() {
    if (!fb) return;
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            int offs = y * pitch + x * 4;
            fb[offs] = 0;
            fb[offs + 1] = 0;
            fb[offs + 2] = 0;
            fb[offs + 3] = 0;
        }
    }
}

void fb_draw_pixel(int x, int y, unsigned int color) {
    if (!fb || x >= (int)width || y >= (int)height) return;
    unsigned int *pixel = (unsigned int*)(fb + y * pitch + x * (depth / 8));
    *pixel = color;
}

void fb_draw_char(char c, int x, int y, unsigned int color) {
    if (c < 32 || c > 126) return;
    const unsigned char *glyph = font8x8_basic[c - 32];
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (glyph[row] & (1 << (7 - col))) {
                fb_draw_pixel(x + col, y + row, color);
            }
        }
    }
}

static int cursor_x = 0, cursor_y = 0;

void fb_print(const char *str) {
    if (!fb) return;
    while (*str) {
        if (*str == '\n') {
            cursor_x = 0;
            cursor_y += 10;
        } else {
            fb_draw_char(*str, cursor_x, cursor_y, 0xFFFFFF);
            cursor_x += 8;
            if (cursor_x >= (int)width - 8) {
                cursor_x = 0;
                cursor_y += 10;
            }
        }
        str++;
    }
}





