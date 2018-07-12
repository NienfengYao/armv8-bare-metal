/* -*- mode: c; coding:utf-8 -*- */
/**********************************************************************/
/*  OS kernel sample                                                  */
/*  Copyright 2014 Takeharu KATO                                      */
/*                                                                    */
/*  Arm Generic Interrupt Controller(PL390)                           */
/*                                                                    */
/**********************************************************************/

#if 0 //RyanYao
#include <kern/kernel.h>

#include <hal/hal.h>
#endif


#include <stdint.h>
#include "board.h"
#include "gic-pl390.h"
#include "uart.h"

#define RYAN_DEBUG 1

#if 0 //RyanYao
static irq_ctrlr arm_gic_ctrlr = {
	.config_irq = gic_pl390_config_irq,
	.enable_irq = gic_pl390_enable_irq,
	.disable_irq = gic_pl390_disable_irq,
	.eoi = gic_pl390_eoi,
	.initialize = gic_pl390_initialize,
	.finalize = gic_pl390_finalize,
	.private = NULL
};
#endif

/** Initialize GIC Controller
 * ARM Generic Interrupt Controller Architecture Specification version 1.0
 * Architecture Specification
 */
static void init_gicc(void) {
	uint32_t pending_irq;
	uint32_t val;

	/*
	 *  Disable CPU interface
	 */
	*REG_GIC_GICC_ICR = GICC_ICR_DISABLE;
	#if RYAN_DEBUG //RyanYao
	uart_puts("GICC_CTLR: ");
	uart_puthex(GIC_GICC_ICR);
	uart_puts(" = ");
	val = *REG_GIC_GICC_ICR;
	uart_puthex(val);
	uart_puts("\n");
	#endif

	/*
	 *  Set the priority level as the lowest priority.
	 */
	/* Note: Higher priority corresponds to a lower Priority field value in the GIC_PMR.
	 * In addition to this, writing 255 to the GICC_PMR always sets it to the 
	 * largest supported priority field value.
	 * See. ARM Generic Interrupt Controller Architecture Specification version 2.0
	 * 3.3 Interrupt prioritization and 3.3.2 Priority masking
	 * for each issue.
	 */
	*REG_GIC_GICC_PMR = GICC_PMR_PRIO_MIN;
	#if RYAN_DEBUG //RyanYao
	uart_puts("REG_GIC_GICC_PMR: ");
	uart_puthex(GIC_GICC_PMR);
	uart_puts(" = ");
	val = *REG_GIC_GICC_PMR;
	uart_puthex(val);
	uart_puts("\n");
	#endif

	/*
	 *  Handle all of interrupts in a single group.
	 */
	*REG_GIC_GICC_BPR = GICC_BPR_NO_GROUP;
	#if RYAN_DEBUG //RyanYao
	uart_puts("REG_GIC_GICC_BPR : ");
	uart_puthex(GIC_GICC_BPR);
	uart_puts(" = ");
	val = *REG_GIC_GICC_BPR;
	uart_puthex(val);
	uart_puts("\n");
	#endif

	/*
	 *  Clear all of the active interrupts
	 */
	for(pending_irq = ( *REG_GIC_GICC_IAR & GICC_IAR_INTR_IDMASK ); 
	    ( pending_irq != GICC_IAR_SPURIOUS_INTR );
	    pending_irq = ( *REG_GIC_GICC_IAR & GICC_IAR_INTR_IDMASK ) )
		*REG_GIC_GICC_EOI = *REG_GIC_GICC_IAR;
	#if RYAN_DEBUG //RyanYao
	uart_puts("REG_GIC_GICC_EOI : Clear all of the active interrupts\n");
	#endif
	/*
	 * Enable CPU interface
	 */
	*REG_GIC_GICC_ICR = GICC_ICR_ENABLE;
	#if RYAN_DEBUG //RyanYao
	uart_puts("REG_GIC_GICC_CTLR : ");
	uart_puthex(GIC_GICC_ICR);
	uart_puts(" = ");
	val = *REG_GIC_GICC_ICR;
	uart_puthex(val);
	uart_puts("\n");
	#endif
}

#if 0
static void
finalize_gicc(void) {

	/*
	 *  Disable CPU interface
	 */
	*REG_GIC_GICC_ICR = GICC_ICR_DISABLE;
}
#endif

static void init_gicd(void) {
	int32_t	      i;
	int32_t	regs_nr;
	uint32_t val;

	/*
	 *  Diable distributor
	 */
    uart_puts("init_gicd()\n");

	*REG_GIC_GICD_CTLR = GIC_GICD_CTLR_DISABLE;
	#if RYAN_DEBUG //RyanYao
	uart_puts("REG_GIC_GICD_CTLR: ");
	uart_puthex(GIC_GICD_CTLR);
	uart_puts(" = ");
	val = *REG_GIC_GICD_CTLR;
	uart_puthex(val);
	uart_puts("\n");
	#endif

	/*
	 *  Disable all IRQs
	 */
	regs_nr = (GIC_INT_MAX + GIC_GICD_INT_PER_REG - 1) / GIC_GICD_INT_PER_REG;
	for (i = 0; regs_nr > i; ++i)
		*REG_GIC_GICD_ICENABLER(i) = ~((uint32_t)(0)); 
	#if RYAN_DEBUG
	uart_puts("Write REG_GIC_GICD_ICENABLER:\n");
	for (i = 0; regs_nr > i; ++i){
		uart_puthex(GIC_GICD_ICENABLER(i));
		uart_puts(" = ");
		val = ~((uint32_t)(0));
		uart_puthex(val);
		uart_puts("\n");
	}
	#endif
	#if 0 //RyanYao: It should not be read
	uart_puts("REG_GIC_GICD_ICENABLER:\n");
	for (i = 0; regs_nr > i; ++i){
		uart_puthex(GIC_GICD_ICENABLER(i));
		uart_puts(" = ");
		val = *REG_GIC_GICD_ICENABLER(i);
		uart_puthex(val);
		uart_puts("\n");
	}
	#endif

	/*
	 *  Clear all pending IRQs
	 */
	regs_nr = (GIC_INT_MAX + GIC_GICD_INT_PER_REG - 1) / GIC_GICD_INT_PER_REG;
	for (i = 0; regs_nr > i; ++i) 
		*REG_GIC_GICD_ICPENDR(i) = ~((uint32_t)(0));
	#if RYAN_DEBUG //RyanYao: we set bit-1, but read bit-0. It's reasonable.
	uart_puts("Write REG_GIC_GICD_ICPENDR:\n");
	for (i = 0; regs_nr > i; ++i){
		uart_puthex(GIC_GICD_ICPENDR(i));
		uart_puts(" = ");
		val = ~((uint32_t)(0));
		uart_puthex(val);
		uart_puts("\n");
	}
	#endif
	#if 0 //RyanYao: we set bit-1, but read bit-0. It's reasonable.
	uart_puts("REG_GIC_GICD_ICPENDR:\n");
	for (i = 0; regs_nr > i; ++i){
		uart_puthex(GIC_GICD_ICPENDR(i));
		uart_puts(" = ");
		val = *REG_GIC_GICD_ICPENDR(i);
		uart_puthex(val);
		uart_puts("\n");
	}
	#endif

	/*
	 *  Set all of interrupt priorities as the lowest priority.
	 */
	regs_nr = ( GIC_INT_MAX + GIC_GICD_IPRIORITY_PER_REG - 1) / 
		GIC_GICD_IPRIORITY_PER_REG ;
	for (i = 0; regs_nr > i; i++)
		*REG_GIC_GICD_IPRIORITYR(i) = ~((uint32_t)(0));
	#if RYAN_DEBUG //RyanYao
	uart_puts("REG_GIC_GICD_IPRIORITYR:\n");
	for (i = 0; regs_nr > i; i++){
		uart_puthex(GIC_GICD_IPRIORITYR(i));
		uart_puts(" = ");
		val = *REG_GIC_GICD_IPRIORITYR(i);
		uart_puthex(val);
		uart_puts("\n");
	}
	#endif

	/*
	 *  Set target of all of shared peripherals to processor 0.
	 */
	for (i = GIC_INTNO_SPI0 / GIC_GICD_ITARGETSR_PER_REG;
	     ( (GIC_INT_MAX + (GIC_GICD_ITARGETSR_PER_REG - 1) ) / 
		 GIC_GICD_ITARGETSR_PER_REG ) > i; ++i) 
		*REG_GIC_GICD_ITARGETSR(i) = 
			(uint32_t)GIC_GICD_ITARGETSR_CORE0_TARGET_BMAP;
	#if RYAN_DEBUG //RyanYao, Do we need this? I only want to use PPI
	uart_puts("REG_GIC_GICD_ITARGETSR:\n");
	for (i = GIC_INTNO_SPI0 / GIC_GICD_ITARGETSR_PER_REG;
	     ( (GIC_INT_MAX + (GIC_GICD_ITARGETSR_PER_REG - 1) ) / 
		 GIC_GICD_ITARGETSR_PER_REG ) > i; ++i) {
		uart_puthex(GIC_GICD_ITARGETSR(i));
		uart_puts(" = ");
		val = *REG_GIC_GICD_ITARGETSR(i);
		uart_puthex(val);
		uart_puts("\n");
	}
	#endif

	/*
	 *  Set trigger type for all peripheral interrupts level triggered.
	 */
	for (i = GIC_INTNO_PPI0 / GIC_GICD_ICFGR_PER_REG;
	     (GIC_INT_MAX + (GIC_GICD_ICFGR_PER_REG - 1)) / GIC_GICD_ICFGR_PER_REG > i; ++i)
		*REG_GIC_GICD_ICFGR(i) = 0;
	#if RYAN_DEBUG
	uart_puts("REG_GIC_GICD_ICFGR:\n");
	for (i = GIC_INTNO_PPI0 / GIC_GICD_ICFGR_PER_REG;
	     (GIC_INT_MAX + (GIC_GICD_ICFGR_PER_REG - 1)) / GIC_GICD_ICFGR_PER_REG > i; ++i){
		uart_puthex(GIC_GICD_ICFGR(i));
		uart_puts(" = ");
		val = *REG_GIC_GICD_ICFGR(i);
		uart_puthex(val);
		uart_puts("\n");
	}
	#endif

	/*
	 *  Enable distributor
	 */
	*REG_GIC_GICD_CTLR = GIC_GICD_CTLR_ENABLE;
	#if RYAN_DEBUG //RyanYao
	uart_puts("REG_GIC_GICD_CTLR: ");
	uart_puthex(GIC_GICD_CTLR);
	uart_puts(" = ");
	val = *REG_GIC_GICD_CTLR;
	uart_puthex(val);
	uart_puts("\n");
	#endif
}
#if 0 //RyanYao

/** Finalize GICD
 */
static void
finalize_gicd(void) {

	/*
	 *  Disable distributor
	 */
	*REG_GIC_GICD_CTLR = GIC_GICD_CTLR_DISABLE;
}

/** Disable IRQ
    @param[in] irq IRQ number
 */
static void
gicd_disable_int(irq_no irq) {

	*REG_GIC_GICD_ICENABLER( (irq / GIC_GICD_ICENABLER_PER_REG) ) = 
		1U << ( irq % GIC_GICD_ICENABLER_PER_REG );
}
#endif

/** Enable IRQ
    @param[in] irq IRQ number
 */
static void gicd_enable_int(irq_no irq) {
	uint32_t val;

	*REG_GIC_GICD_ISENABLER( (irq / GIC_GICD_ISENABLER_PER_REG) ) =
		1U << ( irq % GIC_GICD_ISENABLER_PER_REG );

	#if RYAN_DEBUG //RyanYao
	uart_puts("REG_GIC_GICD_ISENABLER: ");
	uart_puthex((GIC_GICD_ISENABLER( (irq / GIC_GICD_ISENABLER_PER_REG) )));
	uart_puts(" = ");
	val = *REG_GIC_GICD_ISENABLER( (irq / GIC_GICD_ISENABLER_PER_REG) );
	uart_puthex(val);
	uart_puts("\n");
	#endif
}

/** Clear a pending interrupt
    @param[in] irq IRQ number
 */
static void
gicd_clear_pending(irq_no irq) {

	*REG_GIC_GICD_ICPENDR( (irq / GIC_GICD_ICPENDR_PER_REG) ) = 
		1U << ( irq % GIC_GICD_ICPENDR_PER_REG );
}

#if 0 //RyanYao
/** Set interrupt pending
    @param[in] irq IRQ number
 */
static void
gicd_set_pending(irq_no irq) {

	*REG_GIC_GICD_ISPENDR( (irq / GIC_GICD_ISPENDR_PER_REG) ) =
		1U << ( irq % GIC_GICD_ISPENDR_PER_REG );
}

/** Probe pending interrupt
    @param[in] irq IRQ number
 */
static int
gicd_probe_pending(irq_no irq) {
	int is_pending;

	is_pending = ( *REG_GIC_GICD_ISPENDR( (irq / GIC_GICD_ISPENDR_PER_REG) ) &
	    ( 1U << ( irq % GIC_GICD_ISPENDR_PER_REG ) ) );

	return ( is_pending != 0 );
}
#endif

/** Set an interrupt target processor
    @param[in] irq IRQ number
    @param[in] p   Target processor mask
    0x1 processor 0
    0x2 processor 1
    0x4 processor 2
    0x8 processor 3
 */
static void
gicd_set_target(irq_no irq, uint32_t p){
	uint32_t  shift;
	uint32_t    reg;

	shift = (irq % GIC_GICD_ITARGETSR_PER_REG) * GIC_GICD_ITARGETSR_SIZE_PER_REG;

	reg = *REG_GIC_GICD_ITARGETSR(irq / GIC_GICD_ITARGETSR_PER_REG);
	reg &= ~( ((uint32_t)(0xff)) << shift);
	reg |= (p << shift);
	*REG_GIC_GICD_ITARGETSR(irq / GIC_GICD_ITARGETSR_PER_REG) = reg;
}

/** Set an interrupt priority
    @param[in] irq  IRQ number
    @param[in] prio Interrupt priority in Arm specific expression
 */
static void
gicd_set_priority(irq_no irq, uint32_t prio){
	uint32_t  shift;
	uint32_t    reg;

	shift = (irq % GIC_GICD_IPRIORITY_PER_REG) * GIC_GICD_IPRIORITY_SIZE_PER_REG;
	reg = *REG_GIC_GICD_IPRIORITYR(irq / GIC_GICD_IPRIORITY_PER_REG);
	reg &= ~(((uint32_t)(0xff)) << shift);
	reg |= (prio << shift);
	*REG_GIC_GICD_IPRIORITYR(irq / GIC_GICD_IPRIORITY_PER_REG) = reg;
}

/** Configure IRQ line
    @param[in] irq     IRQ number
    @param[in] config  Configuration value for GICD_ICFGR
 */
static void
gicd_config(irq_no irq, unsigned int config){
	uint32_t	shift; 
	uint32_t	  reg;

	shift = (irq % 16) * 2; /* GICD_ICFGR has 16 fields, each field has 2bits. */

	reg = *REG_GIC_GICD_ICFGR( irq / 16 );

	reg &= ~( ( (uint32_t)(0x03) ) << shift );  /* Clear the field */
	reg |= ( ( (uint32_t)config ) << shift );  /* Set the value to the field correponding to irq */
	*REG_GIC_GICD_ICFGR( irq / 16 ) = reg;
}

#if 0 //RyanYao
/** Configure IRQ line for GIC
    @param[in] ctrlr   IRQ controller information
    @param[in] irq     IRQ number
    @param[in] attr    IRQ attribution
    @param[in] prio    Interrupt priority(Architecture Common Expression)
      0 ... The highest
     15 ... The lowest
 */
static int 
gic_pl390_config_irq(struct _irq_ctrlr *ctrlr __attribute__((unused)), 
    irq_no irq, irq_attr attr, irq_prio prio){

	gic_pl390_disable_irq(ctrlr, irq);

	if ( attr & IRQ_ATTR_EDGE ) {

		gicd_config(irq, GIC_GICD_ICFGR_EDGE);
		gicd_clear_pending(irq);
	} else {

		gicd_config(irq, GIC_GICD_ICFGR_LEVEL);
	}
	gicd_set_priority(irq, (prio & GIC_PRI_MASK) << GIC_PRI_SHIFT );  /* Set priority */
	gicd_set_target(irq, 0x1);  /* processor 0 */

	return 0;
}

/** Enable IRQ line for GIC
    @param[in] ctrlr   IRQ controller information
    @param[in] irq     IRQ number
 */
static void 
gic_pl390_enable_irq(struct _irq_ctrlr *ctrlr __attribute__((unused)), irq_no irq){

	gicd_enable_int(irq);
}

/** Disable IRQ line for GIC
    @param[in] ctrlr   IRQ controller information
    @param[in] irq     IRQ number
 */
static void
gic_pl390_disable_irq(struct _irq_ctrlr *ctrlr __attribute__((unused)), irq_no irq) {

	gicd_disable_int(irq);
}

/** Send End of Interrupt to IRQ line for GIC
    @param[in] ctrlr   IRQ controller information
    @param[in] irq     IRQ number
 */
static void
gic_pl390_eoi(struct _irq_ctrlr *ctrlr __attribute__((unused)), irq_no irq) {

	gicd_clear_pending(irq);
}
#endif

/** Initialize GIC IRQ controller
    @param[in] ctrlr   IRQ controller information
 */
#if 1 //RyanYao
void gic_pl390_initialize(void){

    uart_puts("gic_pl390_initialize\n");
	/* Set trigger type for all peripheral interrupts level triggered */
	init_gicd();
	init_gicc();
	gicd_config(27, GIC_GICD_ICFGR_EDGE);
	gicd_set_priority(27, 0 << GIC_PRI_SHIFT );  /* Set priority */
	gicd_set_target(27, 0x1);  /* processor 0 */
	gicd_clear_pending(27);
	gicd_enable_int(27);
}
#else
static int
gic_pl390_initialize(struct _irq_ctrlr *ctrlr){

	init_gicd();
	init_gicc();
	ctrlr->private = NULL;
}
#endif

#if 0 //RyanYao
/** Finalize GIC IRQ controller
    @param[in] ctrlr   IRQ controller information
 */
static void
gic_pl390_finalize(struct _irq_ctrlr *ctrlr){

	finalize_gicc();
	finalize_gicd();
	ctrlr->private = NULL;
}

/** Find pending IRQ
    @param[in]     exc  An exception frame
    @param[in,out] irqp An IRQ number to be processed
 */
static int
gic_pl390_find_pending_irq(struct _exception_frame *exc __attribute__((unused)), irq_no *irqp) {
	int   rc;
	irq_no i;

	for( i = 0; GIC_INT_MAX > i; ++i) {
		if ( gicd_probe_pending(i) ) {

			rc = IRQ_FOUND;
			*irqp = i;
			goto found;
		}
	}

	rc = IRQ_NOT_FOUND ;
found:
	return rc;
}


int 
test_handler(irq_no irq, struct _exception_frame *exc, void *private __attribute__((unused))){

	kprintf("Handler\n");
	return IRQ_HANDLED;
}

/** Initialize interrupt facilities 
 */
void 
aarch64_init_interrupt(void){
	int i;

	aarch64_setup_vector();

	irq_register_pending_irq_finder(gic_pl390_find_pending_irq);

	for(i = 0; GIC_INT_MAX > i; ++i) 
		irq_register_ctrlr(i, &arm_gic_ctrlr);

	gic_pl390_initialize(&arm_gic_ctrlr);
	irq_register_handler(35, IRQ_ATTR_EXCLUSIVE | IRQ_ATTR_NESTABLE | IRQ_ATTR_EDGE, 
	    1, NULL, test_handler);

}

/** Raise Interrupt(Debugging use)
    @param[in] irq     IRQ number
 */
void
gic_raise_irq(irq_no irq){

	gicd_set_pending(irq);	
}
#endif
