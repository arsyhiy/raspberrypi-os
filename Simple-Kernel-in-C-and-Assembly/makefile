all: nasm gcc ld 

nasm:
	nasm -f elf32 kernel.asm -o kasm.o
gcc:
	gcc -m32 -c kernel.c -o kc.o
ld:
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o

clean:
	rm -rf *.o ./kernel all
