#include <avr/io.h>
#include <stdio.h>
#include "main.h"

FILE uartstdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

int main () {
	uart_init();
	stdout = &uartstdout;

	while(1) {
		printf("Test\r\n");
	}
}

void uart_init() {
  UBRR0H = (UBBR>>8);
  UBRR0L = UBBR;
  UCSR0A = 0;                           /* disable doube data rate mode */
  UCSR0B |= _BV(TXEN0);                 /* enable transmitter */
  UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);  /* 8 data bits, 1 stop bit*/
}

int uart_putchar(char c, FILE *stream) {
	if (c == '\n') uart_putchar('\r', stream);
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = c;
	return 0;
}
