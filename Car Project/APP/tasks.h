/*
 * tasks.h
 *
 *  Created on: Sep 14, 2023
 *      Author: Mazen
 */

#ifndef APP_TASKS_H_
#define APP_TASKS_H_

#include "HAL/Ultrasonic/Ultrasonic.h"
#include "HAL/Motors/Motor.h"
#include "HAL/LDR/LDR.h"
#include "HAL/Temperature/Temperature.h"
#include "HAL/LCD/LCD.h"
#include "HAL/Button/Button.h"

void tasks_modulesInit(void);

void button_scan(void);
void ldr_swing_car(void);
void lcd_display(void);
void avoid_obstacles(void);


#endif /* APP_TASKS_H_ */
