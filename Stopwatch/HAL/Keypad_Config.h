/*
 * Keypad.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Mazen
 */

#ifndef HAL_KEYPAD_CONFIG_H_
#define HAL_KEYPAD_CONFIG_H_


#include "../MCAL/DIO.h"

#define KEYPAD_ROW_PORT  PORTE
#define KEYPAD_COL_PORT  PORTA

#define KEYPAD_R0_PIN   BIT1
#define KEYPAD_R1_PIN   BIT2
#define KEYPAD_R2_PIN   BIT3
#define KEYPAD_R3_PIN   BIT4

#define KEYPAD_C0_PIN   BIT4
#define KEYPAD_C1_PIN   BIT5
#define KEYPAD_C2_PIN   BIT6
#define KEYPAD_C3_PIN   BIT7

#define FIRST_ROW   KEYPAD_R0_PIN
#define FIRST_COL   KEYPAD_C0_PIN

#define NUM_COLS    4
#define NUM_ROWS    4


#endif /* HAL_KEYPAD_CONFIG_H_ */
