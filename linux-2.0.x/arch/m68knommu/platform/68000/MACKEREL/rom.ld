/*****************************************************************************/
/* 
 *  crt0_rom.S
 * 
 *  linux/arch/m68knommu/platform/68000/68Katy/rom.ld
 *
*   68Katy GNU ld command file for running kernel directly from ROM
 *  you probably need an own version of this file for your board
 *
 *  Author:     Steve Chamberlin (steve.chamberlin@gmail.com)
 *
 *  This program is free software;  you can redistribute it and/or modify it
 *  under the  terms of the GNU  General Public License as  published by the
 *  Free Software Foundation.  See the file COPYING in the main directory of
 *  this archive for more details.
 *
 *  This program  is distributed  in the  hope that it  will be  useful, but
 *  WITHOUT   ANY   WARRANTY;  without   even   the   implied  warranty   of
 *  MERCHANTABILITY  or  FITNESS FOR  A  PARTICULAR  PURPOSE.   See the  GNU
 *  General Public License for more details.
 * *
 *  Change history:
 *
 */
 /****************************************************************************/

MEMORY 
	{
          /* romvec only used to determinate size of ROM */
          romvec   : ORIGIN = 0x80000, LENGTH = 0x00
            
          /* 68Katy flash memory (480k) */
          flash    : ORIGIN = 0x100000, LENGTH = 0x80000
        
	  /* 68Katy flash memory end */
          eflash   : ORIGIN = 0x180000, LENGTH = 1

          /* interrupt vectors in RAM */
	  ramvec   : ORIGIN = 0x00, LENGTH = 1024

          /* user RAM memory */
	  ram      : ORIGIN = 0x400, LENGTH = 0x100000 - 0x400

          /* end of RAM (used to set %sp) */
	  eram     : ORIGIN = 0x100000, LENGTH = 1
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
