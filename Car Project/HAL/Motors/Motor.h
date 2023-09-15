/******************************************************************************/
/*                                                                            */
/* !Layer           : Hardware Abstraction Layer (HAL)                        */
/*                                                                            */
/* !Module          : Motors                                                  */
/* !Description     : Motors Module Header file                               */
/*                                                                            */
/* !File            : Motor.h                                                 */
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

#ifndef HAL_MOTOR_H_
#define HAL_MOTOR_H_

/******************************************************************************/
/*********************************** INCLUDES *********************************/
/******************************************************************************/

#include "../../GeneralFunctions/std_types.h"

/******************************************************************************/
/****************************** Local Types ***********************************/
/******************************************************************************/
typedef enum
{
    MOTOR_1,MOTOR_2
}Motors;


/******************************************************************************/
/*************************** Functions Declaration ****************************/
/******************************************************************************/

/******************************************************************************/
/*! \Description Initialise the Motors pin used                               */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void MOTOR_vidInit(void);
/******************************************************************************/
/*! \Description set the pins to move the 2 motors forward                    */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void MOTOR_vidForward(void);
/******************************************************************************/
/*! \Description set the pins to move the 2 motors backward                   */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void MOTOR_vidBackward(void);
/******************************************************************************/
/*! \Description set the pins to move one motor forward and the other         */
/*               motor backward to Turn right                                 */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void MOTOR_vidTurnRight(void);
/******************************************************************************/
/*! \Description set the pins to move one motor forward and the other         */
/*               motor backward to Turn left                                  */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void MOTOR_vidTurnLeft(void);
/******************************************************************************/
/*! \Description set the pins to stop the 2 motors                            */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void MOTOR_vidStop(void);
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
void MOTOR_vidSetSpeed(Motors Motor,uint16_t value);



#endif /* HAL_MOTOR_H_ */
