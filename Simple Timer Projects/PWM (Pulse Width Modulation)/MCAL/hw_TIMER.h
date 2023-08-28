/*
 * hw_TIMER.h
 *
 *  Created on: Aug 28, 2023
 *      Author: Mazen
 */

#ifndef MCAL_HW_TIMER_H_
#define MCAL_HW_TIMER_H_

#define TIMER_CFG(timer_id)         (*(volatile uint32 *)(0x40030000 + (timer_id * 0x1000)))
#define TIMER_TAMR(timer_id)        (*(volatile uint32 *)(0x40030004 + (timer_id * 0x1000)))
#define TIMER_TBMR(timer_id)        (*(volatile uint32 *)(0x40030008 + (timer_id * 0x1000)))
#define TIMER_CTL(timer_id)         (*(volatile uint32 *)(0x4003000C + (timer_id * 0x1000)))
#define TIMER_TAILR(timer_id)       (*(volatile uint32 *)(0x40030028 + (timer_id * 0x1000)))
#define TIMER_TBILR(timer_id)       (*(volatile uint32 *)(0x4003002C + (timer_id * 0x1000)))
#define TIMER_TAMATCHR(timer_id)    (*(volatile uint32 *)(0x40030030 + (timer_id * 0x1000)))
#define TIMER_TBMATCHR(timer_id)    (*(volatile uint32 *)(0x40030034 + (timer_id * 0x1000)))

#endif /* MCAL_HW_TIMER_H_ */
