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

