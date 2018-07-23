# armv8-bare-metal
*	Purpose
	* It's a bare-metal study in QEMU (-M virt -cpu cortex-a57)
*	How to run
	```
	# export PATH inclueding your cross compile tool
	export PATH=$PATH:/home/ryanyao/work/buildroot-2017.11-rc1/output/host/bin
	make run
	```
*	GDB (Terminal 1/2 should be in the same directory.)
	```
	Terminal 1:
		qemu-system-aarch64 -machine virt -cpu cortex-a57 -kernel kernel.elf -nographic -S -s
	Terminal 2:
		aarch64-linux-gnu-gdb kernel.elf --tui
		target remote :1234
	```
*	Timer IRQ works. It assert Timer_Handler() every 1 sec.
	```
	timer_test
	gic_v3_initialize()
	init_gicd()
	init_gicc()
	CurrentEL = 0x00000000 00000004
	RVBAR_EL1 = 0x00000000 00000000
	VBAR_EL1 = 0x00000000 40000000
	DAIF = 0x00000000 000003C0
	Disable the timer, CNTV_CTL_EL0 = 0x00000000 00000000
	System Frequency: CNTFRQ_EL0 = 0x00000000 03B9ACA0
	Current counter: CNTVCT_EL0 = 0x00000000 0001BA16
	Assert Timer IRQ after 1 sec: CNTV_CVAL_EL0 = 0x00000000 03BB66B6
	Enable the timer, CNTV_CTL_EL0 = 0x00000000 00000001
	Enable IRQ, DAIF = 0x00000000 00000340
	
	Exception Handler! (AARCH64_EXC_IRQ_SPX)
	IRQ found: 0x00000000 0000001B
	timer_handler:
			Disable the timer, CNTV_CTL_EL0 = 0x00000000 00000000
			System Frequency: CNTFRQ_EL0 = 0x00000000 03B9ACA0
			Current counter: CNTVCT_EL0 = 0x00000000 03BD40D5
			Assert Timer IRQ after 0x00000000 00000001 sec(s): CNTV_CVAL_EL0 = 0x00000000 0776ED75
			Enable the timer, CNTV_CTL_EL0 = 0x00000000 00000001
	
	Exception Handler! (AARCH64_EXC_IRQ_SPX)
	IRQ found: 0x00000000 0000001B
	timer_handler:
			Disable the timer, CNTV_CTL_EL0 = 0x00000000 00000000
			System Frequency: CNTFRQ_EL0 = 0x00000000 03B9ACA0
			Current counter: CNTVCT_EL0 = 0x00000000 0778E288
			Assert Timer IRQ after 0x00000000 00000001 sec(s): CNTV_CVAL_EL0 = 0x00000000 0B328F28
			Enable the timer, CNTV_CTL_EL0 = 0x00000000 00000001
	```

# Issues
*	GDB can't step into main() if miss lable: main_label in boot.S (commit b72c6a8cc7033a4fed89b57f75826d201466179f)
*	(Fixed, 2018/07/19) Timer IRQ doesn't work(commit b72c6a8cc7033a4fed89b57f75826d201466179f)
	*	We can see CNTV_CTL_EL0[2]:ISTATUS changes, but irq_handler doesn't be called.
	*	And we also didn't see any changes in ISR_EL1. 
	* 	Solved in commit 2aaa0bff7516e84e01acd10d8de64189839d9d51.
*	(Fixed, 2018/07/05) It should be some problems in vector_table_el1 in boot.S. If I set "b hang" in other vectors except lower_el_aarch64_irq, the uart outpt will be incorrect or system hang (commit b72c6a8cc7033a4fed89b57f75826d201466179f)
	*	Root cause should be the stack memory is overlaid. Now, we set stack_top = 0x41000000 to avoid it. (commit c14d653fca24387b5996285f45f0fef2906cb2c9)


# Reference
*	Project
	*   [aarch64-bare-metal-qemu](https://github.com/freedomtan/aarch64-bare-metal-qemu)
	*   [raspberrypi](https://github.com/eggman/raspberrypi)
	*   [sample-tsk-sw](https://github.com/takeharukato/sample-tsk-sw)
*   QEMU
	*   [QEMU version 2.12.50 User Documentation](https://qemu.weilnetz.de/doc/qemu-doc.html)
*   Makefile
	*   [Makefile範例教學](http://maxubuntu.blogspot.com/2010/02/makefile.html)
	*   [GNU 的連結工具 (ld, nm, objdump, ar)](http://sp1.wikidot.com/gnulinker)
	*   [GCC Command-Line Options](http://tigcc.ticalc.org/doc/comopts.html)
	*   [LD Index](https://sourceware.org/binutils/docs/ld/LD-Index.html#LD-Index)
*	ARM
	*	[Arm® Compiler armasm User Guide](http://www.keil.com/support/man/docs/armclang_asm/armclang_asm_chunk708094578.htm)
	*	Application Note Bare-metal Boot Code for ARMv8-A Processors Version 1.0
	*	ARM® Architecture Reference Manual ARMv8, for ARMv8-A architecture profile Beta
	*	ARM® Cortex®-A57 MPCore™ Processor Revision: r1p0 Technical Reference Manual
	*	ARM® Cortex®-A Series Version: 1.0 Programmer’s Guide for ARMv8-A
	*	ARM® Generic Interrupt Controller Architecture Specification GIC architecture version 3.0 and version 4.0
