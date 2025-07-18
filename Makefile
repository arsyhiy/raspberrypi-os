AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -O2 -nostdlib -nostartfiles -ffreestanding -Wall -Wextra -mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -march=armv6zk
LDFLAGS = -Ttext=0x8000

all: kernel.img

start.o: start.s
	$(AS) start.s -o start.o

main.o: main.c fb.h led.h
	$(CC) $(CFLAGS) -c main.c -o main.o

fb.o: fb.c fb.h font8x8.h mbox.h pi_config.h
	$(CC) $(CFLAGS) -c fb.c -o fb.o

led.o: led.c led.h pi_config.h
	$(CC) $(CFLAGS) -c led.c -o led.o

mbox.o: mbox.c mbox.h pi_config.h
	$(CC) $(CFLAGS) -c mbox.c -o mbox.o

kernel.elf: start.o main.o fb.o led.o mbox.o
	$(LD) $(LDFLAGS) -o kernel.elf start.o main.o fb.o led.o mbox.o

kernel.img: kernel.elf
	$(OBJCOPY) kernel.elf -O binary kernel.img

clean:
	rm -f *.o *.elf *.img
