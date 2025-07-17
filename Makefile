CROSS_COMPILE = arm-none-eabi-
CFLAGS = -O2 -nostdlib -nostartfiles -ffreestanding

all: kernel.elf

kernel.elf: start.o main.o
	$(CROSS_COMPILE)ld -Ttext=0x8000 -o kernel.elf start.o main.o

%.o: %.c
	$(CROSS_COMPILE)gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CROSS_COMPILE)as $< -o $@

clean:
	rm -f *.o *.elf *.img