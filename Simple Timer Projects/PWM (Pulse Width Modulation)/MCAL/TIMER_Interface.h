/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Tamer
 *         File:  TIMER_Interface.h
 *        Layer:  MCAL
 *       Module:  TIMER_Interface
 *      Version:  1.00
 *
 *  Description:  APIs for the utilization of timers for the TIVA
 *
 *********************************************************************************************************************/

#ifndef MCAL_TIMER_INTERFACE_H_
#define MCAL_TIMER_INTERFACE_H_

/**********************************************************************************************************************
 *  LIBRARIES NEEDED
 *********************************************************************************************************************/

#include "hw_TIMER.h"
#include "Libraries/hw_gpio.h"
#include "MCAL/DIO.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
    TIMER0 = 0,
    TIMER1 = 1,
    TIMER2 = 2,
    TIMER3 = 3,
    TIMER4 = 4,
    TIMER5 = 5,
    WTIMER0 = 6,
    WTIMER1 = 7,
    WTIMER2 = 28,
    WTIMER3 = 29,
    WTIMER4 = 30,
    WTIMER5 = 31
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

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/***************************************************************************************************************************
* \Syntax          : void Timer_PWM_Config(Timer Timer_Num, Timer_GPIO_Port_One Timer_Port, Timer_GPIO_Pin_One Timer_Pin, TimerAB Timer_Letter, Timer_Edge Edge, Timer_Operation Operation, Timer_PWM_Inversion Inversion, uint16 intervalLoad);
* \Description     : Initialize the timer and configure it to use the PWM capabilities
*
* \Sync\Async      : Synchronous
* \Re-entrancy      : Non Reentrant
* \Parameters (in) : Timer                  Specifies which timer to be initialized
*                    Timer_GPIO_Port_One    Specifies the port that has the pin concerned with the timer
*                    Timer_GPIO_Pin_One     Specifies the specific pin for the timer
*                    TimerAB                Specifies whether to use Timer A, B, or utilize the concatenated mode
*                    Timer_Edge             Specifies whether to use Edge-count or Edge-time modes
*                    Timer_Operation        Specifies mode of operation (one-shot, periodic, etc..)
*                    Timer_PWM_Inversion    Choose to invert the output behavior of the PWM or not
*                    intervalLoad           Provide a load value for the PWM timer
* \Parameters (out): None
* \Return value:   : void
***************************************************************************************************************************/

void Timer_PWM_Config(Timer Timer_Num, Timer_GPIO_Port_One Timer_Port, Timer_GPIO_Pin_One Timer_Pin, TimerAB Timer_Letter, Timer_Edge Edge, Timer_Operation Operation, Timer_PWM_Inversion Inversion, uint16 intervalLoad);

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/***************************************************************************************************************************
* \Syntax          : void Timer_PWM_setDutyCycle(Timer Timer_Num, TimerAB Timer_Letter, uint16 dutyCycle)
* \Description     : Initialize the timer and configure it to use the PWM capabilities
*
* \Sync\Async      : Synchronous
* \Re-entrancy      : Non Reentrant
* \Parameters (in) : Timer                  Specifies which timer to be initialized
*                    TimerAB                Specifies whether Timer A, B, or concatenated mode is to be used
*                    dutyCycle              Specifies the duty cycle of the PWM
* \Parameters (out): None
* \Return value:   : void
***************************************************************************************************************************/

void Timer_PWM_setDutyCycle(Timer Timer_Num, TimerAB Timer_Letter, uint16 dutyCycle);

#endif /* MCAL_TIMER_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: TIMER_Interface.h
 *********************************************************************************************************************/
