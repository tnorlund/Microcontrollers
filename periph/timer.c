// boilerplate for timer control

#include <stdint.h>
#include <stdbool.h>
#include "ppb.h"
#include "osc.h"
#include "gptm.h"
#include "sysctl.h"

// The two # lines below control whether to compile the SYSTICK code or your
// Timer3A code.  The following line defines a symbol which is used to enable
// only the SYSTICK related code.
#define USING_SYSCTL

//define 32 bit timer
#define USING_32BIT_TIMER

// Uncommenting this line disables the SYSTICK code and enables your Timer3A
// code.
#undef USING_SYSCTL

#ifdef USING_SYSCTL


// Copy these definitions into a "ppb.h" header file.  Create it using the
// same format as sysctl.h and gpio.h.

//#define PPB                     ((volatile uint32_t *) 0xe000e000)
//
//enum {
//  PPB_STCTRL = (0x10 >> 2),
//#define   PPB_STCTRL_COUNT   (1<<16)
//#define   PPB_STCTRL_CLK_SRC (1<<2)
//#define   PPB_STCTRL_INTEN   (1<<1)
//#define   PPB_STCTRL_ENABLE  (1<<0)
//  PPB_STRELOAD,
//  PPB_STCURRENT,
//};
#else

#endif
#undef USING_32BIT_TIMER
#ifdef USING_32BIT_TIMER
#else

#endif
// Frequency of switching between left and right LED display
#define   SWITCHFREQ    200

#define   PRESCALAR 10

// Add the calculation for your reload value here.
#define RELOAD_VALUE    (MAINOSCFREQ/SWITCHFREQ)
//number of bits needed are bits=2^16=65536

// Configure Timer3A as a periodic timer with a period of 1/200th second.
// The names of each register you will need are defined in gptm.h; you do not 
// need to use any registers not named there.  You will need to define the 
// offsets for each bit or field in the registers.
// 
// ALSO: remember to enable the Run Mode Clock Gating for the timer before
// attempting to access any of its registers!
void initTimer( void ) {
#ifdef USING_SYSCTL

  PPB[PPB_STCTRL] = 0;
  PPB[PPB_STRELOAD] = RELOAD_VALUE-1;
  PPB[PPB_STCTRL] = PPB_STCTRL_CLK_SRC | PPB_STCTRL_ENABLE;

#endif


#ifdef USING_32BIT_TIMER
    SYSCTL[SYSCTL_RCGCTIMER] |= SYSCTL_RCGCTIMER_TIMER3;
    SYSCTL[SYSCTL_RCGCTIMER] |= SYSCTL_RCGCTIMER_TIMER3;
    GPTM_TIMER3[GPTM_CTL] &= ~GPTM_CTL_TAEN;
    GPTM_TIMER3[GPTM_CFG] &=~GPTM_CFG_M;
    GPTM_TIMER3[GPTM_CFG] |=GPTM_CFG_32BITTIMER;
    //GPTM_TIMER3[GPTM_CFG] |=GPTM_CFG_16BITTIMERS;
    GPTM_TIMER3[GPTM_TAMR] = (GPTM_TIMER3[GPTM_TAMR]&~GPTM_TAMR_TAMR_M)|GPTM_TAMR_TAMR_PERIODIC;
    GPTM_TIMER3[GPTM_TAILR]= (RELOAD_VALUE)-1;
    //GPTM_TIMER3[GPTM_TAILR]= (RELOAD_VALUE/PRESCALAR)-1;
    //GPTM_TIMER3[GPTM_TAPR]= PRESCALAR-1;

    GPTM_TIMER3[GPTM_ICR] = GPTM_ICR_TATOCINT;

    GPTM_TIMER3[GPTM_CTL] |= GPTM_CTL_TAEN|GPTM_CTL_TASTALL;
#else
    SYSCTL[SYSCTL_RCGCTIMER] |= SYSCTL_RCGCTIMER_TIMER3;
    SYSCTL[SYSCTL_RCGCTIMER] |= SYSCTL_RCGCTIMER_TIMER3;
    GPTM_TIMER3[GPTM_CTL] &= ~GPTM_CTL_TAEN;
    GPTM_TIMER3[GPTM_CFG] &=~GPTM_CFG_M;
    GPTM_TIMER3[GPTM_CFG] |=GPTM_CFG_16BITTIMERS;
    GPTM_TIMER3[GPTM_TAMR] = (GPTM_TIMER3[GPTM_TAMR]&~GPTM_TAMR_TAMR_M)|GPTM_TAMR_TAMR_PERIODIC;
    GPTM_TIMER3[GPTM_TAILR]= (RELOAD_VALUE/PRESCALAR)-1;
    GPTM_TIMER3[GPTM_TAPR]= PRESCALAR-1;
    GPTM_TIMER3[GPTM_ICR] = GPTM_ICR_TATOCINT;
    GPTM_TIMER3[GPTM_CTL] |= GPTM_CTL_TAEN|GPTM_CTL_TASTALL;
#endif
   }

// Wait for Timer3A to reload, then return.  Perform any necessary actions to
// clear the reload condition.  DO NOT turn off the timer!
void waitOnTimer( void ) {
#ifdef USING_SYSCTL

  while( ( PPB[PPB_STCTRL] & PPB_STCTRL_COUNT ) == 0 );

#else
  while((GPTM_TIMER3[GPTM_RIS]& GPTM_RIS_TATORIS)==0);
      GPTM_TIMER3[GPTM_ICR] = GPTM_ICR_TATOCINT;

#endif
}
