/*
 * ppb.h
 *
 *  Created on: Sep 12, 2018
 *      Author: Luis Alonzo Mendoza
 */

#ifndef PPB_H_
#define PPB_H_

#define PPB                     ((volatile uint32_t *) 0xe000e000)

enum {
  PPB_STCTRL = (0x10 >> 2),
#define   PPB_EN2 (0x108)
#define   PPB_EN2_TIMER5A (1<<1)
#define   PPB_PRI16 (0x440)
#define   PPB_PRI_INTB_M (1<<13)
#define   PPB_PRI_INTB_S (1<<1)

#define   PPB_STCTRL_COUNT   (1<<16)
#define   PPB_STCTRL_CLK_SRC (1<<2)
#define   PPB_STCTRL_INTEN   (1<<1)
#define   PPB_STCTRL_ENABLE  (1<<0)
#define   PPB_EN0  (0x100)
#define   PPB_NVIC_EN0_BIT23 (1<<23)
  PPB_STRELOAD,
  PPB_STCURRENT,
};

#endif /* PPB_H_ */
