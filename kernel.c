#include <stdint.h>
#include "board.h"
#include "gic-pl390.h"
#include "uart.h"


extern void enable_irq(void);


/*
*	Basic
*/
void exception_svc(void)
{
/*
Supervisor call to allow application code to call the OS. 
	It generates an exception targeting exception level 1 (EL1).
*/
	asm("svc #0xdead");
}

uint32_t read_current_el(void)
{
/*
CurrentEL, Current Exception Level

EL, bits [3:2]
	Current exception level. Possible values of this field are:
	00 EL0
	01 EL1
	10 EL2
	11 EL3
*/
	uint32_t val;

	asm volatile ("mrs %0, CurrentEL" : "=r" (val));
	return val;
}

uint32_t read_daif(void)
{
/* 
DAIF, Interrupt Mask Bits
	Allows access to the interrupt mask bits.

D, bit [9]: Debug exceptions.
A, bit [8]: SError (System Error) mask bit.
I, bit [7]: IRQ mask bit.
F, bit [6]: FIQ mask bit.

value: 
	0 Exception not masked.
	1 Exception masked.
*/
	uint32_t val;

	asm volatile ("mrs %0, daif" : "=r" (val));
	return val;
}

uint32_t read_isr_el1(void)
{
/* 
ISR_EL1, Interrupt Status Register
	Shows whether an IRQ, FIQ, or SError interrupt is pending.
*/
	uint32_t val;

	asm volatile ("mrs %0, isr_el1" : "=r" (val));
	return val;
}

uint32_t read_spsr_el1(void)
{
/* 
SPSR_EL1, Saved Program Status Register (EL1)
	Holds the saved processor state when an exception is taken to EL1.
*/
	uint32_t val;

	asm volatile ("mrs %0, spsr_el1" : "=r" (val));
	return val;
}

uint32_t read_sctlr_el1(void)
{
/* 
SCTLR_EL1, System Control Register (EL1)
	Provides top level control of the system, including its memory system, at EL1.
*/
	uint32_t val;

	asm volatile ("mrs %0, sctlr_el1" : "=r" (val));
	return val;
}

uint32_t read_vbar_el1(void)
{
/* 
VBAR_EL1, Vector Base Address Register (EL1)
	Holds the exception base address for any exception that is taken to EL1.
*/
	uint32_t val;

	asm volatile ("mrs %0, vbar_el1" : "=r" (val));
	return val;
}

uint32_t read_rvbar_el1(void)
{
/* 
RVBAR_EL1, Reset Vector Base Address Register (if EL2 and EL3 not implemented)
	If EL1 is the highest exception level implemented, contains the 
	IMPLEMENTATION DEFINED address that execution starts from after reset when
	executing in AArch64 state.
*/
	uint32_t val;

	asm volatile ("mrs %0, rvbar_el1" : "=r" (val));
	return val;
}

#if 0
uint32_t read_scr_el3(void)
{
/* 
SCR_EL3, Secure Configuration Register
	Defines the configuration of the current security state. It specifies:
	• The security state of EL0 and EL1, either Secure or Non-secure.
	• The register width at lower exception levels.
	• Whether IRQ, FIQ, and External Abort interrupts are taken to EL3.
*/
	uint32_t val;

	asm volatile ("mrs %0, scr_el3" : "=r" (val));
	return val;
}
#endif

static inline void io_halt(void)
{
/*
Wait for Interrupt.
*/
	asm volatile ("wfi");
}

/*
*	Timer
*/  
#define ARM_ARCH_TIMER_ENABLE			(1 << 0)
#define ARM_ARCH_TIMER_IMASK			(1 << 1)
#define ARM_ARCH_TIMER_ISTATUS			(1 << 2)

uint32_t read_cntv_ctl(void)
{
/*
CNTV_CTL_EL0, Counter-timer Virtual Timer Control register
	Control register for the virtual timer.

ISTATUS, bit [2]:	The status of the timer interrupt.
IMASK, bit [1]:		Timer interrupt mask bit.
ENABLE, bit [0]:	Enables the timer.
*/
	uint32_t val;

	asm volatile ("mrs %0, cntv_ctl_el0" : "=r" (val));
	return val;
}

void disable_cntv(void)
{
	uint32_t val;

	val = read_cntv_ctl();
	val &= ~ARM_ARCH_TIMER_ENABLE;
	asm volatile ("msr cntv_ctl_el0, %0" :: "r" (val));
}

void enable_cntv(void)
{
	uint32_t val;

	val = read_cntv_ctl();
	val |= ARM_ARCH_TIMER_ENABLE;
	asm volatile ("msr cntv_ctl_el0, %0" :: "r" (val));
}

uint32_t read_cntfrq(void)
{
/*
CNTFRQ_EL0, Counter-timer Frequency register
	Holds the clock frequency of the system counter.
*/
	uint32_t val;

	asm volatile ("mrs %0, cntfrq_el0" : "=r" (val));
	return val;
}

uint64_t read_cntvct(void)
{
/*
CNTVCT_EL0, Counter-timer Virtual Count register
	Holds the 64-bit virtual count value.
*/
	uint64_t val;
	asm volatile ("mrs %0, cntvct_el0" : "=r" (val));
	return val;
}

uint64_t read_cntv_cval(void)
{
/*
CNTV_CVAL_EL0, Counter-timer Virtual Timer CompareValue register
	Holds the compare value for the virtual timer.
*/
	uint64_t val;

	asm volatile ("mrs %0, cntv_cval_el0" : "=r" (val));
	return val;
}

void write_cntv_cval(uint64_t val)
{
	asm volatile ("msr cntv_cval_el0, %0" :: "r" (val));
	return;
}

void sync_test()
{
    uart_puts("sync_test\n");
}

void irq_test()
{
    uart_puts("irq_test\n");
}

void fiq_test()
{
    uart_puts("fiq_test\n");
}

void serror_test()
{
    uart_puts("serror_test\n");
}

void timer_test(void)
{
	uint32_t cntfrq, val;
	uint64_t ticks, current_cnt;
	uint32_t tmp;

    uart_puts("timer_test\n");

	// GIC Init
	gic_pl390_initialize();

    uart_puts("CurrentEL = ");
	val = read_current_el();
	uart_puthex(val);

    uart_puts("\nRVBAR_EL1 = ");
	val = read_rvbar_el1();
	uart_puthex(val);

    uart_puts("\nVBAR_EL1 = ");
	val = read_vbar_el1();
	uart_puthex(val);

    uart_puts("\nDAIF = ");
	val = read_daif();
	uart_puthex(val);

    uart_puts("\nCNTV_CTL_EL0 = ");
	val = read_cntv_ctl();
	uart_puthex(val);

	// Disable the timer
	disable_cntv();
    uart_puts("\nDisable the timer, CNTV_CTL_EL0 = ");
	val = read_cntv_ctl();
	uart_puthex(val);
    uart_puts("\nCNTFRQ_EL0 = ");
	cntfrq = read_cntfrq();
	uart_puthex(cntfrq);

	// Next timer IRQ is after 1 sec.
	ticks = cntfrq;
	// Get value of the current timer
	current_cnt = read_cntvct();
    uart_puts("\nCNTVCT_EL0 = ");
	uart_puthex(current_cnt);
	// Set the interrupt in Current Time + TimerTick
	write_cntv_cval(current_cnt + ticks);
    uart_puts("\nSet it as next 1 sec, CNTV_CVAL_EL0 = ");
	val = read_cntv_cval();
	uart_puthex(val);

	// Enable the timer
	enable_cntv();
    uart_puts("\nEnable the timer, CNTV_CTL_EL0 = ");
	val = read_cntv_ctl();
	uart_puthex(val);

	// Enable IRQ 
	enable_irq();
    uart_puts("\nEnable IRQ, DAIF = ");
	val = read_daif();
	uart_puthex(val);
    uart_puts("\n");

#if 1 // Observe CNTP_CTL_EL0[2]: ISTATUS
	tmp = 0;
	while(1){
		current_cnt = read_cntvct();
		val = read_cntv_ctl();
		if (tmp <5){
			uart_puts("\nCNTVCT_EL0 = ");
			uart_puthex(current_cnt);
			uart_puts(", CNTV_CTL_EL0 = ");
			uart_puthex(val);
			tmp++;
		}

		if ((val&0x4) != 0){	// Break if ISTATUS is 1
			uart_puts("\nCNTVCT_EL0 = ");
			uart_puthex(current_cnt);
			uart_puts(", CNTV_CTL_EL0 = ");
			uart_puthex(val);
			break;
		}
	}

	val = read_spsr_el1();
	uart_puts("\nSPSR_EL1 = ");
	uart_puthex(val);

	val = read_isr_el1();
	uart_puts("\nISR_EL1 = ");
	uart_puthex(val);

	/*
	val = read_sctlr_el1();
	uart_puts("\nSCTLR_EL1 = ");
	uart_puthex(val);
	*/
#endif

	while(1){
		// Wait for Interrupt.
		io_halt();
	}
}

/*
*	Main
*/
void exception_svc_test(void)
{
	uart_puts("exception_svc_test... start\n");
	/* SVC instruction causes a Supervisor Call exception. */ 
	/* vector_table:_curr_el_spx_sync should be called */
	exception_svc();

	// Wait for Interrupt.
	io_halt();
	uart_puts("exception_svc_test... done\n");
}

int main() {
	exception_svc_test();
	//timer_test();
}


