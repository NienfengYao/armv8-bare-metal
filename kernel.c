#include <stdint.h>


/*
*	UART
*/
volatile unsigned int * const UART0DR = (unsigned int *) 0x09000000;

void uart_putc(const char c)
{
	*UART0DR = c; /* Transmit char */
}

void uart_puthex(uint64_t n)
{
	const char *hexdigits = "0123456789ABCDEF";

	uart_putc('0');
	uart_putc('x');
	for (int i = 60; i >= 0; i -= 4){
		uart_putc(hexdigits[(n >> i) & 0xf]);
		if (i == 32)
			uart_putc(' ');
	}
}

void uart_puts(const char *s) {
	while(*s != '\0') { 		/* Loop until end of string */
		*UART0DR = (unsigned char)(*s); /* Transmit char */
		s++;			        /* Next char */
	}
}

 
/*
*	Main
*/
int main() {
	uart_putc('A');
	uart_putc('b');
	uart_putc('\n');
	uart_puthex(0xA);
	uart_putc('\n');
	uart_puthex(sizeof(uint64_t));
	uart_putc('\n');
	uart_puts("Hello world!\n");
}


