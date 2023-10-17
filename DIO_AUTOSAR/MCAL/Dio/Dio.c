/*
 * Dio.c
 *
 *  Created on: Oct 14, 2023
 *      Author: Mazen
 */

#include "Dio.h"

void Port_Init(uint8 Direction, Dio_ChannelType ChannelId)
{
    uint8 Port = ChannelId / NUM_OF_PINS;
    uint8 Pin = ChannelId % NUM_OF_PINS;

    SYSCTL_RCGCGPIO_R |= (STD_HIGH << Port);

    switch(Port)
    {
    case PORTA:

        if (Direction == STD_OUTPUT)
        {
            GPIO_PORTA_DIR_R |= (STD_HIGH << Pin);
        }
        else
        {
            GPIO_PORTA_DIR_R &= ~(STD_HIGH << Pin);
        }


        break;
    case PORTB:

        if (Direction == STD_OUTPUT)
        {
            GPIO_PORTB_DIR_R |= (STD_HIGH << Pin);
        }
        else
        {
            GPIO_PORTB_DIR_R &= ~(STD_HIGH << Pin);
        }

        break;
    case PORTC:

        GPIO_PORTC_LOCK_R = 0x4C4F434B;
        GPIO_PORTC_CR_R = 0xFF;
        GPIO_PORTC_DEN_R = 0xFF;

        if (Direction == STD_OUTPUT)
        {
            GPIO_PORTC_DIR_R |= (STD_HIGH << Pin);
        }
        else
        {
            GPIO_PORTC_DIR_R &= ~(STD_HIGH << Pin);
        }

        break;
    case PORTD:

        GPIO_PORTD_LOCK_R = 0x4C4F434B;
        GPIO_PORTD_CR_R = 0xFF;
        GPIO_PORTD_DEN_R = 0xFF;

        if (Direction == STD_OUTPUT)
        {
            GPIO_PORTD_DIR_R |= (STD_HIGH << Pin);
        }
        else
        {
            GPIO_PORTD_DIR_R &= ~(STD_HIGH << Pin);
        }

        break;
    case PORTE:

        if (Direction == STD_OUTPUT)
        {
            GPIO_PORTE_DIR_R |= (STD_HIGH << Pin);
        }
        else
        {
            GPIO_PORTE_DIR_R &= ~(STD_HIGH << Pin);
        }

        break;
    case PORTF:

        GPIO_PORTF_LOCK_R = 0x4C4F434B;
        GPIO_PORTF_CR_R = 0xFF;
        GPIO_PORTF_DEN_R = 0xFF;

        if (Direction == STD_OUTPUT)
        {
            GPIO_PORTF_DIR_R |= (STD_HIGH << Pin);
        }
        else
        {
            GPIO_PORTF_DIR_R &= ~(STD_HIGH << Pin);
        }

        break;
    }
}

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    uint8 Port = ChannelId / NUM_OF_PINS;
    uint8 Pin = ChannelId % NUM_OF_PINS;
    uint8 PinRead;
    switch(Port)
    {
    case PORTA:
        PinRead = ((GPIO_PORTA_DATA_BITS_R[STD_HIGH << Pin] >> Pin));
        break;
    case PORTB:
        PinRead = ((GPIO_PORTB_DATA_BITS_R[STD_HIGH << Pin] >> Pin));
        break;
    case PORTC:
        PinRead = ((GPIO_PORTC_DATA_BITS_R[STD_HIGH << Pin] >> Pin));
        break;
    case PORTD:
        PinRead = ((GPIO_PORTD_DATA_BITS_R[STD_HIGH << Pin] >> Pin));
        break;
    case PORTE:
        PinRead = ((GPIO_PORTE_DATA_BITS_R[STD_HIGH << Pin] >> Pin));
        break;
    case PORTF:
        PinRead = ((GPIO_PORTF_DATA_BITS_R[STD_HIGH << Pin] >> Pin));
        break;
    }
    return PinRead;
}

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    uint8 Port = ChannelId / NUM_OF_PINS;
    uint8 Pin = ChannelId % NUM_OF_PINS;

    switch(Port)
    {
    case PORTA:
        GPIO_PORTA_DATA_BITS_R[(Level << Pin)] = (Level << Pin);
        break;
    case PORTB:
        GPIO_PORTB_DATA_BITS_R[(Level << Pin)] = (Level << Pin);
        break;
    case PORTC:
        GPIO_PORTC_DATA_BITS_R[(Level << Pin)] = (Level << Pin);
        break;
    case PORTD:
        GPIO_PORTD_DATA_BITS_R[(Level << Pin)] = (Level << Pin);
        break;
    case PORTE:
        GPIO_PORTE_DATA_BITS_R[(Level << Pin)] = (Level << Pin);
        break;
    case PORTF:
        GPIO_PORTF_DATA_BITS_R[(Level << Pin)] = (Level << Pin);
        break;
    }
}

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
    Dio_PortLevelType PortRead;
    switch(PortId)
    {
    case PORTA:
        PortRead = GPIO_PORTA_DATA_BITS_R[MAX_MASK];
        break;
    case PORTB:
        PortRead = GPIO_PORTB_DATA_BITS_R[MAX_MASK];
        break;
    case PORTC:
        PortRead = GPIO_PORTC_DATA_BITS_R[MAX_MASK];
        break;
    case PORTD:
        PortRead = GPIO_PORTD_DATA_BITS_R[MAX_MASK];
        break;
    case PORTE:
        PortRead = GPIO_PORTE_DATA_BITS_R[MAX_MASK];
        break;
    case PORTF:
        PortRead = GPIO_PORTF_DATA_BITS_R[MAX_MASK];
        break;
    default:
        break;
    }
    return PortRead;
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
    switch(PortId)
    {
    case PORTA:
        GPIO_PORTA_DATA_BITS_R[Level] = Level;
        break;
    case PORTB:
        GPIO_PORTB_DATA_BITS_R[Level] = Level;
        break;
    case PORTC:
        GPIO_PORTC_DATA_BITS_R[Level] = Level;
        break;
    case PORTD:
        GPIO_PORTD_DATA_BITS_R[Level] = Level;
        break;
    case PORTE:
        GPIO_PORTE_DATA_BITS_R[Level] = Level;
        break;
    case PORTF:
        GPIO_PORTF_DATA_BITS_R[Level] = Level;
        break;
    default:
        break;
    }
}




