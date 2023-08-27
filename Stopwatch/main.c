

/**
 * main.c
 */
#include <APP/Stopwatch_Interface.h>
#include "MCAL/SYSTICK.h"
#include "MCAL/DIO.h"
#include "HAL/LCD_Interface.h"
#include "HAL/Keypad_Interface.h"


int main(void)
{
    LCD_Init();
    Keypad_init();

    DIO_init(PORTF);
    DIO_SetPortDirection(PORTF, 0x0E);

    DIO_EnableInterrupt(PORTA, BIT4, EDGE, FALLING_EDGE);
    DIO_EnableInterrupt(PORTA, BIT5, EDGE, FALLING_EDGE);
    DIO_EnableInterrupt(PORTA, BIT6, EDGE, FALLING_EDGE);
    DIO_EnableInterrupt(PORTA, BIT7, EDGE, FALLING_EDGE);

    SYSTICK_setInterruptCallback(StopwatchCount);
    DIO_SetInterruptCallback(Keypad_InterruptButton);

    while (1)
    {
        StopwatchInit();
    }
}

