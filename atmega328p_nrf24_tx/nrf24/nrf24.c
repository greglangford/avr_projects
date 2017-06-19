#include <avr/io.h>
#include "nrf24.h"

void nrf24_spi_init() {
  SPCR |= _BV(SPE) | _BV(MSTR);

  DDRB |= _BV(PB5) | _BV(PB2) | _BV(PB3);    // Outputs
  DDRB &= ~_BV(PB4);  // Inputs

  // SPI mode 0: Clock Polarity CPOL = 0, Clock Phase CPHA = 0
  SPCR &= ~_BV(CPOL) | ~_BV(CPHA) | ~_BV(SPR0) | ~_BV(SPR1);

  // Clock 2X speed
  SPSR |= _BV(SPI2X);

  // most significant first (MSB)
  SPCR &= ~_BV(DORD);
}
