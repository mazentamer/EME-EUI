#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include "../Libraries/Std_types.h"
#include "../MCAL/DIO.h"

void LCD_Init(void);
void LCD_WriteString(uint8* str);
void LCD_WriteChar(uint8 character);
void LCD_WriteNumber(sint32 num);
void LCD_GoTo(uint8 line, uint8 position);
void LCD_WriteFloatNumber(f32 num);
void LCD_ClearScreen(void);

#endif
