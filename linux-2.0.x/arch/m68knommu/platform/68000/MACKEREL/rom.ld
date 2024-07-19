MEMORY 
	{
        /* romvec only used to determinate size of ROM */
        romvec   : ORIGIN = 0x70000, LENGTH = 0x00

        /* flash memory (512k) */
        flash    : ORIGIN = 0x380000, LENGTH = 0x70000

	  	/* flash memory end */
        eflash   : ORIGIN = 0x3F0000, LENGTH = 1

        /* interrupt vectors in RAM */
	  	ramvec   : ORIGIN = 0x00, LENGTH = 1024

        /* user RAM memory */
		ram      : ORIGIN = 0x400, LENGTH = 0x380000 - 0x400

        /* end of RAM (used to set %sp) */
	    eram     : ORIGIN = 0x380000, LENGTH = 1
	}

SECTIONS
{
 	.romvec :
	{
	_romvec = . ;
	__rom_start = . ;
	} > romvec

        .text :
	{
	text_start = . ;
        *(.text)
        . = ALIGN(4) ;
	_etext = . ;
        *(.rodata)
        . = ALIGN(4) ;
	__data_rom_start = ALIGN ( 4 ) ;
        } > flash

	.eflash :
	{
	_flashend = . ;
	} > eflash

	.ramvec :
	{
	__ram_start = . ;
	_ramvec = . ;
	} > ramvec

        .data :
	{
	_sdata = . ;
	__data_start = . ;
        *(.data)
        . = ALIGN(16) ;
	_edata = . ;
	edata = ALIGN( 0x10 ) ;
        } > ram

        .bss :
        {
	_sbss = ALIGN( 0x10 ) ;
	__bss_start = ALIGN( 0x10 ) ;
	__data_end = ALIGN( 0x10 ) ;
	*(.bss)
        . = ALIGN(4);
	*(COMMON)
	_ebss = . ;
	__bss_end = . ;
        . = ALIGN(16) ;
	end = ALIGN( 0x10 ) ;
	_end = ALIGN( 0x10 ) ;
	} > ram

	.eram :
	{
	_boot_stack = . - 4;
	_ramend = . ;
	} > eram
}

/*
 *Local Variables:
 * mode: c
 * c-indent-level: 8
 * c-brace-imaginary-offset: 0
 * c-brace-offset: -8
 * c-argdecl-indent: 8
 * c-label-offset: -8
 * c-continued-statement-offset: 8
 * c-continued-brace-offset: 0
 * indent-tabs-mode: nil
 * c-file-style: "Linux"
 * fill-column: 76
 * tab-width: 8
 * time-stamp-pattern: "4/<%%>"
 * End:
 */
