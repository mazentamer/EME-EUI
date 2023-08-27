/*
 * Keypad.c
 *
 *  Created on: Aug 19, 2023
 *      Author: Mazen
 */

#include <HAL/Keypad_Config.h>
#include <HAL/Keypad_Interface.h>

static void delay(uint32 ms);
uint8 key = 0xFF;

uint8 keypad_buttons[4][4] = {
                              {1,2,3,'+'},
                              {4,5,6,'-'},
                              {7,8,9,'/'},
                              {'C',0,'=','*'}
};

void Keypad_init(void)
{
    DIO_init(KEYPAD_ROW_PORT);

    DIO_init(KEYPAD_COL_PORT);

    DIO_SetPortDirection(KEYPAD_ROW_PORT, 0x1E);

    DIO_SetPortDirection(KEYPAD_COL_PORT, 0x00);

    DIO_SetResistorMode(KEYPAD_COL_PORT, KEYPAD_C0_PIN, PULL_UP);
    DIO_SetResistorMode(KEYPAD_COL_PORT, KEYPAD_C1_PIN, PULL_UP);
    DIO_SetResistorMode(KEYPAD_COL_PORT, KEYPAD_C2_PIN, PULL_UP);
    DIO_SetResistorMode(KEYPAD_COL_PORT, KEYPAD_C3_PIN, PULL_UP);

    DIO_WritePin(PORTE, BIT1, LOW);
    DIO_WritePin(PORTE, BIT2, LOW);
    DIO_WritePin(PORTE, BIT3, LOW);
    DIO_WritePin(PORTE, BIT4, LOW);
}

uint8 Keypad_CheckButton(void)
{
    uint8 buttonPressed = 0xFF;
    for (uint8 iter_row = 0; iter_row < NUM_ROWS; iter_row++)
    {
        DIO_WritePin(KEYPAD_ROW_PORT, ((uint8)FIRST_ROW + iter_row), LOW);
        for (uint8 iter_col = 0; iter_col < NUM_COLS; iter_col++)
        {
            if (DIO_ReadPin(KEYPAD_COL_PORT, ((uint8)FIRST_COL + iter_col)) == 0)
            {
                buttonPressed = keypad_buttons[iter_row][iter_col];
                while (DIO_ReadPin(KEYPAD_COL_PORT, ((uint8)FIRST_COL + iter_col)) == 0){};
                delay(50);
            }
        }
        DIO_WritePin(KEYPAD_ROW_PORT, ((uint8)FIRST_ROW + iter_row), HIGH);
    }
    return buttonPressed;
}

void Keypad_InterruptButton(void)
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

static void delay(uint32 ms)
{
    unsigned long volatile t;
    t = 1600*ms;
    while(t){
        t--;
    }
}
