#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H

#include "../Libraries/Std_types.h"

uint8 positions[2][16] = {
                          {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F},
                          {0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF}
};

void LCD_WriteData(uint8 data);
void LCD_WriteInstruction(uint8 instruction);


#endif
