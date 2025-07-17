
#include "fb.h"
#include "font8x8.h"

volatile unsigned int __attribute__((aligned(16))) mbox[36];

unsigned int width, height, pitch;
unsigned char *fb;

int fb_init() {
    mbox[0] = 35 * 4;
    mbox[1] = 0;

    mbox[2] = 0x00048003; mbox[3] = 8; mbox[4] = 8;
    mbox[5] = 640; mbox[6] = 480;

    mbox[7] = 0x00048004; mbox[8] = 8; mbox[9] = 8;
    mbox[10] = 640; mbox[11] = 480;

    mbox[12] = 0x00048005; mbox[13] = 4; mbox[14] = 4;
    mbox[15] = 32;

    mbox[16] = 0x00040001; mbox[17] = 8; mbox[18] = 8;
    mbox[19] = 16; mbox[20] = 0;

    mbox[21] = 0x00040008; mbox[22] = 8; mbox[23] = 8;
    mbox[24] = 0; mbox[25] = 0;

    mbox[26] = 0;
    
    if (mbox_call(8)) {
    led_on();  // индикация успешной инициализации
    } else {
    led_off(); // ошибка — не инициализировался
    }
    return -1;
}

void fb_clear() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int offs = y * pitch + x * 4;
            fb[offs] = 0;
            fb[offs + 1] = 0;
            fb[offs + 2] = 0;
        }
    }
}

static int cursor_x = 0, cursor_y = 0;

void fb_draw_pixel(int x, int y, unsigned int color) {
    if (!fb || x >= width || y >= height) return;

    unsigned int *pixel = (unsigned int*)(fb + y * pitch + x * (depth / 8));
    *pixel = color;
}


for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
        if (glyph[row] & (1 << col)) {
            // раньше ты писал напрямую в fb
            // теперь вызывай
            fb_draw_pixel(cursor_x + col, cursor_y + row, 0xFFFFFF);
        }
    }
}


