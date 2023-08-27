#ifndef DIO_H
#define DIO_H

#include "../Libraries/Std_types.h"
#include "../Libraries/hw_gpio.h"
#include "../Libraries/bitwise_operation.h"

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

void DIO_init(GPIO_PORT port);
void DIO_WritePin(GPIO_PORT port, PORT_BIT bit, GPIO_STATES state);
void DIO_WritePORT(GPIO_PORT port, uint8 byte);
uint8 DIO_ReadPin(GPIO_PORT port, PORT_BIT bit);
uint8 DIO_ReadPort(GPIO_PORT port);
void DIO_SetPinDirection(GPIO_PORT port, PORT_BIT bit, GPIO_IO io);
void DIO_SetPortDirection(GPIO_PORT port, uint8 byte);
void DIO_SetResistorMode(GPIO_PORT port, PORT_BIT bit, DIO_RESISTOR_MODE resistor);
void DIO_EnableInterrupt(GPIO_PORT port, PORT_BIT bit, DIO_INTERRUPT_SENSE sense, DIO_EDGE edge);

#endif
