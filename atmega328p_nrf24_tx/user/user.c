#include <avr/io.h>
#include <util/delay.h>

int main () {
	// PORTD all output
	DDRD = 0xFF;

	// PORTD all high
	PORTD = 0xFF;

	while(1) {
		PORTD = 0b11101111;
		_delay_ms(1000);
		PORTD = PORTD << 1;
		_delay_ms(1000);
		PORTD = PORTD << 1;
		_delay_ms(1000);
	}
}
