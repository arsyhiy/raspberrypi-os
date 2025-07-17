#include "mbox.h"

#define MBOX_BASE      0x2000B880
#define MBOX_READ      ((volatile unsigned int*)(MBOX_BASE + 0x00))
#define MBOX_STATUS    ((volatile unsigned int*)(MBOX_BASE + 0x18))
#define MBOX_WRITE     ((volatile unsigned int*)(MBOX_BASE + 0x20))

extern volatile unsigned int mbox[36];

int mbox_call(uint8_t ch) {
    unsigned int r = ((unsigned int)((unsigned long)&mbox) & ~0xF) | (ch & 0xF);

    while (*MBOX_STATUS & 0x80000000); // wait until not full
    *MBOX_WRITE = r;

    while (1) {
        while (*MBOX_STATUS & 0x40000000); // wait for message
        if (*MBOX_READ == r)
            return mbox[1] == 0x80000000;
    }
}

