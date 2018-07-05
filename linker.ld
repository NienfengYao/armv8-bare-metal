ENTRY(_start)

STACKTOP = 0x41000000;

SECTIONS
{
	/* Starts at LOADER_ADDR. */
	. = 0x40000000;
	__start = .;
	__text_start = .;
	.text :
	{
	KEEP(*(.text.boot))
	*(.text)
	}
	. = ALIGN(4096); /* align to page size */
	__text_end = .;

	__data_start = .;
	.data :
	{
	*(.data)
	}
	. = ALIGN(4096); /* align to page size */
	__data_end = .;

	__bss_start = .;
	.bss :
	{
	bss = .;
	*(.bss)
	}
	. = ALIGN(4096); /* align to page size */
	__bss_end = .;
	__end = .;

	. = STACKTOP ; /* stack memory */
	stack_top = .;
}
__bss_size = (__bss_end - __bss_start)>>3;
