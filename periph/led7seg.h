/*
 * led7seg.h
 *
 *  Created on: July 29, 2018
 *      Author: khughes
 *      Lab on: September 5, 2018
 *    Partners: Tyler Norlund & Luis Mendoza
 */

#ifndef _LED7SEG_H
#define _LED7SEG_H

#include <stdint.h>

void init7SegLED( void );
void displayVal( uint8_t display, uint8_t value );
uint8_t getDisplayDataSize( void );

#endif // _LED7SEG_H
