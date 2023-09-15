/*
 * push_button.c
 *
 *  Created on: Sep 3, 2023
 *      Author: Mazen
 */
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "../INC/push_button.h"

void GPIOF_Handler(void);

void pushButton_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    *((volatile uint32_t*)(GPIO_PORTF_BASE+GPIO_O_LOCK)) = GPIO_LOCK_KEY;
    GPIOUnlockPin(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);


    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);

    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_0);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);

    GPIOIntRegister(GPIO_PORTF_BASE, GPIOF_Handler);
}

void GPIOF_Handler(void)
{
    if (GPIOIntStatus(GPIO_PORTF_BASE, false) == GPIO_INT_PIN_0)
    {
        GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_0);
        pushButton1_Function();

    }
    else if (GPIOIntStatus(GPIO_PORTF_BASE, false) == GPIO_INT_PIN_4)
    {
        GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
        pushButton2_Function();

    }
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_1|GPIO_INT_PIN_2|GPIO_INT_PIN_3);
}

void pushButton_CallBackFunction(void (*ptr_fun1)(void), void (*ptr_fun2)(void))
{
    pushButton1_Function = ptr_fun1;
    pushButton2_Function = ptr_fun2;
}
