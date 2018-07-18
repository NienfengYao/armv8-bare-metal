/* -*- mode: c; coding:utf-8 -*- */
/**********************************************************************/
/*  OS kernel sample                                                  */
/*  Copyright 2014 Takeharu KATO                                      */
/*                                                                    */
/*  Exception handler                                                 */
/*                                                                    */
/**********************************************************************/

#include "exception.h"
#include "uart.h"

#if 0 //RyanYao
#include <kern/kernel.h>

#include <hal/exception.h>
#endif

void handle_exception(exception_frame *exc) {
	uart_puts("An exception occur:\n");
	uart_puts("exc_type: ");
	uart_puthex(exc->exc_type);
	uart_puts("\nESR: "); uart_puthex(exc->exc_esr);
	uart_puts("  SP: "); uart_puthex(exc->exc_sp);
	uart_puts(" ELR: "); uart_puthex(exc->exc_elr);
	uart_puts(" SPSR: "); uart_puthex(exc->exc_spsr);
	uart_puts("\n x0: "); uart_puthex(exc->x0);
	uart_puts("  x1: "); uart_puthex(exc->x1);
	uart_puts("  x2: "); uart_puthex(exc->x2);
	uart_puts("  x3: "); uart_puthex(exc->x3);
	uart_puts("\n x4: "); uart_puthex(exc->x4);
	uart_puts("  x5: "); uart_puthex(exc->x5);
	uart_puts("  x6: "); uart_puthex(exc->x6);
	uart_puts("  x7: "); uart_puthex(exc->x7);
	uart_puts("\n x8: "); uart_puthex(exc->x8);
	uart_puts("  x9: "); uart_puthex(exc->x9);
	uart_puts(" x10: "); uart_puthex(exc->x10);
	uart_puts(" x11: "); uart_puthex(exc->x11);
	uart_puts("\nx12: "); uart_puthex(exc->x12);
	uart_puts(" x13: "); uart_puthex(exc->x13);
	uart_puts(" x14: "); uart_puthex(exc->x14);
	uart_puts(" x15: "); uart_puthex(exc->x15);
	uart_puts("\nx16: "); uart_puthex(exc->x16);
	uart_puts(" x17: "); uart_puthex(exc->x17);
	uart_puts(" x18: "); uart_puthex(exc->x18);
	uart_puts(" x19: "); uart_puthex(exc->x19);
	uart_puts("\nx20: "); uart_puthex(exc->x20);
	uart_puts(" x21: "); uart_puthex(exc->x21);
	uart_puts(" x22: "); uart_puthex(exc->x22);
	uart_puts(" x23: "); uart_puthex(exc->x23);
	uart_puts("\nx24: "); uart_puthex(exc->x24);
	uart_puts(" x25: "); uart_puthex(exc->x25);
	uart_puts(" x26: "); uart_puthex(exc->x26);
	uart_puts(" x27: "); uart_puthex(exc->x27);
	uart_puts("\nx28: "); uart_puthex(exc->x28);
	uart_puts(" x29: "); uart_puthex(exc->x29);
	uart_puts(" x30: "); uart_puthex(exc->x30);
}

void common_trap_handler(exception_frame *exc){
	uart_puts("common_trap_handler!\n");
	//handle_exception(exc);
	//thread_info_t *ti;

	if ( ( exc->exc_type & 0xff ) == AARCH64_EXC_SYNC_SPX ) {
		uart_puts("AARCH64_EXC_SYNC_SPX\n");
		handle_exception(exc);
/*
		ti_update_preempt_count(ti, THR_EXCCNT_SHIFT, 1);
		psw_enable_interrupt();
		hal_handle_exception(exc);
		psw_disable_interrupt();
		ti_update_preempt_count(ti, THR_EXCCNT_SHIFT, -1);
*/
	}

#if 0 //RyanYao
	if ( ( exc->exc_type & 0xf ) == 0x2 ) {

		ti_update_preempt_count(ti, THR_IRQCNT_SHIFT, 1);
		irq_handle_irq(exc);
		ti_update_preempt_count(ti, THR_IRQCNT_SHIFT, -1);
	}

	sched_delay_disptach();  /*  遅延ディスパッチ  */
#endif

	return;
}

