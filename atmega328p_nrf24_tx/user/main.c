#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "main.h"
#include "nrf24.h"

FILE uartstdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

int main () {
	uart_init();
	stdout = &uartstdout;

	nrf24_spi_init();

	while(1) {
		_delay_ms(1000);
		printf("SPCR: %02x\r\n", SPCR);
		_delay_ms(1000);
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
