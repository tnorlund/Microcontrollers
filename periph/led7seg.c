/*
 * led7seg.c
 *
 *  Created on: July 29, 2018
 *      Author: khughes
 *      Lab on: September 5, 2018
 *    Partners: Tyler Norlund & Luis Mendoza
 */

#include <stdint.h>
#include <stdbool.h>

// SYSCTL and GPIO definitions.
#include "sysctl.h"
#include "gpio.h"

// Table containing data to display characters on LED.  Assumes segment A is
// MSB, segment N is LSB.  "0b" prefix used to define value in binary
static uint8_t displayData[] = {
0b11111100,
0b00001100,
0b11011011,
0b11110011,
0b01100111,
0b10110111,
0b10111111,
0b11100000,
0b11111111,
0b11110111,
0b11101111
};

uint8_t getDisplayDataSize( void ) {
  // Return the number of items in the displayData array.  Remember, this
  // must be calculated, not hard-coded.



    uint8_t length = sizeof(displayData);
    return length;
}
//init7SegLED configures
void init7SegLED( void ) {
  // Enable PORTD and PORTE gate clocks.  The second write is only necessary
  // as a delay so that the clock is stable before writing to the GPIO
  // registers.  If we don't delay, we may get a fault.
    SYSCTL[SYSCTL_RCGCGPIO] |= SYSCTL_RCGCGPIO_PORTD | SYSCTL_RCGCGPIO_PORTE;
    SYSCTL[SYSCTL_RCGCGPIO] |= SYSCTL_RCGCGPIO_PORTD | SYSCTL_RCGCGPIO_PORTE;

  // To use PD7, the commit register must be written.  Before doing this,
  // a special code must be written to the lock register to enable this.
  // See the data sheet page on GPIOLOCK for details.
  GPIO_PORTD[GPIO_LOCK] = 0x4c4f434b;
  GPIO_PORTD[GPIO_CR] = GPIO_ALLPINS;
  GPIO_PORTD[GPIO_LOCK] = 0;

  // Configure output pins on PORTD and PORTE.
  GPIO_PORTD[GPIO_DIR] |= GPIO_ALLPINS;
  GPIO_PORTE[GPIO_DIR] |= (GPIO_PIN_0 | GPIO_PIN_1);

  // Enable pins on both ports.
  GPIO_PORTD[GPIO_DEN] |= GPIO_ALLPINS;
  GPIO_PORTE[GPIO_DEN] |= (GPIO_PIN_0 | GPIO_PIN_1);
}

void displayVal(uint8_t display, uint8_t value) {
  // Activate and deactivate the two transistors to turn on only one display.
  if(display == 1) {
      GPIO_PORTE[GPIO_PIN_0 | GPIO_PIN_1] = (1<<1);}
  else {GPIO_PORTE[GPIO_PIN_0 | GPIO_PIN_1] = (1<<0);}

  // Write data to the active LED display.
  GPIO_PORTD[GPIO_ALLPINS] = displayData[value];
}
