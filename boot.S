#define ASM_FILE   1


	.globl _start
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
		GDB hang if access:
			vbar_el3, vbar_el2
			scr_el3, hcr_el2
	*/
	ldr	x1, = vectors
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

