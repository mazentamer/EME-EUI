/*
 * Keypad_Interface.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Mazen
 */

#ifndef HAL_KEYPAD_INTERFACE_H_
#define HAL_KEYPAD_INTERFACE_H_

#include "Keypad_Config.h"
#include "../MCAL/DIO.h"
#include "../Libraries/Std_types.h"

void Keypad_init(void);
uint8 Keypad_CheckButton(void);
void Keypad_InterruptButton(void);


#endif /* HAL_KEYPAD_INTERFACE_H_ */
