

/**
 * main.c
 */
#include "MCAL/SYSTICK.h"
#include "MCAL/DIO.h"
#include "HAL/LCD_Interface.h"
#include "HAL/Keypad_Interface.h"

void Systick_Handler(void);
void GPIOA_Handler(void);

volatile uint32 stopwatch[6] = {};
volatile uint8 start_flag;
volatile uint8 lap_flag;

uint8 key = 0xFF;

volatile uint8 tick_counter;

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

    while (1)
    {
        if (key != 0xFF)
        {
            if (key == '=')
            {
                if (start_flag == 1)
                {
                    NVIC_ST_CURRENT_R = 0x01;
                    CLEAR_BIT(NVIC_ST_CTRL_R, 0);
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
                        LCD_GoTo(1, 9);
                        LCD_WriteString("LAP 2");
                        LCD_GoTo(2, 9);
                        LCD_WriteNumber(stopwatch[3]);
                        LCD_WriteNumber(stopwatch[2]);
                        LCD_WriteChar(':');
                        LCD_WriteNumber(stopwatch[1]);
                        LCD_WriteNumber(stopwatch[0]);
                        LCD_WriteChar('.');
                        LCD_WriteNumber(stopwatch[5]);
                        LCD_WriteNumber(stopwatch[4]);
                        lap_flag = 1;
                    }
                    else
                    {
                        LCD_GoTo(1, 1);
                        LCD_WriteString("LAP 1");
                        LCD_GoTo(2, 1);
                        LCD_WriteNumber(stopwatch[3]);
                        LCD_WriteNumber(stopwatch[2]);
                        LCD_WriteChar(':');
                        LCD_WriteNumber(stopwatch[1]);
                        LCD_WriteNumber(stopwatch[0]);
                        LCD_WriteChar('.');
                        LCD_WriteNumber(stopwatch[5]);
                        LCD_WriteNumber(stopwatch[4]);
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
                    stopwatch[4] = 0;
                    stopwatch[5] = 0;
                }
            }
            key = 0xFF;
        }

        if (lap_flag == 1)
        {
            lap_flag = 1;
            LCD_GoTo(1, 9);
            LCD_WriteString("LAP 2");
            LCD_GoTo(2, 9);
            LCD_WriteNumber(stopwatch[3]);
            LCD_WriteNumber(stopwatch[2]);
            LCD_WriteChar(':');
            LCD_WriteNumber(stopwatch[1]);
            LCD_WriteNumber(stopwatch[0]);
            LCD_WriteChar('.');
            LCD_WriteNumber(stopwatch[5]);
            LCD_WriteNumber(stopwatch[4]);
        }
        else
        {
            LCD_GoTo(1, 1);
            LCD_WriteString("LAP 1");
            LCD_GoTo(2, 1);
            LCD_WriteNumber(stopwatch[3]);
            LCD_WriteNumber(stopwatch[2]);
            LCD_WriteChar(':');
            LCD_WriteNumber(stopwatch[1]);
            LCD_WriteNumber(stopwatch[0]);
            LCD_WriteChar('.');
            LCD_WriteNumber(stopwatch[5]);
            LCD_WriteNumber(stopwatch[4]);
        }
    }
}

void Systick_Handler(void)
{
    start_flag = 1;
    //stopwatch[0]++;
    stopwatch[4]++;
    if (stopwatch[4] % 10 == 0)
    {
        stopwatch[4] = 0;
        stopwatch[5]++;
        if (stopwatch[5] % 10 == 0)
        {
            stopwatch[5] = 0;
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
    }
}

void GPIOA_Handler(void)
{
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R0_PIN, LOW);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R1_PIN, HIGH);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R2_PIN, HIGH);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R3_PIN, HIGH);

    if ((GPIO_PORTA_DATA_R & 0x10) == 0)
    {
        key = 1;
        LCD_WriteNumber(key);
    }
    else if ((GPIO_PORTA_DATA_R & 0x20) == 0)
    {
        key = 2;
        LCD_WriteNumber(key);
    }
    else if ((GPIO_PORTA_DATA_R & 0x40) == 0)
    {
        key = 3;
        LCD_WriteNumber(key);
    }
    else if ((GPIO_PORTA_DATA_R & 0x80) == 0)
    {
        key = '+';
        LCD_WriteChar(key);
    }

    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R0_PIN, HIGH);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R1_PIN, LOW);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R2_PIN, HIGH);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R3_PIN, HIGH);

    if ((GPIO_PORTA_DATA_R & 0x10) == 0)
    {
        key = 4;
        LCD_WriteNumber(key);
    }
    else if ((GPIO_PORTA_DATA_R & 0x20) == 0)
    {
        key = 5;
        LCD_WriteNumber(key);
    }
    else if ((GPIO_PORTA_DATA_R & 0x40) == 0)
    {
        key = 6;
        LCD_WriteNumber(key);
    }
    else if ((GPIO_PORTA_DATA_R & 0x80) == 0)
    {
        key = '-';
        LCD_WriteChar(key);
    }

    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R0_PIN, HIGH);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R1_PIN, HIGH);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R2_PIN, LOW);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R3_PIN, HIGH);

    if ((GPIO_PORTA_DATA_R & 0x10) == 0)
    {
        key = 7;
        LCD_WriteNumber(key);
    }
    else if ((GPIO_PORTA_DATA_R & 0x20) == 0)
    {
        key = 8;
        LCD_WriteNumber(key);
    }
    else if ((GPIO_PORTA_DATA_R & 0x40) == 0)
    {
        key = 9;
        LCD_WriteNumber(key);
    }
    else if ((GPIO_PORTA_DATA_R & 0x80) == 0)
    {
        key = '/';
        LCD_WriteChar(key);
    }

    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R0_PIN, HIGH);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R1_PIN, HIGH);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R2_PIN, HIGH);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R3_PIN, LOW);

    if ((GPIO_PORTA_DATA_R & 0x10) == 0)
    {
        key = 'C';
    }
    else if ((GPIO_PORTA_DATA_R & 0x20) == 0)
    {
        key = 0;
        LCD_WriteChar('0');
    }
    else if ((GPIO_PORTA_DATA_R & 0x40) == 0)
    {
        key = '=';
        LCD_WriteChar(key);
    }
    else if ((GPIO_PORTA_DATA_R & 0x80) == 0)
    {
        key = '*';
        LCD_WriteChar(key);
    }

    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R0_PIN, LOW);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R1_PIN, LOW);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R2_PIN, LOW);
    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R3_PIN, LOW);

    if (GPIO_PORTA_MIS_R & 0x10)
    {
        GPIO_PORTA_ICR_R |= 0x10;
    }
    else if (GPIO_PORTA_MIS_R & 0x20)
    {
        GPIO_PORTA_ICR_R |= 0x20;
    }
    else if (GPIO_PORTA_MIS_R & 0x40)
    {
        GPIO_PORTA_ICR_R |= 0x40;
    }
    else if (GPIO_PORTA_MIS_R & 0x80)
    {
        GPIO_PORTA_ICR_R |= 0x80;
    }
}
