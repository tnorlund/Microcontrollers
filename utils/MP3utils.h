/*
 * MP3utils.h
 *
 *  Created on: Aug 9, 2018
 *      Author: khughes
 */

#ifndef _MP3UTILS_H
#define _MP3UTILS_H

#include <stdint.h>

// FatFs data types definitions.
#include "ff.h"

uint8_t countMP3( void );
bool findMP3( uint8_t index, FIL *fp );

#endif // _MP3UTILS_H
