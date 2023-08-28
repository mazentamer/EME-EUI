/*
 * TIMER.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Mazen
 */
#include "MCAL/DIO.h"
#include "TIMER_Config.h"
#include "TIMER_Interface.h"

void Timer_PWM_Config(Timer Timer_Num, Timer_GPIO_Port_One Timer_Port, Timer_GPIO_Pin_One Timer_Pin, TimerAB Timer_Letter, Timer_Edge Edge, Timer_Operation Operation, Timer_PWM_Inversion Inversion, uint16 intervalLoad)
{
    if (Timer_Port >= TIMERA_PORT1)
    {
        DIO_init(Timer_Port - 28);
    }
    else
    {
        DIO_init(Timer_Port);
    }

    GPIO_PORT_AFSEL(Timer_Port) |= (1 << Timer_Pin);
    GPIO_PORT_PCTL(Timer_Port) &= ~(0xF << Timer_Pin);
    GPIO_PORT_PCTL(Timer_Port) |= (7 << (Timer_Pin*4));
    SET_BIT(GPIO_PORT_DEN(Timer_Port), Timer_Pin);

    if (Timer_Num >= WTIMER0)
    {
        if (Timer_Num >= WTIMER2)
        {
            SET_BIT(SYSCTL_RCGCWTIMER_R, (Timer_Num - WTIMER2));
        }
        else
        {
            SET_BIT(SYSCTL_RCGCWTIMER_R, (Timer_Num % WTIMER0));
        }
    }
    else
    {
        SET_BIT(SYSCTL_RCGCTIMER_R, Timer_Num);
    }

    CLEAR_BIT(TIMER_CTL(Timer_Num), 0);

    if (Timer_Letter == TIMERA)
    {
        TIMER_CFG(Timer_Num) = INDIVIDUAL_MODE;
        SET_BIT(TIMER_TAMR(Timer_Num), TAAMS);
        CLEAR_BIT(TIMER_TAMR(Timer_Num), TACMR);
        TIMER_TAMR(Timer_Num) |= Operation;
        TIMER_CTL(Timer_Num) |= (Inversion << TAPWML);
        TIMER_TAILR(Timer_Num) = intervalLoad;
    }
    else if (Timer_Letter == TIMERB)
    {
        TIMER_CFG(Timer_Num) = INDIVIDUAL_MODE;
        SET_BIT(TIMER_TBMR(Timer_Num), TBAMS);
        CLEAR_BIT(TIMER_TBMR(Timer_Num), TBCMR);
        TIMER_TBMR(Timer_Num) |= Operation;
        TIMER_CTL(Timer_Num) |= (Inversion << TBPWML);
        TIMER_TBILR(Timer_Num) = intervalLoad;
    }
    else
    {
        TIMER_CFG(Timer_Num) = CONCATENATED_MODE;
    }

    SET_BIT(TIMER_CTL(Timer_Num), 0);
}

void Timer_PWM_setDutyCycle(Timer Timer_Num, TimerAB Timer_Letter, uint16 dutyCycle)
{
    if (Timer_Letter == TIMERA)
    {
        TIMER_TAMATCHR(Timer_Num) = dutyCycle;
    }
    else if (Timer_Letter == TIMERB)
    {
        TIMER_TBMATCHR(Timer_Num) = dutyCycle;
    }
}

