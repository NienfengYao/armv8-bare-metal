// To keep this in the first portion of the binary.
.section ".text.boot"

.global _start
_start:
	/* check CPU ID = 0x0, or jump to hang */
	mrs	x0, mpidr_el1
	and	x0, x0, #3 
	cmp	x0, #0
	bne	hang

/*
 * Reset Vector Base Address,
 */
reset_vector_base:
/*
	GDB hang if read:
		vbar_el3, vbar_el2
		scr_el3, hcr_el2

	ldr	x1, = vector_table_el3
	msr	vbar_el3, x1

	ldr	x1, = vector_table_el2
	msr	vbar_el2, x1
*/
	ldr	x1, = vector_table_el1
	msr	vbar_el1, x1

boot_cpu:
	/* configure stack */
	adrp	x0, stack_top	// Address of 4KB page at a PC-relative offset

main_label:					// Why we need this label let GDB step into main()?
	mov	sp, x0				// sp = stack_top (align with 4KB page)
	bl	main

hang:
	wfi
	b	hang

/*
 * IRQ
 */
.globl enable_irq
enable_irq:
	msr	daifclr, #2
	ret

.globl disable_irq
disable_irq:
	msr	daifset, #2
	ret

/*
 * Exception vectors.
 */
.balign	0x800
vector_table_el3:
curr_el_sp0_sync:			// The exception handler for the synchronous
	bl	sync_test			// exception from the current EL using SP0.

.balign	0x80
curr_el_sp0_irq:			// The exception handler for the IRQ exception
	bl	irq_test			// from the current EL using SP0.

.balign	0x80
curr_el_sp0_fiq:			// The exception handler for the FIQ exception
	bl	fiq_test			// from the current EL using SP0.

.balign	0x80
curr_el_sp0_serror:			// The exception handler for the system error
	bl	serror_test			// exception from the current EL using SP0.

.balign	0x80
vector_table_el2:
curr_el_spx_sync:			// The exception handler for the synchronous
	bl	sync_test			// exception from the current EL using the
							// current SP.

.balign	0x80
curr_el_spx_irq:			// The exception handler for IRQ exception
	bl	irq_test			// from the current EL using the current SP.

.balign	0x80
curr_el_spx_fiq:			// The exception handler for the FIQ exception
	bl	fiq_test			// from the current EL using the current SP.

.balign	0x80
curr_el_spx_serror:			// The exception handler for the system error
	bl	serror_test			// exception from the current EL using the
							// current SP.

.balign	0x80
vector_table_el1:
lower_el_aarch64_sync:		// The exception handler for the synchronous
	bl	sync_test			// exception from a lower EL (AArch64).

.balign	0x80
lower_el_aarch64_irq:		// The exception handler for the IRQ exception
	bl	irq_test			// from a lower EL (AArch64).

.balign	0x80
lower_el_aarch64_fiq:		// The exception handler for the FIQ exception
	bl	fiq_test			// from a lower EL (AArch64).

.balign	0x80
lower_el_aarch64_serror:	// The exception handler for the system error
	bl	serror_test			// exception from a lower EL(AArch64).

.balign	0x80
lower_el_aarch32_sync:		// The exception handler for the synchronous
	bl	sync_test			// exception from a lower EL(AArch32).

.balign	0x80
lower_el_aarch32_irq:		// The exception handler for the IRQ exception
	bl	irq_test						// from a lower EL (AArch32).

.balign	0x80
lower_el_aarch32_fiq:		// The exception handler for the FIQ exception
	bl	fiq_test			// from a lower EL (AArch32).

.balign	0x80
lower_el_aarch32_serror:	// The exception handler for the system error
	bl	serror_test			// exception from a lower EL(AArch32).

