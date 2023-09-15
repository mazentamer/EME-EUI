/******************************************************************************/
/*                                                                            */
/* !Layer           : Hardware Abstraction Layer (HAL)                        */
/*                                                                            */
/* !Module          : UART Communication                                      */
/* !Description     : UART Communication Module Header file                   */
/*                                                                            */
/* !File            : COM_UART.h                                              */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : CHAT Project @EME - EUI                                 */
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
/* !Designed by     : Mahmoud Emara                    !Date : SEP 04, 2023   */
/* !Coded by        : Mahmoud Emara                    !Date : SEP 04, 2023   */
/*                                                                            */
/* Ver 1.0    SEP 04, 2023     Initial release                                */
/******************************************************************************/

#ifndef HAL_COM_UART_INC_COM_UART_H_
#define HAL_COM_UART_INC_COM_UART_H_
#include <stdint.h>
/******************************************************************************/
/**************************** Configuration Macros ****************************/
/******************************************************************************/
#define MSG_MAX     20


/******************************************************************************/
/******************************** Local Type **********************************/
/******************************************************************************/
typedef enum
{
    NOT_OK,
    OK,
    LONG_MSG_ERROR,
    NOT_SEND_ERROR,
    COM_TYPE_ERROR
}COM_UARTstate_t;

typedef enum
{
    Tiva2Tiva,
    Tiva2PC
}COM_type_t;



/******************************************************************************/
/*************************** Functions Declaration ****************************/
/******************************************************************************/

/******************************************************************************/
/*! \Description : Initialise the UART Peripheral and GPIO Pins used in UART  */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void COM_UARTvidInit(void);

/******************************************************************************/
/*! \Description : Receive data from UART and Save it in a Buffer             */
/*! \return      : COM_UARTstate_t (NOT_OK, OK, LONG_MSG_ERROR,               */
/*                                  NOT_SEND_ERROR, COM_TYPE_ERROR)           */
/*! \arguments   :  COM_type_t Copy_COM ,  uint8_t*  Copy_Data                */
/******************************************************************************/
COM_UARTstate_t COM_UARTenuSendMSG(COM_type_t Copy_COM ,  uint8_t*  Copy_Data);

/******************************************************************************/
/*! \Description : Send data by UART from a Buffer                            */
/*! \return      : COM_UARTstate_t (NOT_OK, OK, LONG_MSG_ERROR,               */
/*                                  NOT_SEND_ERROR, COM_TYPE_ERROR)           */
/*! \arguments   :  COM_type_t Copy_COM ,  uint8_t*  Copy_Data                */
/******************************************************************************/
COM_UARTstate_t COM_UARTenuRecieveMSG(COM_type_t Copy_COM , uint8_t * Copy_Data);

/******************************************************************************/
/*! \Description : Send a String by UART given as paramter                    */
/*! \return      : COM_UARTstate_t (NOT_OK, OK, LONG_MSG_ERROR,               */
/*                                  NOT_SEND_ERROR, COM_TYPE_ERROR)           */
/*! \arguments   : COM_type_t Copy_COM , const uint8_t * Copy_Data            */
/******************************************************************************/
COM_UARTstate_t COM_UARTenuSendString(COM_type_t Copy_COM , const uint8_t * Copy_Data);

/******************************************************************************/
/*! \Description : Clear a given Buffer                                       */
/*! \return      : none                                                       */
/*! \arguments   : const uint8_t * Copy_Data                                  */
/******************************************************************************/
void COM_UARTvidClearBuffer(uint8_t* Copy_Buffer);



#endif /* HAL_COM_UART_INC_COM_UART_H_ */
