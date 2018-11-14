/*
 * control.c
 *
 *  Created on: Aug 13, 2018
 *      Author: khughes
 */

#include <stdint.h>
#include <stdbool.h>

#include "control.h"

// The total number of songs on the MicroSD card.
static uint8_t numSongs;
// The next song to play.
static uint8_t song = 0;
// Indicates termination of current song by user.
static bool done = false;
// Indicates whether decoding/playing is playing or paused.
static bool paused = false;
// Indicates if the MP3 player is in song shuffle mode.
static bool shuffle = false;

// Private procedure for selecting the next song in shuffle mode.
static uint8_t getShuffle( uint8_t song ) {
  return song;
}

// Return the number of the song to play.  Initially, just
// return the next sequential song, and wrap back to 0 when all
// songs have been returned.
uint8_t getSong( void ) {
  // Save the song number for the end.
  uint8_t tmp = song;

  // Pick the next song to play.
  if( shuffle == false ) {
    song = ( song + 1 ) % numSongs;
  } else {
    song = getShuffle( song );
  }

  // Return song number.
  return tmp;
}

// Store the total number of songs (needed by getSong()).
void setNumSongs( uint8_t num ) {
  numSongs = num;
}

// Store the total number of songs (needed by getSong()).
uint8_t getNumSongs( void ) {
  return numSongs;
}

// Set next song explicitly.
void setSong( uint8_t v ) {
  song = v;
}

// Indicates whether the current MP3 song should be terminated early.
bool isDone( void ) {
  bool tmp = done;
  done = false;
  return tmp;
}

// Set song to terminate.
void setDone( void ) {
  done = true;
}

// Indicates whether the MP3 player is paused.
bool isPaused( void ) {
  return paused;
}

// Set state of pause.
void setPaused( bool v ) {
  paused = v;
}

// Indicates state of shuffle mode.
bool isShuffle( void ) {
  return shuffle;
}

// Set state of shuffle mode.
void setShuffle( bool v ) {
  shuffle = v;
}
