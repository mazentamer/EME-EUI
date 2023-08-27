/*
 * SYSTICK.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Mazen
 */

#ifndef MCAL_SYSTICK_H_
#define MCAL_SYSTICK_H_

#include "Libraries/Std_types.h"

//void SYSTICK_init(uint32 value);
void SYSTICK_delayMS(uint32 ms);
void SYSTICK_delaySEC(void);

#endif /* MCAL_SYSTICK_H_ */
