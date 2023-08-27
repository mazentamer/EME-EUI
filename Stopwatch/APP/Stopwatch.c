/*
 * Stopwatch.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Mazen
 */
#include <APP/Stopwatch_Interface.h>
#include "../MCAL/SYSTICK.h"
#include "../HAL/LCD_Interface.h"
#include "Stopwatch_Interface.h"
#include "Stopwatch_Private.h"

uint32 stopwatch[6] = {};
uint8 start_flag;
uint8 lap_flag;

extern uint8 key;

void StopwatchInit(void)
{
    if (key != 0xFF)
    {
        if (key == '=')
        {
            if (start_flag == 1)
            {
                SYSTICK_stopCounter();
                start_flag = 0;
            }
            else
            {
                LCD_ClearScreen();
                SYSTICK_delayMS(10);
            }
        }
        else if (key == 'C')
        {
            if (start_flag == 1)
            {
                if (lap_flag == 0)
                {
                    Stopwatch_Lap2();
                    lap_flag = 1;
                }
                else
                {
                    Stopwatch_Lap1();
                    lap_flag = 0;
                }
            }
            else
            {
                LCD_ClearScreen();
                lap_flag = 0;
                stopwatch[0] = 0;
                stopwatch[1] = 0;
                stopwatch[2] = 0;
                stopwatch[3] = 0;
            }
        }
        key = 0xFF;
    }

    if (lap_flag == 1)
    {
        lap_flag = 1;
        Stopwatch_Lap2();
    }
    else
    {
        Stopwatch_Lap1();
    }
}

void StopwatchCount(void)
{
    start_flag = 1;

    stopwatch[0]++;
    if (stopwatch[0] % 10 == 0)
    {
        stopwatch[0] = 0;
        stopwatch[1]++;
        if (stopwatch[1] % 6 == 0)
        {
            stopwatch[1] = 0;
            stopwatch[2]++;
            if (stopwatch[2] % 10 == 0)
            {
                stopwatch[2] = 0;
                stopwatch[3]++;
            }
        }
    }
}

void Stopwatch_Lap1(void)
{
    LCD_GoTo(1, 1);
    LCD_WriteString("LAP 1");
    LCD_GoTo(2, 1);
    LCD_WriteNumber(stopwatch[3]);
    LCD_WriteNumber(stopwatch[2]);
    LCD_WriteChar(':');
    LCD_WriteNumber(stopwatch[1]);
    LCD_WriteNumber(stopwatch[0]);
}

void Stopwatch_Lap2(void)
{
    LCD_GoTo(1, 9);
    LCD_WriteString("LAP 2");
    LCD_GoTo(2, 9);
    LCD_WriteNumber(stopwatch[3]);
    LCD_WriteNumber(stopwatch[2]);
    LCD_WriteChar(':');
    LCD_WriteNumber(stopwatch[1]);
    LCD_WriteNumber(stopwatch[0]);
}

