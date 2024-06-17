/*****************************************************************************/
/* 
 *  config.c v1.0 <2003-07-28 17:55:00 gc>
 * 
 *  linux/arch/m68knommu/platform/68000/config.c
 *
 *  uClinux version 2.0.x MC68000 SM2010 board initalization
 *
 *  Author:     Guido Classen (classeng@clagi.de)
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
 *
 *  Thanks to:
 *    inital code taken from 68328/config.c
 *
 *      Copyright (C) 1993 Hamish Macdonald
 *      Copyright (C) 1999 D. Jeff Dionne
 *
 *  Change history:
 *       2002-05-15 G. Classen: initial version for MC68000
 *
 */
 /****************************************************************************/

#include <stdarg.h>
#include <linux/config.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/tty.h>
#include <linux/console.h>

#include <asm/setup.h>
#include <asm/system.h>
#include <asm/pgtable.h>
#include <asm/irq.h>
#include <asm/machdep.h>

#include <asm/mackerel.h>

void config_M68000_irq(void);


static void 
BSP_sched_init(void (*timer_routine)(int, void *, struct pt_regs *))
{
        // TODO

        printk("Mackerel 68k support by Colin Maykish 2024\n");
}

void BSP_tick(void)
{

}

unsigned long BSP_gettimeoffset(void)
{
        return 0;
}

void BSP_gettod (int *yearp, int *monp, int *dayp,
                 int *hourp, int *minp, int *secp)
{
}

int BSP_hwclk(int op, struct hwclk_time *t)
{
        if (!op) {
                /* read */
        } else {
                /* write */
        }
        return 0;
}

int BSP_set_clock_mmss (unsigned long nowtime)
{
#if 0
        short real_seconds = nowtime % 60, real_minutes = (nowtime / 60) % 60;

        tod->second1 = real_seconds / 10;
        tod->second2 = real_seconds % 10;
        tod->minute1 = real_minutes / 10;
        tod->minute2 = real_minutes % 10;
#endif
        return 0;
}

void BSP_reset (void)
{
        cli();
        HARD_RESET_NOW();
}

void config_BSP(char *command, int len)
{
        duart_putc('M');
        duart_putc('M');
        duart_putc('M');
        duart_putc('M');
        duart_putc('M');
        duart_putc('M');
        duart_putc('M');
        duart_putc('M');
        duart_putc('M');
        duart_putc('M');

        mc68681_console_initialize();

        mach_sched_init      = BSP_sched_init;
        mach_tick            = BSP_tick;
        mach_gettimeoffset   = BSP_gettimeoffset;
        mach_gettod          = BSP_gettod;
        mach_hwclk           = NULL;
        mach_set_clock_mmss  = NULL;
        mach_mksound         = NULL;
        mach_reset           = BSP_reset;
        mach_debug_init      = NULL;

        config_M68000_irq();

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
