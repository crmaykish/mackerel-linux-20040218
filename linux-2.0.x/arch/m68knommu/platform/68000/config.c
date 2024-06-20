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

// #include "SM2010/sm2010_hw.h"

#include <asm/traps.h>
#include <asm/mackerel.h>

void mackerel_console_initialize(void);

void config_M68000_irq(void);

/* initialize timer hardware */
// static void sm2010_init_timer_hw(void)
// {
//         /* Timer 0 controlwort out = low MODE 0*/
//         SM2010_TIMER.control    = 0x30;
//         SM2010_TIMER.counter0   = 0;
//         SM2010_TIMER.counter0   = 0;
//         /* Timer 2 nur controlwort out = high MODE 2*/
//         SM2010_TIMER.control    = 0xb4;

//         /* timer2 auf 2ms initialisieren */
//         SM2010_TIMER.counter2   = ((SM2010_SIO_CLOCK_SYS / 500)) & 0xff;
//         SM2010_TIMER.counter2   = ((SM2010_SIO_CLOCK_SYS / 500)) >> 8;
//         SM2010_RESET_TIMER_INT2 = 0;
//         SM2010_TIMER.control    = 0x74;
//         SM2010_TIMER.counter1   = (SM2010_SIO_CLOCK_SYS / 1000) & 0xff;
//         SM2010_TIMER.counter1   = (SM2010_SIO_CLOCK_SYS / 1000) >> 8;
// }

static void mackerel_init_timer_hw(void)
{
        printk("Setting up DUART1\n");
        // Setup DUART1
        MEM(DUART1_IMR) = 0x00;        // Mask all interrupts
        MEM(DUART1_MR1B) = 0x13; // No Rx RTS, No Parity, 8 bits per character
        MEM(DUART1_MR2B) = 0x07; // Channel mode normal, No Tx RTS, No CTS, stop bit length 1
        MEM(DUART1_ACR) = 0x80;        // Baudrate set 2
        MEM(DUART1_CRB) = 0x80;        // Set Rx extended bit
        MEM(DUART1_CRB) = 0xA0;        // Set Tx extended bit
        MEM(DUART1_CSRB) = 0x88;       // 115200 baud
        MEM(DUART1_CRB) = 0x05;      // Enable Tx/Rx

        // Setup DUART1 timer as 50 Hz interrupt
        MEM(DUART1_IVR) = 66;   // Interrupt base register
        MEM(DUART1_ACR) = 0xF0; // Set timer mode X/16
        MEM(DUART1_IMR) = 0x08; // Unmask counter interrupt
        MEM(DUART1_CUR) = 0x09; // Counter upper byte, (3.6864MHz / 2 / 16 / 0x900) = 50 Hz
        MEM(DUART1_CLR) = 0x00; // Counter lower byte
        MEM(DUART1_OPR);        // Start counter
}

// static void timer1_interrupt(int irq, void *dummy, struct pt_regs *regs)
// {
//         SM2010_RESET_TIMER_INT1 = 0;
// }



static void
BSP_sched_init(void (*timer_routine)(int, void *, struct pt_regs *))
{
        /* initialize timer */
        // sm2010_init_timer_hw();
        // request_irq(SM2010_INT_NUM_TIMER2-VEC_SPUR,
        //             timer_routine, IRQ_FLG_LOCK, "timer2", NULL);
        // request_irq(SM2010_INT_NUM_TIMER1-VEC_SPUR,
        //             timer1_interrupt, IRQ_FLG_LOCK, "timer1", NULL);

        // printk("\nMC68000 SM2010 support (C) 2002 Weiss-Electronic GmbH, "
        //        "Guido Classen\n");

        mackerel_init_timer_hw();

        request_irq(66-VEC_SPUR,
                    timer_routine, IRQ_FLG_LOCK, "timer", NULL);

        printk("\nMC68000 Mackerel support (C) 2024, Colin Maykish\n");
}

void BSP_tick(void)
{
        /* Reset Timer2 */
        // SM2010_RESET_TIMER_INT2 = 0;

        MEM(DUART1_OPR_RESET); // Stop counter, i.e. reset the timer
}

unsigned long BSP_gettimeoffset(void)
{
        return 0;
}

void BSP_gettod(int *yearp, int *monp, int *dayp,
                int *hourp, int *minp, int *secp)
{
}

int BSP_hwclk(int op, struct hwclk_time *t)
{
        if (!op)
        {
                /* read */
        }
        else
        {
                /* write */
        }
        return 0;
}

int BSP_set_clock_mmss(unsigned long nowtime)
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

void BSP_reset(void)
{
        cli();
        HARD_RESET_NOW();
}

void config_BSP(char *command, int len)
{
        // mpsc_console_initialize();

        

        mackerel_console_initialize();

        mach_sched_init = BSP_sched_init;
        mach_tick = BSP_tick;
        mach_gettimeoffset = BSP_gettimeoffset;
        mach_gettod = BSP_gettod;
        mach_hwclk = NULL;
        mach_set_clock_mmss = NULL;
        mach_mksound = NULL;
        mach_reset = BSP_reset;
        mach_debug_init = NULL;

        config_M68000_irq();

        /* enable interrupts :-) */
        // SM2010_BOARD_CONTROL = 0x1f;
}
