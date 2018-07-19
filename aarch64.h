/* -*- mode: C; coding:utf-8 -*- */
/**********************************************************************/
/*  OS kernel sample                                                  */
/*  Copyright 2014 Takeharu KATO                                      */
/*                                                                    */
/*  AArch64 definitions                                               */
/*                                                                    */
/**********************************************************************/
#if !defined(_AARCH64_H)
#define  _AARCH64_H 

/*
 * Interrupt flags
 */
#define AARCH64_DAIF_FIQ    (1)     /* FIQ */
#define AARCH64_DAIF_IRQ    (2)     /* IRQ */

#if 0 //RyanYao
/*
 * Exception Level
 */
#define AARCH64_CUREL_MASK ( 0xc )  /*< 2-3 bits        */
#define AARCH64_EL_EL3     ( 0xc )  /*< Secure Monitor  */
#define AARCH64_EL_EL2     ( 0x8 )  /*< Hyper Visor     */
#define AARCH64_EL_EL1     ( 0x4 )  /*< OS              */
#define AARCH64_EL_EL0     ( 0x0 )  /*< Application     */

/* SCR_EL3 
 * see 4.3.42. Secure Configuration Register in 
 * ARM Cortex-A53 MPCore Processor Technical Reference Manual
 */
#define AARCH64_SCR_EL3_NS   (0x1 << 0)    /*< Non-secure bit  */
#define AARCH64_SCR_EL3_IRQ  (0x1 << 1)    /*< Physical IRQ Routing */
#define AARCH64_SCR_EL3_FIQ  (0x1 << 2)    /*< Physical FIQ Routing  */
#define AARCH64_SCR_EL3_EA   (0x1 << 3)    /*< External Abort and SError 
					      interrupt Routing */
#define AARCH64_SCR_EL3_RES  (0x3 << 4)    /*< Reserved */
#define AARCH64_SCR_EL3_SMA  (0x1 << 7)    /*< SMC instruction disable */
#define AARCH64_SCR_EL3_HCE  (0x1 << 8)    /*< Hyp Call enable */
#define AARCH64_SCR_EL3_SIF  (0x1 << 9)    /*< Secure Instruction Fetch */
#define AARCH64_SCR_EL3_RW   (0x1 << 10)   /*< Register width control for lower 
					      exception levels */
#define AARCH64_SCR_EL3_ST   (0x1 << 11)   /*< Enable Secure EL1 access to 
					      CNTPS_TVAL_EL1, CNTS_CTL_EL1, and 
					      CNTPS_CVAL_EL1 registers */
#define AARCH64_SCR_EL3_TWI  (0x1 << 12)   /*< Traps WFI instructions */
#define AARCH64_SCR_EL3_TWE  (0x1 << 13)   /*< Traps WFE instructions */

/* HCR_EL2
 * see 4.3.36 Hypervisor Configuration Register in
 * ARM Cortex-A53 MPCore Processor Technical Reference Manual
 */
#define AARCH64_HCR_EL2_VM    (0x1 << 0)     /*<  Enables second stage of translation  */
#define AARCH64_HCR_EL2_SWIO  (0x1 << 1)     /*<  Set/Way Invalidation Override        */
#define AARCH64_HCR_EL2_PTW   (0x1 << 2)     /*<  Protected Table Walk                 */
#define AARCH64_HCR_EL2_FMO   (0x1 << 3)     /*<  Physical FIQ routing                 */
#define AARCH64_HCR_EL2_IMO   (0x1 << 4)     /*<  Physical IRQ routing                 */
#define AARCH64_HCR_EL2_AMO   (0x1 << 5)     /*<  Asynchronous abort and error interrupt 
						 routing  */
#define AARCH64_HCR_EL2_VF    (0x1 << 6)      /*< Virtual FIQ interrupt */
#define AARCH64_HCR_EL2_VI    (0x1 << 7)      /*< Virtual IRQ interrupt */
#define AARCH64_HCR_EL2_VSE   (0x1 << 8)      /*< Virtual System Error/Asynchronous Abort */
#define AARCH64_HCR_EL2_FB    (0x1 << 9)      /*< Forces broadcast */
#define AARCH64_HCR_EL2_BSU_NE    (0x0 << 10) /*<  Barrier shareability upgrade(No effect) */
#define AARCH64_HCR_EL2_BSU_INNER (0x1 << 10) /*<  Barrier shareability upgrade(Inner)     */
#define AARCH64_HCR_EL2_BSU_OUTER (0x2 << 10) /*<  Barrier shareability upgrade(Outer)     */
#define AARCH64_HCR_EL2_BSU_FULL  (0x3 << 10) /*<  Barrier shareability upgrade(Full)      */
#define AARCH64_HCR_EL2_DC        (0x1 << 12) /*<  Default cacheable */
#define AARCH64_HCR_EL2_WFI       (0x1 << 13) /*<  Traps WFI instruction 
						  if it causes suspension of execution */
#define AARCH64_HCR_EL2_WFE       (0x1 << 14) /*<  Traps WFE instruction 
						  if it causes suspension of execution */
#define AARCH64_HCR_EL2_TID0      (0x1 << 15) /*<  Traps ID group 0 registers */
#define AARCH64_HCR_EL2_TID1      (0x1 << 16) /*<  Traps ID group 1 registers */
#define AARCH64_HCR_EL2_TID2      (0x1 << 17) /*<  Traps ID group 2 registers */
#define AARCH64_HCR_EL2_TID3      (0x1 << 18) /*<  Traps ID group 3 registers */
#define AARCH64_HCR_EL2_TSC       (0x1 << 19) /*<  Traps SMC instruction */
#define AARCH64_HCR_EL2_TIDCP     (0x1 << 20) /*<  Trap Implementation */
#define AARCH64_HCR_EL2_TACR      (0x1 << 21) /*<  Traps Auxiliary Control registers */
#define AARCH64_HCR_EL2_TSW       (0x1 << 22) /*<  Traps data or unified cache maintenance
						  instructions by Set or Way */
#define AARCH64_HCR_EL2_TPC       (0x1 << 23) /*<  Traps data or unified cache maintenance
						  instructions to Point of Coherency */
#define AARCH64_HCR_EL2_TPU       (0x1 << 24) /*<  Traps cache maintenance instructions to
						  Point of Unification (POU). */
#define AARCH64_HCR_EL2_TTLB      (0x1 << 25) /*<  Traps TLB maintenance instructions  */
#define AARCH64_HCR_EL2_TVM       (0x1 << 26) /*<  Trap virtual memory controls  */
#define AARCH64_HCR_EL2_TGE       (0x1 << 27) /*<  Traps general exceptions.  */
#define AARCH64_HCR_EL2_TDZ       (0x1 << 28) /*<  Traps DC ZVA instruction.  */
#define AARCH64_HCR_EL2_HCD       (0x1 << 29) /*<  Reserved  */
#define AARCH64_HCR_EL2_TRVM      (0x1 << 30) /*<  Trap reads of Virtual Memory controls  */
#define AARCH64_HCR_EL2_RW        (0x1 << 31) /*<  Register width control for lower exception levels.  */
#define AARCH64_HCR_EL2_CD        (0x1 << 32) /*<   Disables stage 2 data cache  */
#define AARCH64_HCR_EL2_ID        (0x1 << 33) /*<   Disables stage 2 instruction cache.  */
/* Saved Process Status Register
 * See 4.1.5 Saved Process Status Register in
 * ARM  Cortex-A Series Programmer’s Guide for ARMv8-A
 */
#define AARCH64_SPSR_DAIF_F_BIT   (0x1 << 6)  /*<  FIQ interrupt Process state mask */
#define AARCH64_SPSR_DAIF_I_BIT   (0x1 << 7)  /*<  IRQ interrupt Process state mask */
#define AARCH64_SPSR_DAIF_A_BIT   (0x1 << 8)  /*<  SError interrupt Process state mask */
#define AARCH64_SPSR_DAIF_D_BIT   (0x1 << 9)  /*<  Debug exceptions mask */
#define AARCH64_SPSR_FROM_AARCH64 (0x0 << 4)  /*<  Exception was taken from AArch64  */
#define AARCH64_SPSR_FROM_AARCH32 (0x1 << 4)  /*<  Exception was taken from AArch64  */
#define AARCH64_SPSR_MODE_EL3     (AARCH64_EL_EL3)       /*<  Exception State EL3 */
#define AARCH64_SPSR_MODE_EL2     (AARCH64_EL_EL2)       /*<  Exception State EL2 */
#define AARCH64_SPSR_MODE_EL1     (AARCH64_EL_EL1)       /*<  Exception State EL1 */
#define AARCH64_SPSR_MODE_EL0     (AARCH64_EL_EL0)       /*<  Exception State EL0 */
#define AARCH64_SPSR_SP_SEL_N     (0x1 << 0)
#define AARCH64_SPSR_SP_SEL_0     (0x0 << 0)

/* System Control Register
 * See 4.3.1 The system control register in
 * ARM  Cortex-A Series Programmer’s Guide for ARMv8-A
 */
#define AARCH64_SCTLR_M           (0x1 << 0)  /*< Enable the MMU */
#define AARCH64_SCTLR_A           (0x1 << 1)  /*< Alignment check enable bit */
#define AARCH64_SCTLR_C           (0x1 << 2)  /*< Data cache enable */
#define AARCH64_SCTLR_SA          (0x1 << 3)  /*< Stack Alignment Check Enable */
#define AARCH64_SCTLR_SA0         (0x1 << 4)  /*< Stack Alignment Check Enable for EL0 */
#define AARCH64_SCTLR_CP15BEN     (0x1 << 5)  /*< CP15 barrier enable */
#define AARCH64_SCTLR_ITD         (0x1 << 7)  /*< Instruction Trace Disable */
#define AARCH64_SCTLR_SED         (0x1 << 8)  /*< SETEND Disable */
#define AARCH64_SCTLR_UMA         (0x1 << 9)  /*< User Mask Access */
#define AARCH64_SCTLR_I           (0x1 << 12) /*< Instruction cache enable */
#define AARCH64_SCTLR_DZE         (0x1 << 14) /*< Access to DC ZVA instruction at EL0 */
#define AARCH64_SCTLR_UCT         (0x1 << 15) /*< CTR_EL0 register access from EL1 */
#define AARCH64_SCTLR_nTWI        (0x1 << 16) /*< Not trap WFI */
#define AARCH64_SCTLR_nTWE        (0x1 << 18) /*< Not trap WFE */
#define AARCH64_SCTLR_WXN         (0x1 << 19) /*< Write permission implies eXecute Never */
#define AARCH64_SCTLR_EOE         (0x1 << 24) /*< Endianness of explicit data accesses */
#define AARCH64_SCTLR_EE          (0x1 << 25) /*< Exception endianness */
#define AARCH64_SCTLR_UCI         (0x1 << 26) /*< DC CVAU, DC CIVAC, DC CVAC, and 
						IC IVAU instructions from EL0 */

/* Cache Size ID Register
 * See 4.3.22 Cache Size ID Register in
 * ARM Cortex-A53 MPCore Processor Technical Reference Manual
 */
#define AARCH64_CCSIDR_LINESIZE_BIT (0)  /*< Line Size the log2
					    (number of words in cache line)) - 2 */
#define AARCH64_CCSIDR_ASCTY_SHIFT    (3)  /*< Associativity */
#define AARCH64_CCSIDR_NUMSETS_SHIFT  (13) /*< the number of sets in cache - 1 */
#define AARCH64_CCSIDR_WA           (0x1 << 28)  /*< Indicates support for Write-Allocation */
#define AARCH64_CCSIDR_RA           (0x1 << 29)  /*< Indicates support for Read-Allocation */
#define AARCH64_CCSIDR_WB           (0x1 << 30)  /*< Indicates support for Write-Back */
#define AARCH64_CCSIDR_WT           (0x1 << 31)  /*< Indicates support for Write-Through */

/* Translation Control Register
 * See 4.3.48 Translation Control Register in
 * ARM Cortex-A53 MPCore Processor Technical Reference Manual
 */
#define AARCH64_TCR_EL1_T0SZ_SHIFT   (0)  /*< Size offset of the memory region
					    by TTBR0_EL1 */
#define AARCH64_TCR_EL1_EPD0_SHIFT   (7)  /*< Translation table walk disable for
					    translations using TTBR0_EL1  */
#define AARCH64_TCR_EL1_IRGN0_SHIFT  (8)  /*< Inner cacheability attribute for
					    memory associated with translation 
					    table walks using TTBR0_EL1 */
#define AARCH64_TCR_EL1_ORGN0_SHIFT  (10)  /*< Outer cacheability attribute for 
					     memory associated with translation 
					     table walks using TTBR0_EL1  */
#define AARCH64_TCR_EL1_SH0_SHIFT    (12)  /*< Shareability attribute for
					     memory associated with translation
					     table walks using TTBR0_EL1. */
#define AARCH64_TCR_EL1_TG0_SHIFT    (14)  /*< TTBR0_EL1 granule size */
#define AARCH64_TCR_EL1_T1SZ_SHIFT   (16)  /*< Size offset of the memory 
					     region addressed by TTBR1_EL1  */
#define AARCH64_TCR_EL1_A1_SHIFT     (22)  /*< Selects whether TTBR0_EL1 or
					     TTBR1_EL1 */
#define AARCH64_TCR_EL1_EPD1_SHIFT   (23)  /*< Translation table walk disable for
					     translations using TTBR1_EL1 */
#define AARCH64_TCR_EL1_IRGN1_SHIFT  (24)  /*< Inner cacheability attribute for
					     memory associated with translation
					     table walks using TTBR1_EL1 */
#define AARCH64_TCR_EL1_ORGN1_SHIFT  (26)  /*< Outer cacheability attribute for
					     memory associated with translation 
					     table walks using TTBR1_EL1 */
#define AARCH64_TCR_EL1_SH1_SHIFT    (28)  /*< Shareability attribute for 
					     memory associated with translation 
					     table walks using TTBR1_EL1 */
#define AARCH64_TCR_EL1_TG1_SHIFT    (30)  /*< TTBR1_EL1 granule size */
#define AARCH64_TCR_EL1_IPS_SHIFT    (32)  /*< Intermediate Physical Address Size */
#define AARCH64_TCR_EL1_AS_SHIFT     (36)  /*< ASID size. */
#define AARCH64_TCR_EL1_TBI0_SHIFT   (37)  /*< Top Byte Ignored for TTBR0_EL1 */
#define AARCH64_TCR_EL1_TBI1_SHIFT   (38)  /*< Top Byte Ignored for TTBR1_EL1 */

#define AARCH64_TCR_T0SZ_4G          (0x20)   /*< Size offset of the memory 
						region addressed by TTBR0_EL1.
						The region size is 2^32 bytes */
#define AARCH64_TCR_TG0_4KB          (0x0)   /*< TTBR0_EL1 4KiB granule size */
#define AARCH64_TCR_TG0_64KB         (0x1)   /*< TTBR0_EL1 64KiB granule size */

#define AARCH64_TCR_SH0_NON_SHAREABLE   (0x0)   /*< Non Shareable */
#define AARCH64_TCR_SH0_OUTER_SHAREABLE (0x2)   /*< Outer Shareable */
#define AARCH64_TCR_SH0_INNER_SHAREABLE (0x3)   /*< Inner Shareable */


#define AARCH64_TCR_CACHE_NC            (0x0)   /*< Normal memory, Non-cacheable */
#define AARCH64_TCR_CACHE_WB            (0x1)   /*< Normal memory,
						    Write-Back Write-Allocate
						   Cacheable */
#define AARCH64_TCR_CACHE_WT            (0x2)   /*< Normal memory, 
						   Write-Through Cacheable */
#define AARCH64_TCR_CACHE_WB_NALLC      (0x3)   /*< Normal memory, 
						   Write-Back 
						   no Write-Allocate Cacheable. */

/* Memory Attribute Indirection Register
 * See 4.3.69 Memory Attribute Indirection Register, EL1 in
 * ARM Cortex-A53 MPCore Processor Technical Reference Manual
 */
#define AARCH64_MAIR_ATTR_UPPER_DEVMEM    (0x00)   /*< Device memory  */
#define AARCH64_MAIR_ATTR_UPPER_MEM_OWT   (0x30)  /*< Normal Memory, Outer,
						    Write-through transient, Read/Write  */
#define AARCH64_MAIR_ATTR_UPPER_MEM_ONC   (0x40)  /*< Normal Memory, Outer, Non-Cacheable */
#define AARCH64_MAIR_ATTR_UPPER_MEM_OWB   (0x70)  /*< Normal Memory, Outer, 
						    Write-back transient Read/Write  */
#define AARCH64_MAIR_ATTR_UPPER_MEM_OWTNT (0xb0)  /*< Normal Memory, Outer, 
						    Write-through non-transient,
						    Read/Write  */
#define AARCH64_MAIR_ATTR_UPPER_MEM_OWBNT (0xf0)  /*< Normal Memory, Outer, 
						    Write-back non-transient,
						    Read/Write */
/* Device memory 
 * G/nG --- Gathering or non Gathering 
 * R/nR --- Re-ordering
 * E/nE --- Early Write Acknowledgement 
 * See. 13.1.2 Device memory in ARM Cortex-A Series Programmer’s Guide for ARMv8-A 
 */
#define AARCH64_MAIR_ATTR_LOWER_DEV_NG_NR_NE (0x00)  /*< Device-nGnRnE memory  */
#define AARCH64_MAIR_ATTR_LOWER_DEV_NG_NR_E  (0x04)  /*< Device-nGnRE memory   */
#define AARCH64_MAIR_ATTR_LOWER_DEV_NG_R_E   (0x08)  /*< Device-nGRE memory    */
#define AARCH64_MAIR_ATTR_LOWER_DEV_G_R_E    (0x0b)  /*< Device-GRE memory     */
/* Normal memory Inner */
#define AARCH64_MAIR_ATTR_LOWER_MEM_IWT (0x03)  /*< Normal Memory, 
					       Inner Write-through transient */
#define AARCH64_MAIR_ATTR_LOWER_MEM_INC (0x04)  /*< Normal memory, 
					       Inner Non-Cacheable */
#define AARCH64_MAIR_ATTR_LOWER_MEM_IWBT (0x07)  /*< Normal Memory, 
					      Inner Write-back transient */
#define AARCH64_MAIR_ATTR_LOWER_MEM_IWTNT (0x08)  /*< Normal Memory, 
					      Inner Write-through non-transient (RW = 00) */
#define AARCH64_MAIR_ATTR_LOWER_MEM_IWTNTRW (0x0b)  /*< Normal Memory, 
					      Inner Write-through non-transient */
#define AARCH64_MAIR_ATTR_LOWER_MEM_IWBNT (0x0c)  /*< Normal Memory, 
					      Inner Write-back non-transient  (RW = 00) */
#define AARCH64_MAIR_ATTR_LOWER_MEM_IWBNTRW (0x0f)  /*< Normal Memory, 
					      Inner Write-back non-transient */

#define AARCH64_MAIR_ATTR0_SHIFT     (0)     /*< ATTR0 */
#define AARCH64_MAIR_ATTR1_SHIFT     (8)     /*< ATTR1 */
#define AARCH64_MAIR_ATTR2_SHIFT    (16)     /*< ATTR2 */
#define AARCH64_MAIR_ATTR3_SHIFT    (24)     /*< ATTR3 */
#define AARCH64_MAIR_ATTR4_SHIFT    (32)     /*< ATTR4 */
#define AARCH64_MAIR_ATTR5_SHIFT    (40)     /*< ATTR5 */
#define AARCH64_MAIR_ATTR6_SHIFT    (48)     /*< ATTR6 */
#define AARCH64_MAIR_ATTR7_SHIFT    (56)     /*< ATTR7 */

#if !defined(ASM_FILE)
#include <stdint.h>

static inline uint64_t
aarch64_current_el(void) {
	uint64_t curel;

	__asm__ __volatile__ ("mrs %0, CurrentEL\n\t":"=r"(curel));
	curel &= AARCH64_CUREL_MASK;
	curel >>= 2;
	return curel;
}

/* Generic Timer register operations
 * See D10.6 Generic Timer registers in
 * ARM Architecture Reference Manual ARMv8, for ARMv8-A architecture profile
 */
/** Read physical counter
 */
static inline uint64_t
aarch64_get_physical_counter(void) {
	uint64_t val;

	__asm__ __volatile__("mrs %0, cntpct_el0\n\t" : "=r"(val));

	return val;
}

/** Get the frequency of generic timers(UNIT:Hz)
 */
static inline uint64_t
aarch64_get_generic_timer_freq(void) {
	uint64_t val;

	__asm__ __volatile__("mrs %0, cntfrq_el0\n\t" : "=r"(val));

	return val;
}

static inline void *
hal_get_sp(void) {
	uint64_t sp;

	__asm__ __volatile__("mov %0, sp\n\t" : "=r"(sp));

	return (void *)sp;
}

void aarch64_setup_vector(void);
#endif  /*  !ASM_FILE  */
#endif //RyanYao
#endif  /*  _AARCH64_H   */
