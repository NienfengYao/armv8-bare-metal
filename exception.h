/* -*- mode: asm; coding:utf-8 -*- */
/************************************************************************/
/*  OS kernel sample                                                    */
/*  Copyright 2014 Takeharu KATO                                        */
/*                                                                      */
/************************************************************************/

#if !defined(_EXCEPTION_H)
#define _EXCEPTION_H 

/* Vector Table
 * see 5.1.1 Setting up a vector table in
 * Application Note Bare-metal Boot Code for ARMv8-A Processors Version 1.0
 */

/*
 * AArch64 exception types
 */
/* Current EL with SP0 */
#define AARCH64_EXC_SYNC_SP0      (0x1)   /* Synchronous */
#define AARCH64_EXC_IRQ_SP0       (0x2)   /* IRQ/vIRQ */
#define AARCH64_EXC_FIQ_SP0       (0x3)   /* FIQ/vFIQ */
#define AARCH64_EXC_SERR_SP0      (0x4)   /* SError/vSError */
/* Current EL with SPx */
#define AARCH64_EXC_SYNC_SPX      (0x11)
#define AARCH64_EXC_IRQ_SPX       (0x12)
#define AARCH64_EXC_FIQ_SPX       (0x13)
#define AARCH64_EXC_SERR_SPX      (0x14)
/* Lower EL using AArch64 */
#define AARCH64_EXC_SYNC_AARCH64  (0x21)
#define AARCH64_EXC_IRQ_AARCH64   (0x22)
#define AARCH64_EXC_FIQ_AARCH64   (0x23)
#define AARCH64_EXC_SERR_AARCH64  (0x24)
/* Lower EL using AArch32 */
#define AARCH64_EXC_SYNC_AARCH32  (0x31)
#define AARCH64_EXC_IRQ_AARCH32   (0x32)
#define AARCH64_EXC_FIQ_AARCH32   (0x33)
#define AARCH64_EXC_SERR_AARCH32  (0x34)

#if defined(ASM_FILE)
#define vector_table_align .align 11    /* Vector tables must be placed at a 2KB-aligned address */
#define vector_entry_align .align 7     /* Each entry is 128B in size*/
#define text_align .align  2            /* Text alignment */
#endif /* ASM_FILE */


/*
 * exception_frame offset definitions
 */
#define EXC_FRAME_SIZE (288)	/* sizeof(struct _exception_frame) */
#define EXC_EXC_TYPE_OFFSET (0)	/* __asm_offsetof(struct _exception_frame, exc_type) */
#define EXC_EXC_ESR_OFFSET (8)	/* __asm_offsetof(struct _exception_frame, exc_esr) */
#define EXC_EXC_SP_OFFSET (16)	/* __asm_offsetof(struct _exception_frame, exc_sp) */
#define EXC_EXC_ELR_OFFSET (24)	/* __asm_offsetof(struct _exception_frame, exc_elr) */
#define EXC_EXC_SPSR_OFFSET (32)/* __asm_offsetof(struct _exception_frame, exc_spsr) */

/*
 * IRQ
 */
#define IRQ_FOUND          (0)
#define IRQ_NOT_FOUND      (1)

#if !defined(ASM_FILE)
#include <stdint.h>
typedef struct _exception_frame{
	uint64_t exc_type;
	uint64_t exc_esr;
	uint64_t exc_sp;
	uint64_t exc_elr;
	uint64_t exc_spsr;
	uint64_t x0;
	uint64_t x1;
	uint64_t x2;
	uint64_t x3;
	uint64_t x4;
	uint64_t x5;
	uint64_t x6;
	uint64_t x7;
	uint64_t x8;
	uint64_t x9;
	uint64_t x10;
	uint64_t x11;
	uint64_t x12;
	uint64_t x13;
	uint64_t x14;
	uint64_t x15;
	uint64_t x16;
	uint64_t x17;
	uint64_t x18;
	uint64_t x19;
	uint64_t x20;
	uint64_t x21;
	uint64_t x22;
	uint64_t x23;
	uint64_t x24;
	uint64_t x25;
	uint64_t x26;
	uint64_t x27;
	uint64_t x28;
	uint64_t x29;
	uint64_t x30;
}exception_frame;

void common_trap_handler(exception_frame *_exc);
#endif /* !ASM_FILE */
#endif /* _EXCEPTION_H */
