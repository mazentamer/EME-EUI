/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Tamer
 *         File:  TIMER.c
 *        Layer:  MCAL
 *       Module:  TIMER
 *      Version:  1.00
 *
 *  Description:  Implementation of Timer Driver
 *
 *********************************************************************************************************************/

#include "MCAL/DIO.h"
#include "TIMER_Config.h"
#include "TIMER_Interface.h"

void Timer_PWM_Config(Timer Timer_Num, Timer_GPIO_Port_One Timer_Port, Timer_GPIO_Pin_One Timer_Pin, TimerAB Timer_Letter, Timer_Edge Edge, Timer_Operation Operation, Timer_PWM_Inversion Inversion, uint16 intervalLoad)
{
    /*Check if GPIO port used is PORTE or PORTF as they have values in the enum that helps in register accessing*/
    if (Timer_Port >= TIMERA_PORT1)
    {
        DIO_init(Timer_Port - 28);
    }
    else
    {
        DIO_init(Timer_Port);
    }

    /*Allow alternate function select on the timer pin based on arguments passed to the function*/
    GPIO_PORT_AFSEL(Timer_Port) |= (1 << Timer_Pin);
    GPIO_PORT_PCTL(Timer_Port) &= ~(0xF << (Timer_Pin*4));
    GPIO_PORT_PCTL(Timer_Port) |= (7 << (Timer_Pin*4)); /*Shifts the desired value to its respective location as each pin is mapped to 4 bits in this register*/
    SET_BIT(GPIO_PORT_DEN(Timer_Port), Timer_Pin);

    /*Checks whether the accessed timers are 16/32-bits or the 32/64 ones and enables their clocks accordingly*/
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

    /*  Disable timer for configuration  */
    CLEAR_BIT(TIMER_CTL(Timer_Num), 0);

    /*  Checks whether timer A or timer B is chosen to access their respective registers*/
    if (Timer_Letter == TIMERA)
    {
        TIMER_CFG(Timer_Num) = INDIVIDUAL_MODE;         /*Enable Individual Mode*/
        SET_BIT(TIMER_TAMR(Timer_Num), TAAMS);          /*Enable PWM Mode*/
        CLEAR_BIT(TIMER_TAMR(Timer_Num), TACMR);        /*Edge-Count Mode*/
        TIMER_TAMR(Timer_Num) |= Operation;             /*Choose Operation Mode*/
        TIMER_CTL(Timer_Num) |= (Inversion << TAPWML);  /*Inversion choice for the output pin*/
        TIMER_TAILR(Timer_Num) = intervalLoad;          /*Load the interval value*/
        SET_BIT(TIMER_CTL(Timer_Num), TAEN);            /*Enable the timer after configuration options*/
    }
    else if (Timer_Letter == TIMERB)                    /*Same operations as TIMER A*/
    {
        TIMER_CFG(Timer_Num) = INDIVIDUAL_MODE;
        SET_BIT(TIMER_TBMR(Timer_Num), TBAMS);
        CLEAR_BIT(TIMER_TBMR(Timer_Num), TBCMR);
        TIMER_TBMR(Timer_Num) |= Operation;
        TIMER_CTL(Timer_Num) |= (Inversion << TBPWML);
        TIMER_TBILR(Timer_Num) = intervalLoad;
        SET_BIT(TIMER_CTL(Timer_Num), TBEN);
    }
    else
    {
        TIMER_CFG(Timer_Num) = CONCATENATED_MODE;
    }
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

/**********************************************************************************************************************
 *  END OF FILE: TIMER.c
 *********************************************************************************************************************/
