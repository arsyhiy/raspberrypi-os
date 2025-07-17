.global _start
.section .text
_start:
    ldr sp, =0x8000
    bl main
    b .
