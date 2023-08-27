/*
 * Keypad.c
 *
 *  Created on: Aug 19, 2023
 *      Author: Mazen
 */

#include <HAL/Keypad_Config.h>
#include <HAL/Keypad_Interface.h>

static void delay(uint32 ms);

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
    //    DIO_SetPinDirection(KEYPAD_ROW_PORT, KEYPAD_R0_PIN, OUTPUT);
    //    DIO_SetPinDirection(KEYPAD_ROW_PORT, KEYPAD_R1_PIN, OUTPUT);
    //    DIO_SetPinDirection(KEYPAD_ROW_PORT, KEYPAD_R2_PIN, OUTPUT);
    //    DIO_SetPinDirection(KEYPAD_ROW_PORT, KEYPAD_R3_PIN, OUTPUT);

    DIO_SetPortDirection(KEYPAD_COL_PORT, 0x00);
    //    DIO_SetPinDirection(KEYPAD_COL_PORT, KEYPAD_C0_PIN, INPUT);
    //    DIO_SetPinDirection(KEYPAD_COL_PORT, KEYPAD_C1_PIN, INPUT);
    //    DIO_SetPinDirection(KEYPAD_COL_PORT, KEYPAD_C2_PIN, INPUT);
    //    DIO_SetPinDirection(KEYPAD_COL_PORT, KEYPAD_C3_PIN, INPUT);

    DIO_SetResistorMode(KEYPAD_COL_PORT, KEYPAD_C0_PIN, PULL_UP);
    DIO_SetResistorMode(KEYPAD_COL_PORT, KEYPAD_C1_PIN, PULL_UP);
    DIO_SetResistorMode(KEYPAD_COL_PORT, KEYPAD_C2_PIN, PULL_UP);
    DIO_SetResistorMode(KEYPAD_COL_PORT, KEYPAD_C3_PIN, PULL_UP);

    //    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R0_PIN, HIGH);
    //    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R1_PIN, HIGH);
    //    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R2_PIN, HIGH);
    //    DIO_WritePin(KEYPAD_ROW_PORT, KEYPAD_R3_PIN, HIGH);
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

static void delay(uint32 ms)
{
    unsigned long volatile t;
    t = 1600*ms;
    while(t){
        t--;
    }
}
