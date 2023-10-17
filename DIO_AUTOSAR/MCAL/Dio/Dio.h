/*
 * Dio.h
 *
 *  Created on: Oct 14, 2023
 *      Author: Mazen
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

#include "../../Std_Types.h"
#include "../../REG.h"

#define NUM_OF_PINS     8U

#define MAX_MASK        255U

#define PORTA           0
#define PORTB           1U
#define PORTC           2U
#define PORTD           3U
#define PORTE           4U
#define PORTF           5U

#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_OUTPUT      0x01
#define STD_INPUT       0x00

typedef uint8 Dio_ChannelType;
typedef uint8 Dio_PortType;
typedef uint8 Dio_LevelType;
typedef uint32 Dio_PortLevelType;

void Port_Init(uint8 Direction, Dio_ChannelType ChannelId);

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);


#endif /* MCAL_DIO_DIO_H_ */
