
#include "fb.h"
#include "led.h"

void delay(int n) {
    for (volatile int i = 0; i < n * 100000; i++);
}

void main() {
    led_init();
    fb_init();

    int cmd = 0;

    while (1) {
        fb_clear();
        fb_print("Mini-shell framebuffer version\n");
        fb_print("Commands:\n");
        fb_print("0 - led on\n");
        fb_print("1 - led off\n");
        fb_print("2 - blink led\n");
        fb_print("3 - clear screen\n");
        fb_print("Press a key (simulated)...\n");

        switch (cmd) {
            case 0:
                led_on();
                fb_print("LED turned ON\n");
                break;
            case 1:
                led_off();
                fb_print("LED turned OFF\n");
                break;
            case 2:
                for (int i = 0; i < 3; i++) {
                    led_on();
                    delay(5);
                    led_off();
                    delay(5);
                }
                fb_print("LED blinked 3 times\n");
                break;
            case 3:
                fb_clear();
                fb_print("Screen cleared\n");
                break;
            default:
                fb_print("Unknown command\n");
                break;
        }

        cmd++;
        if (cmd > 3) cmd = 0;

        delay(30);
    }
}

