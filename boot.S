.text

.global _start
_start:
	/* check CPU ID = 0x0, or jump to hang */
	mrs		x0, mpidr_el1
	and		x0, x0, #3 
	cmp		x0, #0
	bne		hang

boot_cpu:
	/* configure stack */
	adrp	x0,	stack_top	// Address of 4KB page at a PC-relative offset
	mov		sp, x0			// sp = stack_top (align with 4KB page)
	bl		main

hang:
	wfi
	b		hang
