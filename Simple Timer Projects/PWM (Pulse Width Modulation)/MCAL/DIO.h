/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Tamer
 *         File:  DIO.h
 *        Layer:  MCAL
 *       Module:  GPIO
 *      Version:  1.00
 *
 *  Description:  APIs to be used by the user for using the pins on the TIVA board
 *
 *********************************************************************************************************************/

#ifndef DIO_H
#define DIO_H

/**********************************************************************************************************************
 *  LIBRARIES NEEDED
 *********************************************************************************************************************/

#include "../Libraries/Std_types.h"
#include "../Libraries/hw_gpio.h"
#include "../Libraries/bitwise_operation.h"
#include "hw_DIO.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF
} GPIO_PORT;

typedef enum
{
    LOW,
    HIGH
}GPIO_STATES;

typedef enum
{
    INPUT,
    OUTPUT
}GPIO_IO;

typedef enum
{
    BIT0,
    BIT1,
    BIT2,
    BIT3,
    BIT4,
    BIT5,
    BIT6,
    BIT7
}PORT_BIT;

typedef enum
{
    ANALOG,
    DIGITAL
} DIO_MODE;

typedef enum
{
    PULL_DOWN,
    PULL_UP
} DIO_RESISTOR_MODE;

typedef enum
{
    EDGE,
    LEVEL,
    BOTH_EDGES
} DIO_INTERRUPT_SENSE;

typedef enum
{
    FALLING_EDGE,
    RISING_EDGE
} DIO_EDGE;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/***************************************************************************************************************************
* \Syntax          : void DIO_init(GPIO_PORT port)
* \Description     : Initialize the GPIO Port by enabling their respective clock
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : GPIO_PORT
* \Parameters (out): None
* \Return value:   : void
***************************************************************************************************************************/

void DIO_init(GPIO_PORT port);

/***************************************************************************************************************************
* \Syntax          : void DIO_WritePin(GPIO_PORT port, PORT_BIT bit, GPIO_STATES state)
* \Description     : Writes either a HIGH or LOW to the pin in the data register
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : GPIO_PORT          The port of pin to set its value
*                    PORT_BIT           The pin to set its Value
*                    GPIO_STATES        The Pin value
* \Parameters (out): None
* \Return value:   : void
***************************************************************************************************************************/

void DIO_WritePin(GPIO_PORT port, PORT_BIT bit, GPIO_STATES state);

/***************************************************************************************************************************
* \Syntax          : void DIO_WritePORT(GPIO_PORT port, uint8 byte)
* \Description     : Give a complete value to the data register of a certain port
*
* \Sync\Async      : Synchronous
* \Re-entrancy     : Reentrant
* \Parameters (in) : GPIO_PORT          The port to set its value
*                    uint8              The port value
* \Parameters (out): None
* \Return value:   : void
***************************************************************************************************************************/

void DIO_WritePORT(GPIO_PORT port, uint8 byte);

/***************************************************************************************************************************
* \Syntax          : uint8 DIO_ReadPin(GPIO_PORT port, PORT_BIT bit)
* \Description     : Read the value of a certain pin from the data register
*
* \Sync\Async      : Synchronous
* \Re-entrancy     : Non Reentrant
* \Parameters (in) : GPIO_PORT          The port to set its value
*                    PORT_BIT           The pin to be read
* \Parameters (out): None
* \Return value:   : uint8
***************************************************************************************************************************/

uint8 DIO_ReadPin(GPIO_PORT port, PORT_BIT bit);

/***************************************************************************************************************************
* \Syntax          : uint8 DIO_ReadPort(GPIO_PORT port)
* \Description     : Read the value of a certain port from the data register
*
* \Sync\Async      : Synchronous
* \Re-entrancy     : Non Reentrant
* \Parameters (in) : GPIO_PORT          The port to set its value
* \Parameters (out): None
* \Return value:   : uint8
***************************************************************************************************************************/

uint8 DIO_ReadPort(GPIO_PORT port);

/***************************************************************************************************************************
* \Syntax          : void DIO_SetPinDirection(GPIO_PORT port, PORT_BIT bit, GPIO_IO io)
* \Description     : Sets the direction of a certain pin to be either an INPUT or OUTPUT
*
* \Sync\Async      : Synchronous
* \Re-entrancy     : Non Reentrant
* \Parameters (in) : GPIO_PORT          The port needed to access the DIR register
*                    PORT_BIT           The pin to set it's direction
*                    GPIO_IO            The direction of the pin
* \Parameters (out): None
* \Return value:   : void
***************************************************************************************************************************/

void DIO_SetPinDirection(GPIO_PORT port, PORT_BIT bit, GPIO_IO io);

/***************************************************************************************************************************
* \Syntax          : void DIO_SetPortDirection(GPIO_PORT port, uint8 byte)
* \Description     : Sets the direction of a certain port to be either an INPUT or OUTPUT
*
* \Sync\Async      : Synchronous
* \Re-entrancy     : Non Reentrant
* \Parameters (in) : GPIO_PORT          The port needed to access the DIR register
*                    uint8              The value to be written int the DIR register
* \Parameters (out): None
* \Return value:   : void
***************************************************************************************************************************/

void DIO_SetPortDirection(GPIO_PORT port, uint8 byte);

/***************************************************************************************************************************
* \Syntax          : void DIO_SetResistorMode(GPIO_PORT port, PORT_BIT bit, DIO_RESISTOR_MODE resistor)
* \Description     : Sets whether an input pin to be in a pull-up, pull-down, or open-drain state
*
* \Sync\Async      : Synchronous
* \Re-entrancy     : Non Reentrant
* \Parameters (in) : GPIO_PORT          The port needed to access the respective registers
*                    PORT_BIT           The pin to have the given state
*                    DIO_RESISTOR_MODE  The mode the pin to be set in
* \Parameters (out): None
* \Return value:   : void
***************************************************************************************************************************/

void DIO_SetResistorMode(GPIO_PORT port, PORT_BIT bit, DIO_RESISTOR_MODE resistor);

/***************************************************************************************************************************
* \Syntax          : void DIO_EnableInterrupt(GPIO_PORT port, PORT_BIT bit, DIO_INTERRUPT_SENSE sense, DIO_EDGE edge)
* \Description     : Applies interrupt configurations to the selected pin
*
* \Sync\Async      : Synchronous
* \Re-entrancy     : Non Reentrant
* \Parameters (in) : GPIO_PORT              The port needed to access the respective registers
*                    PORT_BIT               The pin to have the interrupt enabled
*                    DIO_INTERRUPT_SENSE    The interrupt mode the pin to be set in
*                    DIO_EDGE               Determines which behavior sets off the interrupt (falling edge, rising edge)
* \Parameters (out): None
* \Return value:   : void
***************************************************************************************************************************/

void DIO_EnableInterrupt(GPIO_PORT port, PORT_BIT bit, DIO_INTERRUPT_SENSE sense, DIO_EDGE edge);

#endif

/**********************************************************************************************************************
 *  END OF FILE: DIO.h
 *********************************************************************************************************************/
