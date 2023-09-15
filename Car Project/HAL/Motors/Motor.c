/******************************************************************************/
/*                                                                            */
/* !Layer           : Hardware Abstraction Layer (HAL)                        */
/*                                                                            */
/* !Module          : Motors                                                  */
/* !Description     : Motors Module implementation                            */
/*                                                                            */
/* !File            : Motor.c                                                 */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : Autonomous Car @EME-EUI  (CLASS 1)                      */
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
/* !Designed by     : Mahmoud Emara                    !Date : SEP 11, 2023   */
/* !Coded by        : Mahmoud Emara                    !Date : SEP 11, 2023   */
/*                                                                            */
/* Ver 1.0    SEP 13, 2023     Initial release                                */
/******************************************************************************/


/*! Include the module header file                                            */
#include "Motor.h"
//#include "Motor_config.h"

/*! Includes                                                                  */
#include "../../MCAL/PWM/PWM.h"
#include "../../MCAL/GPIO/GPIO.h"



/******************************************************************************/
/*! \Description Initialise the Motors pin used and PWM initialisation        */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void MOTOR_vidInit(void)
{
    PWM_vidInit();

    GPIO_vidInitPort(GPIO_PORTA);
    GPIO_vidOutputPin(GPIO_PORTA, PIN2);
    GPIO_vidOutputPin(GPIO_PORTA, PIN4);
    GPIO_vidOutputPin(GPIO_PORTA, PIN5);
    GPIO_vidOutputPin(GPIO_PORTA, PIN6);
}
/******************************************************************************/
/*! \Description set the pins to move the 2 motors forward                    */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void MOTOR_vidForward(void)
{
    GPIO_vidWritePin(GPIO_PORTA, PIN2, OUTPUT_LOW);
    GPIO_vidWritePin(GPIO_PORTA, PIN4, OUTPUT_LOW);
    GPIO_vidWritePin(GPIO_PORTA, PIN5, OUTPUT_HIGH);
    GPIO_vidWritePin(GPIO_PORTA, PIN6, OUTPUT_HIGH);

    PWM_vidSetDutyCycle(Channel0, 50);
    PWM_vidSetDutyCycle(Channel2, 50);
}
/******************************************************************************/
/*! \Description set the pins to move the 2 motors backward                   */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void MOTOR_vidBackward(void)
{
    GPIO_vidWritePin(GPIO_PORTA, PIN2, OUTPUT_HIGH);
    GPIO_vidWritePin(GPIO_PORTA, PIN4, OUTPUT_HIGH);
    GPIO_vidWritePin(GPIO_PORTA, PIN5, OUTPUT_LOW);
    GPIO_vidWritePin(GPIO_PORTA, PIN6, OUTPUT_LOW);

    PWM_vidSetDutyCycle(Channel0, 80);
    PWM_vidSetDutyCycle(Channel2, 80);
}
/******************************************************************************/
/*! \Description set the pins to move one motor forward and the other         */
/*               motor backward to Turn right                                 */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void MOTOR_vidTurnRight(void)
{
    GPIO_vidWritePin(GPIO_PORTA, PIN2, OUTPUT_HIGH);
    GPIO_vidWritePin(GPIO_PORTA, PIN4, OUTPUT_LOW);
    GPIO_vidWritePin(GPIO_PORTA, PIN5, OUTPUT_LOW);
    GPIO_vidWritePin(GPIO_PORTA, PIN6, OUTPUT_HIGH);

    PWM_vidSetDutyCycle(Channel0, 40);
    PWM_vidSetDutyCycle(Channel2, 80);

}
/******************************************************************************/
/*! \Description set the pins to move one motor forward and the other         */
/*               motor backward to Turn left                                  */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void MOTOR_vidTurnLeft(void)
{
    GPIO_vidWritePin(GPIO_PORTA, PIN2, OUTPUT_LOW);
    GPIO_vidWritePin(GPIO_PORTA, PIN4, OUTPUT_HIGH);
    GPIO_vidWritePin(GPIO_PORTA, PIN5, OUTPUT_HIGH);
    GPIO_vidWritePin(GPIO_PORTA, PIN6, OUTPUT_LOW);

    PWM_vidSetDutyCycle(Channel0, 80);
    PWM_vidSetDutyCycle(Channel2, 40);
}
/******************************************************************************/
/*! \Description set the pins to stop the 2 motors                            */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void MOTOR_vidStop(void)
{
    GPIO_vidWritePin(GPIO_PORTA, PIN2, OUTPUT_LOW);
    GPIO_vidWritePin(GPIO_PORTA, PIN4, OUTPUT_LOW);
    GPIO_vidWritePin(GPIO_PORTA, PIN5, OUTPUT_LOW);
    GPIO_vidWritePin(GPIO_PORTA, PIN6, OUTPUT_LOW);

    PWM_vidSetDutyCycle(Channel0, 0);
    PWM_vidSetDutyCycle(Channel2, 0);
}
/******************************************************************************/
/*! \Description set the motors speed using PWM                               */
/*! \return      None                                                         */
/*! \arguments   arg 1                                                        */
/*                      Name : Motor                                          */
/*                      type : local type of enum (Motors)                    */
/*                      Description : Motor number (Motor1 - Motor2)          */
/*               arg 2                                                        */
/*                      Name : Value                                          */
/*                      type : uint16_t                                       */
/*                      Description : Duty Cycle Value (10 - 320)             */
/*                                                                            */
/******************************************************************************/
void MOTOR_vidSetSpeed(Motors motor,uint16_t value)
{
    if(motor == MOTOR_1)
    {
        PWM_vidSetDutyCycle(Channel0, value);
    }
    else if(motor == MOTOR_2)
    {

        PWM_vidSetDutyCycle(Channel2, value);
    }
    else
    {

    }
}

