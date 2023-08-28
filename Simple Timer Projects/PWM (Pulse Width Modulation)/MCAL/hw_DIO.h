/*
 * hw_DIO.h
 *
 *  Created on: Aug 28, 2023
 *      Author: Mazen
 */

#ifndef MCAL_HW_DIO_H_
#define MCAL_HW_DIO_H_


#define GPIO_PORT_DATA(port_id)             (*((volatile uint32 *)(0x400043FC + (port_id*0x1000))))
#define GPIO_PORT_LOCK(port_id)             (*((volatile uint32 *)(0x40004520 + (port_id*0x1000))))
#define GPIO_PORT_CR(port_id)               (*((volatile uint32 *)(0x40004524 + (port_id*0x1000))))
#define GPIO_PORT_DIR(port_id)              (*((volatile uint32 *)(0x40004400 + (port_id*0x1000))))
#define GPIO_PORT_PUR(port_id)              (*((volatile uint32 *)(0x40004510 + (port_id*0x1000))))
#define GPIO_PORT_PDR(port_id)              (*((volatile uint32 *)(0x40004514 + (port_id*0x1000))))
#define GPIO_PORT_DEN(port_id)              (*((volatile uint32 *)(0x4000451C + (port_id*0x1000))))
#define GPIO_PORT_AFSEL(port_id)            (*((volatile unsigned long *)(0x40004420 + (port_id*0x1000))))
#define GPIO_PORT_PCTL(port_id)             (*((volatile uint32 *)(0x4000452C + (port_id*0x1000))))
#define GPIO_PORT_Interrupt_IS(port_id)     (*((volatile uint32 *)(0x40004404 + (port_id*0x1000))))
#define GPIO_PORT_Interrupt_IBE(port_id)    (*((volatile uint32 *)(0x40004408 + (port_id*0x1000))))
#define GPIO_PORT_Interrupt_IEV(port_id)    (*((volatile uint32 *)(0x4000440C + (port_id*0x1000))))
#define GPIO_PORT_Interrupt_IM(port_id)     (*((volatile uint32 *)(0x40004410 + (port_id*0x1000))))
#define GPIO_PORT_Interrupt_RIS(port_id)    (*((volatile uint32 *)(0x40004414 + (port_id*0x1000))))
#define GPIO_PORT_Interrupt_MIS(port_id)    (*((volatile uint32 *)(0x40004418 + (port_id*0x1000))))
#define GPIO_PORT_Interrupt_ICR(port_id)    (*((volatile uint32 *)(0x4000441C + (port_id*0x1000))))


#endif /* MCAL_HW_DIO_H_ */
