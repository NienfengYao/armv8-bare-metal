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
#include "psw.h"
#include "board.h"
#include "gic_v3.h"

extern void timer_handler(void);

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

void irq_handle(exception_frame *exc)
{
	psw_t psw;
	irq_no irq;
	int rc;

	psw_disable_and_save_interrupt(&psw);
	rc = gic_v3_find_pending_irq(exc, &irq);
	if ( rc != IRQ_FOUND )  {
		uart_puts("IRQ not found!\n");
		goto restore_irq_out;
	}else{
		uart_puts("IRQ found: ");
		uart_puthex(irq);
		uart_puts("\n");
	}
	gicd_disable_int(irq);			/* Mask this irq */
	gic_v3_eoi(irq);				/* Send EOI for this irq line */
	timer_handler();
	gicd_enable_int(irq);			/* unmask this irq line */

restore_irq_out:
	psw_restore_interrupt(&psw);
}

void common_trap_handler(exception_frame *exc)
{
	uart_puts("\nException Handler! (");
	//handle_exception(exc);

	if ( ( exc->exc_type & 0xff ) == AARCH64_EXC_SYNC_SPX ) {
		uart_puts("AARCH64_EXC_SYNC_SPX)\n");
		handle_exception(exc);
/*
		ti_update_preempt_count(ti, THR_EXCCNT_SHIFT, 1);
		psw_enable_interrupt();
		hal_handle_exception(exc);
		psw_disable_interrupt();
		ti_update_preempt_count(ti, THR_EXCCNT_SHIFT, -1);
*/
	}

	if ( ( exc->exc_type & 0xff ) == AARCH64_EXC_IRQ_SPX) {
		uart_puts("AARCH64_EXC_IRQ_SPX)\n");
		irq_handle(exc);
	}
	return;
}

