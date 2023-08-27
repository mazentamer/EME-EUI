/*
 * SYSTICK.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Mazen
 */

#ifndef MCAL_SYSTICK_H_
#define MCAL_SYSTICK_H_

#include "Libraries/Std_types.h"

void SYSTICK_delayMS(uint32 ms);
void SYSTICK_delaySEC(void);
void SYSTICK_setInterruptCallback(void(*cb_function)(void));
void SYSTICK_stopCounter(void);

#endif /* MCAL_SYSTICK_H_ */
