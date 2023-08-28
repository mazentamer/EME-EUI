/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Source file for the Tiva C timer driver
 *
 * Author: Hussein Ahmed
 *
 *******************************************************************************/

#include"timer.h"
#include"../Service/REG.h"
#include"../Service/common_macros.h"

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

void GPTM_init(Timer_Config* ptr)
{
    SET_BIT(NVIC_EN0_R,19);                                  /* Enable timer0A interrupt */

    SET_BIT(SYSCTL_RCGCTIMER_R,ptr->timer);                  /* enable clock for the timer*/

    CLEAR_BIT(TIMER0_CTL_R,0);                               /* Disable timer*/

    TIMER0_CFG_R =(TIMER0_CFG_R & 0xF8)|(ptr->size & 0x07);  /* Select the 16-bit timer0 configuration.*/

    CLEAR_BIT(TIMER0_TAMR_R,4);                              /* timer counts down.*/

    TIMER0_TAMR_R =(TIMER0_TAMR_R&0xFC)|(ptr->mode &0x03);   /* select timer0 mode.*/

    TIMER0_TAILR_R = ptr->value;                             /* Set timer0 value.*/

    TIMER0_TAPR_R  = ptr->prescaler;                         /* set timer 0 prescaler value.*/

    SET_BIT(TIMER0_IMR_R,0);                                 /* Enable timer0 interrupt*/

    SET_BIT(TIMER0_CTL_R,0);                                 /* Enable timer0*/
}

/* Description:
 * Function to set the Call Back function address. */
void GPTM_setCallBack(void(*a_ptr)(void))
{
    /* Save the address of the Call back function in a global variable */
    g_callBackPtr = a_ptr;
}

void Timer0_Handler(void)
{
    if(g_callBackPtr != NULL_PTR)
    {
        /* Call the Call Back function in the application after the edge is detected */
        (*g_callBackPtr)();
        SET_BIT(TIMER0_ICR_R,0); // clear interrupt flag
    }

}

