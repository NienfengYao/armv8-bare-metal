# armv8-bare-metal
*	Purpose
	* It's a bare-metal study in QEMU (-M virt -cpu cortex-a57)

*	GDB (Terminal 1/2 should be in the same directory.)
	```
	Terminal 1:
		qemu-system-aarch64 -machine virt -cpu cortex-a57 -kernel kernel.elf -nographic -S -s
	Terminal 2:
		aarch64-linux-gnu-gdb kernel.elf tui
		target remote :1234
	```

# Questions
*	GDB can't step into main() if miss lable: main_label in boot.S (commit b72c6a8cc7033a4fed89b57f75826d201466179f)
*	It should be some problems in vector_table_el1 in boot.S. If I set "b hang" in other vectors except lower_el_aarch64_irq, the uart outpt will be incorrect (commit b72c6a8cc7033a4fed89b57f75826d201466179f)
*	Debug Timer IRQ (commit b72c6a8cc7033a4fed89b57f75826d201466179f)
	*	We can see CNTV_CTL_EL0[2]:ISTATUS changes, but irq_handler doesn't be called.
	*	And we also didn't see any changes in ISR_EL1. 


# Reference
*	Project
	*   [aarch64-bare-metal-qemu]( https://github.com/freedomtan/aarch64-bare-metal-qemu)
*   QEMU
	*   [QEMU version 2.12.50 User Documentation](https://qemu.weilnetz.de/doc/qemu-doc.html)
*   Makefile
	*   [Makefile範例教學](http://maxubuntu.blogspot.com/2010/02/makefile.html)
	*   [GNU 的連結工具 (ld, nm, objdump, ar)](http://sp1.wikidot.com/gnulinker)
	*   [GCC Command-Line Options](http://tigcc.ticalc.org/doc/comopts.html)
	*   [LD Index](https://sourceware.org/binutils/docs/ld/LD-Index.html#LD-Index)

