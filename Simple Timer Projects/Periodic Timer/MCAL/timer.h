/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: Header file for the Tiva C timer driver
 *
 * Author: Hussein Ahmed
 *
 *******************************************************************************/


#ifndef TIMER_H_
#define TIMER_H_

#include"../Service/std_types.h"

typedef enum
{
    TIMER_0,TIMER_1,TIMER_2,TIMER_3,TIMER_4,TIMER_5
}Timer;

typedef enum
{
    TIMER_32,TIMER_16=4
}Timer_Size;

typedef enum
{
    ONE_SHOT=1,PERIODIC,CAPTURE
}Timer_Mode;


typedef struct
{
    uint32 value;
    uint8 prescaler;
    Timer timer;
    Timer_Size size;
    Timer_Mode mode;

}Timer_Config;


void GPTM_init(Timer_Config* ptr);
void GPTM_setCallBack(void(*a_ptr)(void));
#endif /* TIMER_H_ */
