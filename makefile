CFLAGS = -O2 -nostdlib -nostartfiles -ffreestanding -Wall -Wextra
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

all: kernel.img

start.o: start.s
	$(AS) start.s -o start.o

main.o: main.c fb.h led.h
	$(CC) $(CFLAGS) -c main.c -o main.o

fb.o: fb.c fb.h font8x8.h
	$(CC) $(CFLAGS) -c fb.c -o fb.o

led.o: led.c led.h
	$(CC) $(CFLAGS) -c led.c -o led.o

kernel.elf: start.o main.o fb.o led.o mbox.o
	$(LD) -Ttext=0x8000 -o kernel.elf start.o main.o fb.o led.o mbox.o

kernel.img: kernel.elf
	$(OBJCOPY) kernel.elf -O binary kernel.img

clean:
	rm -f *.o *.elf *.img
