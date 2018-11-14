// boilerplate for timer control

#ifndef _TIMER_H
#define _TIMER_H

//#define RELOAD_VALUE    (MAINOSCFREQ/200-1)

// Configure the timer to roll over at a 200Hz frequency.
void initTimer( void );

// Wait for the timer to roll over, then return.
void waitOnTimer( void );

#endif // _TIMER_H
