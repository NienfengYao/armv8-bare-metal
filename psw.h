/**********************************************************************/
/*  OS kernel sample                                                  */
/*  Copyright 2014 Takeharu KATO                                      */
/*                                                                    */
/*  Processor Status Word                                             */
/*                                                                    */
/**********************************************************************/
#if !defined(_PSW_H)
#define  _PSW_H 

#include "aarch64.h"


typedef uint64_t psw_t;  /* Processor status word */


/** Allow interrupt to CPU unconditionally
 */
#define psw_enable_interrupt()     do{				\
      __asm__ __volatile__ ("msr daifclr, %0\n\t" : : "i"(AARCH64_DAIF_IRQ)); \
    }while(0)

/** Unconditionally prohibit interrupt to CPU
 */
#define psw_disable_interrupt()     do{				\
	__asm__ __volatile__ ("msr daifset, %0\n\t" : : "i"(AARCH64_DAIF_IRQ)); \
    }while(0)

/** Save the PSW
    @ param [in] psw PSW storage variable
 */
#define __save_psw(psw)  do{				    \
     __asm__ __volatile__ ("mrs %0, daif\n\t":"=r"(psw));   \
    }while(0)

/** Restore PSW
    @ param [in] psw PSW storage variable
 */
#define __restore_psw(psw) do{                          \
       __asm__ __volatile__ ("msr daif, %0\n\t"         \
	   ::"r"(psw));					\
   }while(0)

void psw_disable_and_save_interrupt(psw_t *);
void psw_restore_interrupt(psw_t *);
#endif  /*  _PSW_H   */
