/******************************************************************************/
/*                                                                            */
/* !Layer           : Hardware Abstraction Layer (HAL)                        */
/*                                                                            */
/* !Module          : LCD                                                     */
/* !Description     : LCD implementation                                      */
/*                                                                            */
/* !File            : LCD.c                                                   */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : Robot Car @EME - EUI                                    */
/*                                                                            */
/* !Target          : TIVA-C TM4C123GH6PM                                     */
/*                                                                            */
/* !Compiler        : Code Composer Studio 8.3.1                              */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Ahmed RAGAB                    !Date : SEP 9, 2023      */
/* !Coded by        : Ahmed RAGAB                    !Date : SEP 9, 2023      */
/*                                                                            */
/* Ver 1.0    SEP 13, 2023     Initial release                                */
/******************************************************************************/

/******************************************************************************/
/******************************* Includes *************************************/
/******************************************************************************/

#include "../../GeneralFunctions/Bit_Math.h"
#include "../../GeneralFunctions/std_types.h"
#include "../../GeneralFunctions/hw_gpio.h"
#include "../../GeneralFunctions/Delay.h"
#include "../../MCAL/GPIO/GPIO.h"

/*! Include the module header file                                            */
#include "LCD.h"

/******************************************************************************/
/******************************** GLOBAL VARIABLES ****************************/
/******************************************************************************/
uint8_t counter;

/******************************************************************************/
/*! \Description : Initialize the LCD Module and GPIO Pins used in LCD        */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void LCD_vidInit(void)
{
    /*SET THE CONFIGRATION FOR THE GPIO PINS THAN WILL BE CONNECTED TO THE LCD*/
    GPIO_vidInitPort(LCD_DATA_PORT_ID);
    GPIO_vidInitPort(LCD_CONTROL_PORT_ID);

    GPIO_vidOutputPin(LCD_DATA_PORT_ID , LCD_D0);
    GPIO_vidOutputPin(LCD_DATA_PORT_ID , LCD_D1);
    GPIO_vidOutputPin(LCD_DATA_PORT_ID , LCD_D2);
    GPIO_vidOutputPin(LCD_DATA_PORT_ID , LCD_D3);

    GPIO_vidOutputPin(LCD_CONTROL_PORT_ID , LCD_EN);
    GPIO_vidOutputPin(LCD_CONTROL_PORT_ID , LCD_RS);


    GPIO_vidWritePin(LCD_DATA_PORT_ID, LCD_D0, 0);
    GPIO_vidWritePin(LCD_DATA_PORT_ID, LCD_D1, 0);
    GPIO_vidWritePin(LCD_DATA_PORT_ID, LCD_D2, 0);
    GPIO_vidWritePin(LCD_DATA_PORT_ID, LCD_D3, 0);

    GPIO_vidWritePin(LCD_CONTROL_PORT_ID, LCD_EN, 0);
    GPIO_vidWritePin(LCD_CONTROL_PORT_ID, LCD_RS, 0);

    delay_ms(40);

    LCD_vidSendNibbleCMD(0x2); /*2 Line, 5*7 matrix in 4-bit mode*/
    LCD_vidSendNibbleCMD(0x8);

    LCD_vidSendNibbleCMD(0x0); /*Display on cursor off*/
    LCD_vidSendNibbleCMD(0xC); /*Increment cursor */

    LCD_vidSendNibbleCMD(0x0);
    LCD_vidSendNibbleCMD(0x6);

    LCD_vidSendNibbleCMD(0x0);/*clear the lcd*/
    LCD_vidSendNibbleCMD(0x1);
}

/******************************************************************************/
/*! \Description :  send nibble in the command mode                           */
/*! \return      None                                                         */
/*! \arguments   uint8_t Copy_u8NibbleCopy                                    */
/******************************************************************************/

void LCD_vidSendNibbleCMD(uint8_t Copy_u8NibbleCopy)
{

    /*clear the RS pin and set the EN pin to enter command mode*/
    GPIO_vidWritePin(LCD_CONTROL_PORT_ID, LCD_RS, 0);
    GPIO_vidWritePin(LCD_CONTROL_PORT_ID, LCD_EN, 1);

    /*send the nibble to the LCD through data pins*/
    INSERT_VALUE(LCD_DATA_PORT_REG,LCD_D0,4,Copy_u8NibbleCopy);

    delay_ms(1);

    GPIO_vidWritePin(LCD_CONTROL_PORT_ID, LCD_EN, 0);

}

/******************************************************************************/
/*! \Description :  send nibble in the data mode                              */
/*! \return      None                                                         */
/*! \arguments   uint8_t Copy_u8NibbleCopy                                    */
/******************************************************************************/
void LCD_vidSendNibbleData(uint8_t Copy_u8NibbleCopy)
{

    /*clear the RS pin and set the EN pin to enter command mode*/

    GPIO_vidWritePin(LCD_CONTROL_PORT_ID, LCD_RS, 1);

    GPIO_vidWritePin(LCD_CONTROL_PORT_ID, LCD_EN, 1);

    /*send the nibble to the LCD through data pins*/
    INSERT_VALUE(LCD_DATA_PORT_REG,LCD_D0,4,Copy_u8NibbleCopy);

    delay_ms(1);

    GPIO_vidWritePin(LCD_CONTROL_PORT_ID, LCD_EN, 0);

}

/******************************************************************************/
/*! \Description :  write a character in the LCD                              */
/*! \return         None                                                      */
/*! \arguments      uint8_t Copy_u8DataCopy                                   */
/******************************************************************************/
void LCD_vidWriteChar (uint8_t Copy_u8DataCopy)
{
    /*store the last 4 bits of the character*/
    uint8_t upper=Copy_u8DataCopy>>4;
    /*send the last 4bits*/
    LCD_vidSendNibbleData(upper);
    /*send the first 4bits*/

    LCD_vidSendNibbleData(Copy_u8DataCopy);
    counter++;

}


/******************************************************************************/
/*! \Description :  write string on the LCD                                   */
/*! \return         None                                                      */
/*! \arguments      uint8_t* Copy_ptr_u8StringCopy                            */
/******************************************************************************/

void LCD_vidWriteString (uint8_t* Copy_ptr_u8StringCopy)
{
    uint8_t i;
    /*loop into string till reach null*/
    for(i=0; Copy_ptr_u8StringCopy[i] != '\0'; i++)
    {
        /*print the each single character individually*/
        LCD_vidWriteChar(Copy_ptr_u8StringCopy[i]);
    }
}

/******************************************************************************/
/*! \Description :  move the lcd cursor to certain position                   */
/*! \return         None                                                      */
/*! \arguments      uint8_t Copy_u8column , uint8_t Copy_u8row                */
/******************************************************************************/
void LCD_vidMoveCursor(uint8_t Copy_u8column,uint8_t Copy_u8row){

    /*initialize a variable to store the position*/
    uint8_t Copy_u8positon ;
    /*check if the column is the first column*/
    if(Copy_u8column==0){
        /*add the row number to the address of the first row in the first column*/
        Copy_u8positon=0x80+Copy_u8row;
        /*check if the column is the second column*/
    }else if(Copy_u8column==1){
        /*add the row number to the address of the first row in the second column*/
        Copy_u8positon=Copy_u8row+0xC0;
    }
    /*send the position of the cursor*/
    LCD_vidSendNibbleCMD(Copy_u8positon>>4);
    LCD_vidSendNibbleCMD(Copy_u8positon);
    delay_ms(5);


}

/******************************************************************************/
/*! \Description :  clear the lcd                                             */
/*! \return         None                                                      */
/*! \arguments      None                                                      */
/******************************************************************************/
void LCD_vidClearScreen(void){
    LCD_vidSendNibbleCMD(0x0);
    LCD_vidSendNibbleCMD(0x1);
    counter=0;
}

/******************************************************************************/
/*! \Description :  write number on  the LCD                                  */
/*! \return         None                                                      */
/*! \arguments      uint16_t Copy_u16num                                      */
/******************************************************************************/
void LCD_vidWriteNumber (uint16_t Copy_u16num ){

    uint8_t arr[5]={0};
    uint8_t Local_u8iterator=5;
    if(Copy_u16num & 0x8000)
    {
        Copy_u16num = ((~Copy_u16num) +1);
        LCD_vidWriteChar('-');
    }
    if(Copy_u16num==0){
        LCD_vidWriteChar('0');
    }else{
        while(Copy_u16num!=0){
            Local_u8iterator--;
            arr[Local_u8iterator]=Copy_u16num%10;
            Copy_u16num=Copy_u16num/10;
        }
        for(;Local_u8iterator<5;Local_u8iterator++){
            LCD_vidWriteChar(arr[Local_u8iterator]+'0');
        }
    }

}
