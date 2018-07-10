/* -*- mode: c; coding:utf-8 -*- */
/**********************************************************************/
/*  OS kernel sample                                                  */
/*  Copyright 2014 Takeharu KATO                                      */
/*                                                                    */
/*  PrimeCell Generic Interrupt Controller (PL390)                    */
/*                                                                    */
/**********************************************************************/
#if !defined(_HAL_GIC_PL390_H)
#define  _HAL_GIC_PL390_H 

#if !defined( _HAL_BOARD_H)
#error "Include hal/board.h before this header file."
#endif  /*   !_HAL_BOARD_H  */

typedef int32_t            irq_no;  /*< IRQ no                       */

#define GIC_GICD_BASE               (GIC_BASE)  /*< GICD MMIO base address */
#define GIC_GICC_BASE               (GIC_BASE + 0x10000) /*< GICC MMIO base address */


#define GIC_GICD_INT_PER_REG        (32)  /* 32 interrupts per reg. in IPRIORITYRn etc. */

/* See 4.3.11 Interrupt Priority Registers, GICD_IPRIORITYRn in
 * PrimeCell Generic Interrupt Controller (PL390)
 */
#define GIC_GICD_IPRIORITY_PER_REG  (4) 
/* See 4.3.11 Interrupt Priority Registers, GICD_IPRIORITYRn in
 * PrimeCell Generic Interrupt Controller (PL390)
 */
#define GIC_GICD_IPRIORITY_SIZE_PER_REG  (8) 
/* See 3.2.10 Target Registers in
 * PrimeCell Generic Interrupt Controller (PL390)
 */
#define GIC_GICD_ITARGETSR_CORE0_TARGET_BMAP (0x01010101)
#define GIC_GICD_ITARGETSR_PER_REG  (4) 
#define GIC_GICD_ITARGETSR_SIZE_PER_REG  (8) 
/** See 3.2.11 Interrupt Configuration Registers in
 * PrimeCell Generic Interrupt Controller (PL390)
 */
#define GIC_GICD_ICFGR_PER_REG  (16) 
/** See 3.2.5 Enable Clear Registers (ICDICERn) in
 * PrimeCell Generic Interrupt Controller (PL390)
 */
#define GIC_GICD_ICENABLER_PER_REG  (32)
/** See 3.2.4 Enable Set Registers in
 * PrimeCell Generic Interrupt Controller (PL390)
 */
#define GIC_GICD_ISENABLER_PER_REG  (32)
/** See 3.2.7 Pending Clear Registers (ICDICPRn)
 * PrimeCell Generic Interrupt Controller (PL390)
 */
#define GIC_GICD_ICPENDR_PER_REG  (32)
/** See 3.2.6 Pending Set Registers (ICDISPRn)
 * PrimeCell Generic Interrupt Controller (PL390)
 */
#define GIC_GICD_ISPENDR_PER_REG  (32)

/** CPU Interface registers
 * See 3.3 CPU Interface register descriptions in 
 * PrimeCell Generic Interrupt Controller (PL390)
 */
#define GIC_GICC_ICR      (GIC_GICC_BASE + 0x000) /*< CPU Interface Control Register */
#define GIC_GICC_PMR      (GIC_GICC_BASE + 0x004) /*< Priority Mask Register  */
#define GIC_GICC_BPR      (GIC_GICC_BASE + 0x008) /*< Binary Point Register   */
#define GIC_GICC_IAR      (GIC_GICC_BASE + 0x00C) /*< Interrupt Acknowledge Register    */
#define GIC_GICC_EOI      (GIC_GICC_BASE + 0x010) /*< End of Interrupt Register   */
#define GIC_GICC_RPR      (GIC_GICC_BASE + 0x014) /*< Running Priority Register */
#define GIC_GICC_HPIR     (GIC_GICC_BASE + 0x018) /*< Highest Pending Interrupt Register*/
#define GIC_GICC_ABPR     (GIC_GICC_BASE + 0x01C) /*< Aliased Binary Point Register */
#define GIC_GICC_IIDR     (GIC_GICC_BASE + 0x0FC) /*< CPU Interface Implementer Identification Register */
#define GIC_GICC_PFIDR8   (GIC_GICC_BASE + 0xFC0) /*< Peripheral Identification Registers (bit 8) */
#define GIC_GICC_PFIDR47  (GIC_GICC_BASE + 0xFD0) /*< Peripheral Identification Registers(4-7 bit) */
#define GIC_GICC_PFIDR03  (GIC_GICC_BASE + 0xFE0) /*< Peripheral Identification Registers(0-3 bit) */
#define GIC_GICC_COMPID   (GIC_GICC_BASE + 0xFF0) /*< PrimeCell Identification Registers */ 
/** CPU Interface Control Register
 * See 4.4.1 CPU Interface Control Register, GICC_CTLR in
 * ARM Generic Interrupt Controller Architecture version 2.0
 */
#define GICC_ICR_ENABLE            (0x1)  /*<  Enable GICC */
#define GICC_ICR_DISABLE           (0x0)  /*<  Disable GICC */

/** Priority Mask Register
 * See 4.4.2 Interrupt Priority Mask Register, GICC_PMR in
 * ARM Generic Interrupt Controller Architecture version 2.0
 */
#define GICC_PMR_PRIO_MIN          (0xff)  /*< The lowest level mask */
#define GICC_PMR_PRIO_HIGH         (0x0)   /*< The highest level mask */

/** Binary Point Register
 * See 4.4.3 Binary Point Register, GICC_BPR in
 * ARM Generic Interrupt Controller Architecture version 2.0
 */
#define GICC_BPR_NO_GROUP          (0x0)  /*< handle all interrupts */

/** Interrupt Acknowledge Register
 * See 4.4.4 Interrupt Acknowledge Register, GICC_IAR in
 * ARM Generic Interrupt Controller Architecture version 2.0
 */
#define GICC_IAR_INTR_IDMASK        (0x3ff)  /*< 0-9 bits means Interrupt ID */
#define GICC_IAR_SPURIOUS_INTR      (0x3ff)  /*< 1023 means spurious interrupt */
#define GICC_IAR_CPUID_MASK        (0x1c00)  /*< CPUID field */

/*
 * GIC Distributor register
 * See 3.2 Distributor register descriptions in 
 * PrimeCell Generic Interrupt Controller (PL390)
 */
#define GIC_GICD_CTLR      (GIC_GICD_BASE + 0x000) /*< Distributor Control Register */
#define GIC_GICD_TYPE	   (GIC_GICD_BASE + 0x004) /*< Interrupt Controller Type Register */
#define GIC_GICD_IIDR	   (GIC_GICD_BASE + 0x008) /*< Distributor Implementer Identification Register */
#define GIC_GICD_IGROUPR(n)   (GIC_GICD_BASE + 0x080 + ( (n) * 4 ) ) /*< Interrupt Group Registers */
#define GIC_GICD_ISENABLER(n)  (GIC_GICD_BASE + 0x100 + ( (n) * 4 ) ) /*< Interrupt Set-Enable Registers */
#define GIC_GICD_ICENABLER(n)  (GIC_GICD_BASE + 0x180 + ( (n) * 4 ) ) /*< Interrupt Clear-Enable Registers */
#define GIC_GICD_ISPENDR(n)    (GIC_GICD_BASE + 0x200 + ( (n) * 4 ) ) /*< Interrupt Set-Pending Registers */
#define GIC_GICD_ICPENDR(n)    (GIC_GICD_BASE + 0x280 + ( (n) * 4 ) ) /*< Interrupt Clear-Pending Registers */
#define GIC_GICD_ISACTIVER(n)  (GIC_GICD_BASE + 0x300 + ( (n) * 4 ) ) /*< Interrupt Set-Active Registers */
#define GIC_GICD_ICACTIVER(n)  (GIC_GICD_BASE + 0x380 + ( (n) * 4 ) ) /*< Interrupt Clear-Active Registers */
#define GIC_GICD_IPRIORITYR(n) (GIC_GICD_BASE + 0x400 + ( (n) * 4 ) ) /*< Interrupt Priority Registers */
#define GIC_GICD_ITARGETSR(n) (GIC_GICD_BASE + 0x800 + ( (n) * 4 ) ) /*< Interrupt Processor Targets Registers */
#define GIC_GICD_ICFGR(n) (GIC_GICD_BASE + 0xc00 + ( (n) * 4 ) ) /*< Interrupt Configuration Registers */
#define GIC_GICD_NSCAR(n) (GIC_GICD_BASE + 0xe00 + ( (n) * 4 ) ) /*< Non-secure Access Control Registers */
#define GIC_GICD_SGIR     (GIC_GICD_BASE + 0xf00 ) /*< Software Generated Interrupt Register */
#define GIC_GICD_CPENDSGIR(n) (GIC_GICD_BASE + 0xf10 + ( (n) * 4 ) ) /*< SGI Clear-Pending Registers */
#define GIC_GICD_SPENDSGIR(n) (GIC_GICD_BASE + 0xf20 + ( (n) * 4 ) ) /*< SGI Set-Pending Registers */

/** Distributor Control Register
 * See 4.3.1 Distributor Control Register, GICD_CTLR in
 * ARM Generic Interrupt Controller Architecture version 2.0
 */
#define GIC_GICD_CTLR_ENABLE       (0x1)  /*<  Enable GICD */
#define GIC_GICD_CTLR_DISABLE      (0x0)  /*<  Disable GICD */

/** Interrupt Configuration Registers
 * See 4.3.13 Interrupt Configuration Registers, GICD_ICFGRn in
 * ARM Generic Interrupt Controller Architecture version 2.0
 */
#define GIC_GICD_ICFGR_LEVEL	  (0x0)  /*< Level interrupt */
#define GIC_GICD_ICFGR_EDGE	  (0x2)  /*< Edge interrupt */


/*
 * Register access macros for GICC
 */
#define REG_GIC_GICC_ICR           ((volatile uint32_t *)(uintptr_t)GIC_GICC_ICR)
#define REG_GIC_GICC_PMR           ((volatile uint32_t *)(uintptr_t)GIC_GICC_PMR)
#define REG_GIC_GICC_BPR           ((volatile uint32_t *)(uintptr_t)GIC_GICC_BPR)
#define REG_GIC_GICC_IAR           ((volatile uint32_t *)(uintptr_t)GIC_GICC_IAR)
#define REG_GIC_GICC_EOI           ((volatile uint32_t *)(uintptr_t)GIC_GICC_EOI)
#define REG_GIC_GICC_RPR           ((volatile uint32_t *)(uintptr_t)GIC_GICC_RPR)
#define REG_GIC_GICC_HPIR          ((volatile uint32_t *)(uintptr_t)GIC_GICC_HPIR)
#define REG_GIC_GICC_ABPR          ((volatile uint32_t *)(uintptr_t)GIC_GICC_ABPR)
#define REG_GIC_GICC_IIDR          ((volatile uint32_t *)(uintptr_t)GIC_GICC_IIDR)
#define REG_GIC_GICC_PFIDR8        ((volatile uint8_t *)GIC_GICC_PFIDR8)
#define REG_GIC_GICC_PFIDR47       ((volatile uint8_t *)GIC_GICC_PFIDR47)
#define REG_GIC_GICC_PFIDR03       ((volatile uint8_t *)GIC_GICC_PFIDR03)
#define REG_GIC_GICC_COMPID        ((volatile uint8_t *)GIC_GICC_COMPID)

/*
 * Register access macros for GICD
 */
#define REG_GIC_GICD_CTLR             ((volatile uint32_t *)(uintptr_t)GIC_GICD_CTLR)
#define REG_GIC_GICD_TYPE             ((volatile uint32_t *)(uintptr_t)GIC_GICD_TYPE)
#define REG_GIC_GICD_IIDR             ((volatile uint32_t *)(uintptr_t)GIC_GICD_IIDR)
#define REG_GIC_GICD_IGROUPR(n)       ((volatile uint32_t *)(uintptr_t)GIC_GICD_IGROUPR(n))
#define REG_GIC_GICD_ISENABLER(n)     ((volatile uint32_t *)(uintptr_t)GIC_GICD_ISENABLER(n))
#define REG_GIC_GICD_ICENABLER(n)     ((volatile uint32_t *)(uintptr_t)GIC_GICD_ICENABLER(n))
#define REG_GIC_GICD_ISPENDR(n)       ((volatile uint32_t *)(uintptr_t)GIC_GICD_ISPENDR(n))
#define REG_GIC_GICD_ICPENDR(n)       ((volatile uint32_t *)(uintptr_t)GIC_GICD_ICPENDR(n))
#define REG_GIC_GICD_ISACTIVER(n)     ((volatile uint32_t *)(uintptr_t)GIC_GICD_ISACTIVER(n))
#define REG_GIC_GICD_ICACTIVER(n)     ((volatile uint32_t *)(uintptr_t)GIC_GICD_ICACTIVER(n))
#define REG_GIC_GICD_IPRIORITYR(n)    ((volatile uint32_t *)(uintptr_t)GIC_GICD_IPRIORITYR(n))
#define REG_GIC_GICD_ITARGETSR(n)     ((volatile uint32_t *)(uintptr_t)GIC_GICD_ITARGETSR(n))
#define REG_GIC_GICD_ICFGR(n)         ((volatile uint32_t *)(uintptr_t)GIC_GICD_ICFGR(n))
#define REG_GIC_GICD_NSCAR(n)         ((volatile uint32_t *)(uintptr_t)GIC_GICD_NSCAR(n))
#define REG_GIC_GICD_SGIR             ((volatile uint32_t *)(uintptr_t)GIC_GICD_SGIR)
#define REG_GIC_GICD_CPENDSGIR(n)     ((volatile uint32_t *)(uintptr_t)GIC_GICD_CPENDSGIR(n))
#define REG_GIC_GICD_SPENDSGIR(n)     ((volatile uint32_t *)(uintptr_t)GIC_GICD_SPENDSGIR(n))

#if 1 //Ryan
//static void gic_pl390_initialize(void);
void gic_pl390_initialize(void);
#else
static int gic_pl390_config_irq(struct _irq_ctrlr *_ctrlr, 
    irq_no _irq, irq_attr _attr, irq_prio _prio);
static void gic_pl390_enable_irq(struct _irq_ctrlr *_ctrlr, irq_no _irq);
static void gic_pl390_disable_irq(struct _irq_ctrlr *_ctrlr, irq_no _irq);
static void gic_pl390_eoi(struct _irq_ctrlr *_ctrlr, irq_no _irq);
static int gic_pl390_initialize(struct _irq_ctrlr *_ctrlr);
static void gic_pl390_finalize(struct _irq_ctrlr *_ctrlr);
#endif 
#endif  /*  _HAL_GIC_PL390_H   */
