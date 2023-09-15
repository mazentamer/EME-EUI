/******************************************************************************/
/*                                                                            */
/* !Layer           : Hardware Abstraction Layer (HAL)                        */
/*                                                                            */
/* !Module          : Ultra-sonic                                             */
/* !Description     : Ultra-sonic Module Implementation                       */
/*                                                                            */
/* !File            : Ultrasonic.c                                            */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : Robot Car Project @EME - EUI                            */
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
/* !Designed by     : Mazen TAMER                      !Date : SEP 09, 2023   */
/* !Coded by        : Mazen TAMER                      !Date : SEP 09, 2023   */
/*                                                                            */
/* Ver 1.0    SEP 13, 2023     Initial release                                */
/******************************************************************************/

/******************************************************************************/
/******************************* Includes *************************************/
/******************************************************************************/

#include <HAL/Ultrasonic/Ultrasonic.h>

/******************************************************************************/
/***************************** Global Variables *******************************/
/******************************************************************************/

uint8_t Glob_u8Flag = 0;                            /*Flag for knowing which variable to store value of timer into*/
uint8_t Glob_u8DistanceFlag = 0;

uint32_t Glob_u32InitVal;                           /*Variable for holding value of timer when ECHO pin is raised*/
uint32_t Glob_u32FinalVal;                          /*Variable for holding value of timer when ECHO pin is lowered*/
uint32_t Glob_u32Distance = 0;                      /*Variable for holding value of distance calculation in centimeter*/

/******************************************************************************/
/**************************** Internal Functions ******************************/
/******************************************************************************/

void delay(uint32_t us);                            /*Function to create delays in microseconds*/

void Ultrasonic_vidMeasureDistance(void);           /*The CallBack Function of The Timer Interrupt That Calculates The Distance*/

/******************************************************************************/
/************************* Function Implementations ***************************/
/******************************************************************************/

/******************************************************************************/
/*! \Description : Initialize Ultra-sonic Module                              */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/

void Ultrasonic_vidInit(void)
{
    /********************* Configuration for the TRIG PIN **********************/
    GPIO_vidInitPort(ULTRASONIC_PORT);                   /*Initialize TRIG PIN Port*/
    GPIO_vidOutputPin(ULTRASONIC_PORT, TRIG_PIN);            /*Set TRIG PIN To GPIO Output*/

    /***************** Configuration for the Wide Timer 5 (A) ******************/
    GPTM_vidSetCallbackFunction(Ultrasonic_vidMeasureDistance);    /*Set The Timer Interrupt CallBack Function*/
    GPTM_vidInit(wideTimer5, edgeTime, down, timerA, 0, both);    /*Initialize The Timer Used In Measuring The Distance*/
}

/******************************************************************************/
/*! \Description : Initiate Ultra-sonic Distance Reading                      */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/

void Ultrasonic_vidGetDistance(void)
{
    GPIO_vidWritePin(GPIO_PORTD, 0x07, 1);          /*Raise the TRIG PIN (Initiate Ultra-sonic Reading)*/
    delay(10U);                                     /*Wait 10 Microseconds (As Instructed By Ultra-sonic Data Sheet)*/
    GPIO_vidWritePin(GPIO_PORTD, 0x07, 0);          /*Lower the TRIG PIN (Initiate Ultra-sonic Reading)*/

}

/******************************************************************************/
/*! \Description : Function To Calculate Distance (CallBack Function)         */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/

void Ultrasonic_vidMeasureDistance(void)
{
    if (Glob_u8Flag == 0)                           /*If The Flag Is Low, Save Timer Value Into The First Variable*/
    {
        Glob_u32InitVal = GPTM_u32GetCurrentValue(wideTimer5, timerA);
        Glob_u8Flag = 1;
    }
    else                                            /*If The Flag Is High, Save Timer Value Into The Second Variable*/
    {
        Glob_u32FinalVal = GPTM_u32GetCurrentValue(wideTimer5, timerA);;
        Glob_u8Flag = 0;

        Glob_u32Distance = ((Glob_u32InitVal - Glob_u32FinalVal) / 16);
        Glob_u32Distance /= 58;                                             /*Calculation to get distance in centimeter*/

        Glob_u32InitVal = 0;
        Glob_u32FinalVal = 0;
        Glob_u8DistanceFlag = 1;                                            /*Acknowledge got a valid distance value*/
    }
}

void delay(uint32_t us){
    unsigned long volatile t;
    t = 16*us;
    while(t){
        t--;
    }
}
