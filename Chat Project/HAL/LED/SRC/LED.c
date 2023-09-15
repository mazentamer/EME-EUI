/*
 * LED.c
 *
 *  Created on: 3 Sep 2023
 *      Author: dell
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

#include "../INC/LED.h"

void LEDvidInit(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

}

void LEDvidON(LED_type_t Copy_LEDid)
{
    if(Copy_LEDid == RED_LED)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
    }
    else if(Copy_LEDid == BLUE_LED)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
    }else if(Copy_LEDid == GREEN_LED)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
    }

}
void LEDvidOFF(LED_type_t Copy_LEDid)
{
    if(Copy_LEDid == RED_LED)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
    }
    else if(Copy_LEDid == BLUE_LED)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
    }else if(Copy_LEDid == GREEN_LED)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
    }

}
void LEDvidAllLedOFF(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);
}
