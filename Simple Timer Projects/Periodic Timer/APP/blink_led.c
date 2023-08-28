/*
 * blink_led.c
 *
 *  Created on: Aug 26, 2023
 *      Author: Hussein
 */

#include"../MCAL/gpio.h"
#include"../MCAL/timer.h"
#include"../Service/common_macros.h"
#include"../Service/REG.h"

void TOGGle_LED(void)
{
    TOGGLE_BIT(GPIO_PORTF_DATA_R,PIN1_ID);
    TOGGLE_BIT(GPIO_PORTF_DATA_R,PIN2_ID);
    TOGGLE_BIT(GPIO_PORTF_DATA_R,PIN3_ID);
}

void Blink_LED(void)
{
    GPIO_Init(PORTF_ID);
    GPIO_setupPinDirection(PORTF_ID, PIN1_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(PORTF_ID, PIN2_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(PORTF_ID, PIN3_ID, PIN_OUTPUT);

    GPTM_setCallBack(TOGGle_LED);
    Timer_Config timer0 ={31249,255,TIMER_0,TIMER_16,PERIODIC};
    GPTM_init(&timer0);

}



