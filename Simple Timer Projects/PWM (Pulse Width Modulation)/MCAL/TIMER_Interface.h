/*
 * TIMER_Interface.h
 *
 *  Created on: Aug 27, 2023
 *      Author: Mazen
 */

#ifndef MCAL_TIMER_INTERFACE_H_
#define MCAL_TIMER_INTERFACE_H_

#include "hw_TIMER.h"
#include "Libraries/hw_gpio.h"
#include "MCAL/DIO.h"

typedef enum
{
    TIMER0,
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER4,
    TIMER5,
    WTIMER0,
    WTIMER1,
    WTIMER2 = 28,
    WTIMER3,
    WTIMER4,
    WTIMER5
} Timer;

typedef enum
{
    TIMERA_PORT0 = 1,
    TIMERB_PORT0 = 1,
    TIMERA_PORT1 = 33,
    TIMERB_PORT1 = 33,
    TIMERA_PORT2 = 33,
    TIMERB_PORT2 = 1,
    TIMERA_POR = 1,
    TIMERB_PORT3 = 1,
    TIMERA_PORT4 = 2,
    TIMERB_PORT4 = 2,
    TIMERA_PORT5 = 2,
    TIMERB_PORT5 = 2,
    WTIMERA_PORT0 = 2,
    WTIMERB_PORT0 = 2,
    WTIMERA_PORT1 = 2,
    WTIMERB_PORT1 = 2,
    WTIMERA_PORT2 = 3,
    WTIMERB_PORT2 = 3,
    WTIMERA_PORT3 = 3,
    WTIMERB_PORT3 = 3,
    WTIMERA_PORT4 = 3,
    WTIMERB_PORT4 = 3,
    WTIMERA_PORT5 = 3,
    WTIMERB_PORT5 = 3
} Timer_GPIO_Port_One;

typedef enum
{
    TIMER0_PIN0 = 6,
    TIMER0_PIN1 = 7,
    TIMER1_PIN0 = 2,
    TIMER1_PIN1 = 3,
    TIMER2_PIN0 = 4,
    TIMER2_PIN1 = 1,
    TIMER3_PIN0 = 2,
    TIMER3_PIN1 = 3,
    TIMER4_PIN0 = 0,
    TIMER4_PIN1 = 1,
    TIMER5_PIN0 = 2,
    TIMER5_PIN1 = 3,
    WTIMER0_PIN0 = 4,
    WTIMER0_PIN1 = 5,
    WTIMER1_PIN0 = 6,
    WTIMER1_PIN1 = 7,
    WTIMER2_PIN0 = 0,
    WTIMER2_PIN1 = 1,
    WTIMER3_PIN0 = 2,
    WTIMER3_PIN1 = 3,
    WTIMER4_PIN0 = 4,
    WTIMER4_PIN1 = 5,
    WTIMER5_PIN0 = 6,
    WTIMER5_PIN1 = 7,
} Timer_GPIO_Pin_One;

typedef enum
{
    TIMERA,
    TIMERB,
    CONCATENATE
} TimerAB;

typedef enum
{
    EDGE_COUNT,
    EDGE_TIME
} Timer_Edge;

typedef enum
{
    ONE_SHOT = 1,
    PERIODIC,
    CAPTURE
} Timer_Operation;

typedef enum
{
    NOT_INVERTED,
    INVERTED
} Timer_PWM_Inversion;


void Timer_PWM_Config(Timer Timer_Num, Timer_GPIO_Port_One Timer_Port, Timer_GPIO_Pin_One Timer_Pin, TimerAB Timer_Letter, Timer_Edge Edge, Timer_Operation Operation, Timer_PWM_Inversion Inversion, uint16 intervalLoad);
void Timer_PWM_setDutyCycle(Timer Timer_Num, TimerAB Timer_Letter, uint16 dutyCycle);

#endif /* MCAL_TIMER_INTERFACE_H_ */
