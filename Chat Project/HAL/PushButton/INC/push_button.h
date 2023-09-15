/*
 * push_button.h
 *
 *  Created on: Sep 3, 2023
 *      Author: Mazen
 */

#ifndef HAL_PUSH_BUTTON_H_
#define HAL_PUSH_BUTTON_H_


void pushButton_init(void);
void pushButton_CallBackFunction(void (*ptr_fun1)(void), void (*ptr_fun2)(void));

void (*pushButton1_Function)(void);
void (*pushButton2_Function)(void);


#endif /* HAL_PUSH_BUTTON_H_ */
