// Updated thread and handler code for use with MP3 player

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

// Peripherals
#include "ssi_DAC.h"
#include "timer2A.h"

// Variables used by thread and handler to communicate.
static volatile bool bufferLow, bufferRefilled;
static volatile uint16_t dataLength, dataAdded;

static uint8_t bufferState;
static bool newBuff;

// The size of one "chunk" of data sent from libmad.
static uint16_t bufsize;

// The additional storage in the buffers to keep from running out of data.
enum {PADDING = 1024};

// The DAC buffers.  Each channel has its own buffer.  Each buffer
// can hold two "chunks" of data.
static uint16_t *rbuffer, *lbuffer;

// These pointers are used to place data into the buffers. They
// contain the address of the next byte to be written, and are
// updated in the main thread.
static uint16_t *lInPtr, *rInPtr;

// These pointers are used to remove data from the buffers. They
// contain the address of the next byte to be sent to the DACs,
// and are updated in the interrupt thread.
static uint16_t *lOutPtr, *rOutPtr;

// Volume control setting.
uint8_t volume = 4;

#define MEASUREMENTS

// Additional code for measuring performance
#ifdef MEASUREMENTS
#include "gpio.h"
#ifndef GPIO_PIN_6
#define GPIO_PIN_6 (1<<6)
#endif
static uint16_t minSpace = 1000;
#endif

// Read from output pointers for number of bytes available.  When there is 
// enough space for a chunk of data, inform main thread.
void writeDACs( void ) {
#ifdef MEASUREMENTS
  GPIO_PORTA[GPIO_PIN_1] = GPIO_PIN_1;  // raise when entering handler
#endif

  // update dataLength with new data
  if ( bufferRefilled ) {
      dataLength += dataAdded;
      bufferRefilled = 0;
  }

  // output data while here
  if ( dataLength > 0 ) {
      if ( dataLength <= bufsize )
          bufferLow = 1;
      // Send one sample to each DAC
      txDataSSI2( 0, *lOutPtr++ / volume );
      txDataSSI2( 1, *rOutPtr++ / volume );
      dataLength -= 1;
      // compare new buffer position
      uint16_t offset = lOutPtr-lbuffer;
      if( offset % bufsize == 0 ) {
        offset /= bufsize;
        switch( bufferState ) {
        // Here we Read from Buff0
        //  wait until Buff1
        case 1:
          if( offset == 1 ) {
            bufferState = 2;
            newBuff = true;
          }
          break;
        // Here we move Buff3 to Buff0
        //  wait until Buff3 is done
        case 2:
          if( offset == 3 ) {
            bufferState = 3;
            lOutPtr = lbuffer;
            rOutPtr = rbuffer;
            newBuff = true;
          }
          break;
        // Here we restart Buff0
        //  load Buff1-Buff4
        //  wait until read Buff1
        case 3:
          if ( offset == 1 ) {
            bufferState = 4;
            newBuff = true;
          }
          break;
        // Here we move Buff4 to Buff0
        //  wait until read Buff4
        //  go back to case 3
        case 4:
          if ( offset == 4 ) {
            bufferState = 3;
            lOutPtr = lbuffer;
            rOutPtr = rbuffer;
            newBuff = true;
          }
          break;
        }
        offset /= bufsize;
      }
  } else
      dataLength = 0; // entire file read

  // Clear the timer's time-out interrupt flag.
  clearTimer2A();

#ifdef MEASUREMENTS
  GPIO_PORTA[GPIO_PIN_1] = 0;           // lower when exiting handler
#endif
}

// Initialize the variables use by the thread and handler.
void initSound( void ) {
  bufferRefilled = false;
  dataLength = dataAdded = 0;

  // Deallocate prior buffers.
  free( lbuffer );
  lbuffer = NULL;
  free( rbuffer );
  rbuffer = NULL;

  // Set so the first interrupt will request data.
  bufferLow = true;

#ifdef MEASUREMENTS
  // enable and initialize three output signals
  GPIO_PORTA[GPIO_DIR] |= GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_1;
  GPIO_PORTA[GPIO_DEN] |= GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_1;
  GPIO_PORTA[GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_1] = 0;
#endif
}

// The thread update code.  This is called when the MP3 decoder has more data
// to be played.  However, it must wait until the handler signals there is
// room in the buffers for it.
void fillBuffers( uint32_t *left, uint32_t *right, uint32_t len ) {
  // On the first call, allocate buffers for DACs based on the length of 
  // the buffers being passed in.  This assumes that the size is constant 
  // for the duration of this particular song.
  if( lbuffer == NULL ) {
    bufsize = len;
    lOutPtr = lInPtr = lbuffer = malloc( (bufsize+PADDING) * sizeof (uint16_t) );
    rOutPtr = rInPtr = rbuffer = malloc( (bufsize+PADDING) * sizeof (uint16_t) );
  }

  // Force everything into registers to speed up the loop below.
  register uint32_t *l = left;
  register uint32_t *r = right;
  register uint16_t *ldest = lInPtr;
  register uint16_t *rdest = rInPtr;
  register uint16_t _len = len;
  register uint16_t *end = lbuffer+bufsize+PADDING;

#ifdef MEASUREMENTS
  // PA7 measures how long we wait on writeDAC()
  GPIO_PORTA[GPIO_PIN_7 | GPIO_PIN_6] = GPIO_PIN_7;
#endif

  // Sleep until there is room in the buffers for new data.
  do {
    asm( " wfi" );
  } while( bufferLow == false );

  // Save number of samples for the interrupt handler.
  dataAdded = _len;

#ifdef MEASUREMENTS
  // PA6 measures how long it takes to copy the chunk into the buffers
  GPIO_PORTA[GPIO_PIN_7 | GPIO_PIN_6] = GPIO_PIN_6;
#endif

  // Convert each 32-bit signed value into 12-bit unsigned values
  // (since DAC is only 12 bits wide).
  while( _len-- ) {
    *ldest++ = ( ( (*l++) ^ 0x80000000 ) >> 20 );
    *rdest++ = ( ( (*r++) ^ 0x80000000 ) >> 20 );
    // If it reaches the end of a buffer, wrap to the start.
    if( ldest == end ) {
      ldest = lbuffer;
      rdest = rbuffer;
    }
  }

#ifdef MEASUREMENTS
  GPIO_PORTA[GPIO_PIN_7 | GPIO_PIN_6] = 0;
  if( dataLength > 0 && dataLength < minSpace) minSpace = dataLength;
#endif

  // Now it's OK to set/clear flags
  bufferRefilled = true;
  bufferLow = false;

  // Update pointers with the final value.
  lInPtr = ldest;
  rInPtr = rdest;
}

// Check whether everything has been sent to the DACs.
bool isSoundFinished( void ) {
  return dataLength == 0;
}

// Future implementation: increase volume
void upVolume( void ) {
}

// Future implementation: decrease volume
void downVolume( void ) {
}
