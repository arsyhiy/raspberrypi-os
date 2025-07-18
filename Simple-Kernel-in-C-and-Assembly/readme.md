https://github.com/chipsetx/Simple-Kernel-in-C-and-Assembly



Simple Kernel in C and Assembly

Hello, world ! Today I'm going to show you how to write a kernel in C and a little bit of assembly. This is a simple kernel written in C and Assembly which could be loaded with the GRUB bootloader on an x86 system. This kernel will display a message on the screen and then hang. All the source code is available on my github repository.

##Tools Before writing the kernel, make sure that the following tools are available in your system.

    An x86 computer (of course)
    Linux
    NASM assembler
    gcc
    ld (GNU Linker)
    grub

##Let's start coding We like to write everything in C, but we cannot avoid a little bit of assembly. We will write a small file in x86 assembly-language that serves as the starting point for our kernel.

Here is our kernel.asm file.

;;kernel.asm
bits 32		;nasm directive
section .text
	;multiboot spec
	align 4
	dd 0x1BADB002			;magic
	dd 0x00				;flags
	dd - (0x1BADB002 + 0x00)	;checksum. m+f+c should be zero

global start
extern kmain	;kmain is defined in the c file

start:
	cli	;block interrupts
	call kmain
	hlt	;halt the CPU

In the kernel.asm we make a call to kmain. So our execution starts at kmain() in the main C file kernel.c.

/*
 *
 * kernel.c - version 1.0.2
 * 
 */


#define WHITE_TXT 0x07 /* light gray on black text */

void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line);

/* simple kernel written in C */
void k_main() 
{
	k_clear_screen();
	k_printf("Hello, world! Welcome to my kernel.", 0);
};

/* k_clear_screen : to clear the entire text screen */
void k_clear_screen()
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
};

/* k_printf : the message and the line # */
unsigned int k_printf(char *message, unsigned int line)
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	i=(line*80*2);

	while(*message!=0)
	{
		if(*message=='\n') // check for a new line
		{
			line++;
			i=(line*80*2);
			*message++;
		} else {
			vidmem[i]=*message;
			*message++;
			i++;
			vidmem[i]=WHITE_TXT;
			i++;
		};
	};

	return(1);
}

All our kernel will do is clear the screen and write to it the string "Hello, world! Welcome to my kernel."

Now the linker.ld script.

/*
 * link.ld
 */

OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
	. = 0x100000;
	.text : {*(.text)}
	.data : {*(.data)}
	.bss  : {*(.bss)}
}

That's it. All done.

##Building the kernel We will now create object files from kernel.asm and kernel.c and then link it using our linker script.

nasm -f elf32 kernel.asm -o kasm.o

Now we will run the assembler to create the object file kasm.o in ELF-32 bit format.

gcc -m32 -c kernel.c -o kc.o

Now the linking part,

ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o

##Now run your kernel We will now run the kernel on the qemu emulator.

qemu-system-i386 -kernel kernel

That's it.
