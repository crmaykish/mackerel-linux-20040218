.global _stext
.global _start
.global _boot_stack
.global _ramend
.global boot_entry        
        	.text

/*  Normally the bootloader would set up the stack and program counter
	Don't assume that was done. Set it up at the very start of the Linux code as well */
	.long _ramend	/* Initial stack pointer */
	.long _start	/* Program counter address */

_start:
_stext:

	nop
	movew	#0x2700, %sr		/* disable interrupts: */
	moveal	#_boot_stack, %sp	/* set up stack at the end of RAM: */

#if 1
	/* Copy data segment from ROM to RAM */
	moveal	#__data_rom_start, %a0
	moveal	#__data_start, %a1
	moveal	#__data_end, %a2

	/* Copy %a0 to %a1 until %a1 == %a2 */
LD1:
	movel	%a0@+, %d0
	movel	%d0, %a1@+
	cmpal	%a1, %a2
	bhi	LD1
#endif

	moveal	#__bss_start, %a0
	moveal	#end, %a1

	/* Copy 0 to %a0 until %a0 == %a1 */
L1:
	movel	#0, %a0@+
	cmpal	%a0, %a1
	bhi	L1


	pea	0
	pea	env
	pea	%sp@(4)
	pea	0


        jsr start_kernel

_exit:
        bra	_exit

        .data
env:
	.long	0
