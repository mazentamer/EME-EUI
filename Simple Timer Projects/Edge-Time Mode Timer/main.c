/****************************************************************************               **/
/*                                                                                           */
/* !Component       : main                                                                   */
/* !Description     : Application Entry Point                                                */
/*                                                                                           */
/* !Module          : main                                                                   */
/* !Description     : Main Module implementation                                             */
/*                                                                                           */
/* !File            : main.c                                                                 */
/*                                                                                           */
/* !Coding language : C                                                                      */
/*                                                                                           */
/* !Project         : Input Edge project                                                     */
/*                                                                                           */
/*                                                                                           */
/*                                                                                           */
/*  all rights reserved                                                                      */
/*                                                                                           */
/*********************************************************************************************/
/* MODIFICATION LOG :                                                                        */
/*********************************************************************************************/
/*                                                                                           */
/* !Designed by :                                                     !Date :  Aug 26, 2023  */
/* !Coded by    :                                                     !Date :  Aug 26, 2023  */
/*                                                                                           */
/* Rev 1.0   Aug 26, 2023     Initial release                                                */
/*********************************************************************************************/

/*! Include compiler types header                                                            */

#include "DIO.h"
#include "bitwise_operations.h"
#include "delay.h"
#include "std_types.h"


void InputEdge_INIT(void){
    SYSCTL_RCGCWTIMER_R|=1;
    DIO_Init(PORTB_ID);
    /*Enable Clock*/
    SYSCTL_RCGCGPIO_R|=(1<<5);
    /*unlock the lock*/
    GPIO_PORTF_LOCK_R=0x4C4F434B;
    GPIO_PORTF_CR_R=0x1F;
    /*set directions*/
    GPIO_PORTF_DIR_R=0x0E;
    /*set pull up resistor*/
    GPIO_PORTF_PUR_R=0x11;
    /*Enable pins*/
    GPIO_PORTF_DEN_R=0x1F;

    DIO_configurePin(PORTB_ID,6, INPUT_PIN, DISABLE,ENABLE);
    GPIO_PORTB_PCTL_R &=~0x0F000000;
    GPIO_PORTB_PCTL_R |=0x07000000;
    GPIO_PORTB_AFSEL_R|=(1<<6);


    Clear_Bit( WTIMER0_CTL_R,0);/*Disable Timer0*/
    WTIMER0_CFG_R=4;
    WTIMER0_TAMR_R=0x17;            /*mode capture ,Edge Time */
    Clear_Bit(WTIMER0_TAMR_R,4);   /*count Dir down */
    Set_Bit(WTIMER0_CTL_R,2);
    Clear_Bit(WTIMER0_CTL_R,3); /*falling edge*/
    WTIMER0_TAILR_R=320000000;
    Set_Bit(NVIC_EN2_R,30); /*enable nvic for Wide TimerA0  */
    Set_Bit(WTIMER0_IMR_R,2);   /*enable Wide TimerA0  */
    Set_Bit( WTIMER0_CTL_R,0); /*Enable Timer0*/
}
float32 tick=0;
uint8 IEV_flag =0;
uint32 LastEdge;
uint32 ThisEdge;


void Wide_Timer_0A_Capture_Handler(void)
{
    if(IEV_flag == 0)
    {
        LastEdge=WTIMER0_TAR_R;
        IEV_flag++;
    }
    else if(IEV_flag == 1)
    {
        ThisEdge=WTIMER0_TAR_R;
        tick=(LastEdge-ThisEdge)*0.0000000625;
        IEV_flag =0;
    }

    WTIMER0_ICR_R=2;      /*GPTM Timer A Capture Mode Event Interrupt Clear*/
    { if(tick>=0 && tick <=5){
        /*LED turn on Red*/
        Set_Bit(GPIO_PORTF_DATA_R,1);
        Clear_Bit(GPIO_PORTF_DATA_R,2);
        Clear_Bit(GPIO_PORTF_DATA_R,3);


    }
    else if(tick>5 && tick <=10)
    {   /*LED turn on Blue*/
        Set_Bit(GPIO_PORTF_DATA_R,2);
        Clear_Bit(GPIO_PORTF_DATA_R,1);
        Clear_Bit(GPIO_PORTF_DATA_R,3);

    }
    else if(tick>10 && tick <=15)
    {   /*LED turn on Green*/
        Clear_Bit(GPIO_PORTF_DATA_R,2);
        Clear_Bit(GPIO_PORTF_DATA_R,1);
        Set_Bit(GPIO_PORTF_DATA_R,3);


    }
    else
    {
        Clear_Bit(GPIO_PORTF_DATA_R,2);
        Clear_Bit(GPIO_PORTF_DATA_R,1);
        Clear_Bit(GPIO_PORTF_DATA_R,3);

    }
}
}

int main(void)
{   InputEdge_INIT();
return 0;
}
