/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Tamer
 *         File:  hw_TIMER.h
 *        Layer:  Libraries
 *       Module:  hw_TIMER
 *      Version:  1.00
 *
 *  Description:  TIMER registers with convenient accessing using function-like macros
 *
 *********************************************************************************************************************/

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

/**********************************************************************************************************************
 *  END OF FILE: hw_TIMER.h
 *********************************************************************************************************************/
