/*
 * SYSTICK.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Mazen
 */
#include "Libraries/Std_types.h"
#include "Libraries/bitwise_operation.h"
#include "Libraries/hw_gpio.h"
#include "SYSTICK.h"

void (*ptr_fun)(void);
void Systick_Handler(void);

void SYSTICK_delayMS(uint32 ms)
{
    NVIC_ST_RELOAD_R = (16000 * ms) - 1;
    NVIC_ST_CURRENT_R = 0x01;
    SET_BIT(NVIC_ST_CTRL_R, 2);
    SET_BIT(NVIC_ST_CTRL_R, 1);
    SET_BIT(NVIC_ST_CTRL_R, 0);
}

void SYSTICK_delaySEC(void)
{
    NVIC_ST_RELOAD_R = 16000000U - 1;
    NVIC_ST_CURRENT_R = 0x01;
    SET_BIT(NVIC_ST_CTRL_R, 2);
    SET_BIT(NVIC_ST_CTRL_R, 1);
    SET_BIT(NVIC_ST_CTRL_R, 0);
}

void SYSTICK_stopCounter(void)
{
    NVIC_ST_CURRENT_R = 0x01;
    CLEAR_BIT(NVIC_ST_CTRL_R, 0);
}

void SYSTICK_setInterruptCallback(void(*cb_function)(void))
{
    ptr_fun = cb_function;
}

void Systick_Handler(void)
{
    (*ptr_fun)();
}
