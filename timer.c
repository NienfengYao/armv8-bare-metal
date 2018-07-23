#include <stdint.h>
#include "aarch64.h"
#include "board.h"
#include "gic_v3.h"
#include "uart.h"
#include "timer.h"

#define TIMER_DEBUG		0
#define TIMER_WAIT		1	/* Assert Timer IRQ after n secs */

static uint32_t cntfrq;		/* System frequency */

#if TIMER_DEBUG
void timer_handler(void){}
#else
/* Assert Timer IRQ after n secs */
void timer_handler(void)
{
	uint64_t ticks, current_cnt;
	uint32_t val;

    uart_puts("timer_handler: \n");

	// Disable the timer
	disable_cntv();
    uart_puts("\tDisable the timer, CNTV_CTL_EL0 = ");
	val = raw_read_cntv_ctl();
	uart_puthex(val);
	gicd_clear_pending(TIMER_IRQ);
    uart_puts("\n\tSystem Frequency: CNTFRQ_EL0 = ");
	uart_puthex(cntfrq);

	// Next timer IRQ is after n sec.
	ticks = TIMER_WAIT * cntfrq;
	// Get value of the current timer
	current_cnt = raw_read_cntvct_el0();
    uart_puts("\n\tCurrent counter: CNTVCT_EL0 = ");
	uart_puthex(current_cnt);
	// Set the interrupt in Current Time + TimerTick
	raw_write_cntv_cval_el0(current_cnt + ticks);
    uart_puts("\n\tAssert Timer IRQ after ");
	uart_puthex(TIMER_WAIT);
    uart_puts(" sec(s): CNTV_CVAL_EL0 = ");
	val = raw_read_cntv_cval_el0();
	uart_puthex(val);

	// Enable the timer
	enable_cntv();
    uart_puts("\n\tEnable the timer, CNTV_CTL_EL0 = ");
	val = raw_read_cntv_ctl();
	uart_puthex(val);
    uart_puts("\n");
}
#endif /* TIMER_DEBUG */

void timer_test(void)
{
	uint32_t val;
	uint64_t ticks, current_cnt;

    uart_puts("timer_test\n");
	// GIC Init
	gic_v3_initialize();

    uart_puts("CurrentEL = ");
	val = raw_read_current_el();
	uart_puthex(val);

    uart_puts("\nRVBAR_EL1 = ");
	val = raw_read_rvbar_el1();
	uart_puthex(val);

    uart_puts("\nVBAR_EL1 = ");
	val = raw_read_vbar_el1();
	uart_puthex(val);

    uart_puts("\nDAIF = ");
	val = raw_read_daif();
	uart_puthex(val);

	// Disable the timer
	disable_cntv();
    uart_puts("\nDisable the timer, CNTV_CTL_EL0 = ");
	val = raw_read_cntv_ctl();
	uart_puthex(val);
    uart_puts("\nSystem Frequency: CNTFRQ_EL0 = ");
	cntfrq = raw_read_cntfrq_el0();
	uart_puthex(cntfrq);

	// Next timer IRQ is after n sec(s).
	ticks = TIMER_WAIT * cntfrq;
	// Get value of the current timer
	current_cnt = raw_read_cntvct_el0();
    uart_puts("\nCurrent counter: CNTVCT_EL0 = ");
	uart_puthex(current_cnt);
	// Set the interrupt in Current Time + TimerTick
	raw_write_cntv_cval_el0(current_cnt + ticks);
    uart_puts("\nAssert Timer IRQ after 1 sec: CNTV_CVAL_EL0 = ");
	val = raw_read_cntv_cval_el0();
	uart_puthex(val);

	// Enable the timer
	enable_cntv();
    uart_puts("\nEnable the timer, CNTV_CTL_EL0 = ");
	val = raw_read_cntv_ctl();
	uart_puthex(val);

	// Enable IRQ 
	enable_irq();
    uart_puts("\nEnable IRQ, DAIF = ");
	val = raw_read_daif();
	uart_puthex(val);
    uart_puts("\n");

#if TIMER_DEBUG // Observe CNTP_CTL_EL0[2]: ISTATUS
	while(1){
		current_cnt = raw_read_cntvct_el0();
		val = raw_read_cntv_ctl();
		uart_puts("\nCNTVCT_EL0 = ");
		uart_puthex(current_cnt);
		uart_puts(", CNTV_CTL_EL0 = ");
		uart_puthex(val);
		val = raw_read_spsr_el1();
		uart_puts(", SPSR_EL1 = ");
		uart_puthex(val);
		val = raw_read_isr_el1();
		uart_puts(", ISR_EL1 = ");
		uart_puthex(val);
		uart_puts("\n");
	}
#else
	while(1){
		wfi();	/* Wait for Interrupt */
	}
#endif
}
