#define GPIO_BASE 0x20200000
#define GPFSEL1   ((volatile unsigned int*)(GPIO_BASE + 0x04))
#define GPSET0    ((volatile unsigned int*)(GPIO_BASE + 0x1C))
#define GPCLR0    ((volatile unsigned int*)(GPIO_BASE + 0x28))
#define GPIO_PIN 16

void led_init() {
    *GPFSEL1 &= ~(7 << 18);
    *GPFSEL1 |=  (1 << 18);
}

void led_on() {
    *GPSET0 = (1 << GPIO_PIN);
}

void led_off() {
    *GPCLR0 = (1 << GPIO_PIN);
}
