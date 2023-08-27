#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"

static void delay(uint32 ms);

void LCD_Init(void)
{
    DIO_init(PORTD);
    DIO_init(PORTB);

    DIO_SetPortDirection(PORTB, 0xFF);
    DIO_SetPortDirection(PORTD, 0x0C);

    delay(100);
    LCD_WriteInstruction(0x38);
    LCD_WriteInstruction(0x0C);
    LCD_WriteInstruction(0x01);
    delay(40);
    LCD_WriteInstruction(0x06);
}

void LCD_WriteString(uint8* str)
{
    uint32 iter = 0;
    while (str[iter] != '\0')
    {
        LCD_WriteChar(str[iter]);
        iter++;
    }
}

void LCD_WriteChar(uint8 character)
{
    LCD_WriteData(character);
}

void LCD_WriteNumber(sint32 num)
{
    uint8 zero_counter = 0;

    if (num < 0)
    {
        LCD_WriteChar('-');
        num = -(num);
    }

    if (num == 0)
    {
        LCD_WriteChar('0');
    }

    uint32 temp = num;
    uint32 newNum = 0;

    while (temp != 0)
    {
        newNum = (newNum * 10) + (temp % 10);
        if (newNum == 0)
        {
            zero_counter++;
        }
        temp /= 10;
    }

    while (newNum != 0)
    {
        LCD_WriteChar(((newNum%10)+'0'));
        newNum /= 10;
    }

    while (zero_counter != 0)
    {
        LCD_WriteChar('0');
        zero_counter--;
    }
}

void LCD_GoTo(uint8 line, uint8 position)
{
    LCD_WriteInstruction(positions[line-1][position-1]);
}

void LCD_WriteFloatNumber(f32 num)
{
    uint8 precision = 4;
    f32 temp = num;
    sint32 int_val = (sint32)temp;

    if ((temp - int_val) == 0)
    {
        LCD_WriteNumber(int_val);
        return;
    }

    if (temp < 0)
    {
        LCD_WriteChar('-');
    }

    LCD_WriteNumber(int_val);
    LCD_WriteChar('.');

    temp -= int_val;

    while (precision != 0)
    {
        temp *= 10;
        if (temp < 0)
        {
            temp *= -1;
        }
        LCD_WriteNumber(((sint32)temp) % 10);
        precision--;
    }
}

void LCD_ClearScreen(void)
{
    LCD_WriteInstruction(0x01);
}

static void delay(uint32 ms)
{
    unsigned long volatile t;
    t = 1600*ms;
    while(t){
        t--;
    }
}

void LCD_WriteData(uint8 data)
{
    DIO_WritePin(PORTD, BIT2, HIGH);

    DIO_WritePORT(PORTB, data);

    DIO_WritePin(PORTD, BIT3, HIGH);
    delay(2);
    DIO_WritePin(PORTD, BIT3, LOW);
    delay(2);

}
void LCD_WriteInstruction(uint8 instruction)
{
    DIO_WritePin(PORTD, BIT2, LOW);

    DIO_WritePORT(PORTB, instruction);

    DIO_WritePin(PORTD, BIT3, HIGH);
    delay(2);
    DIO_WritePin(PORTD, BIT3, LOW);
    delay(2);
}
