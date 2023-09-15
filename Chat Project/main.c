/******************************************************************************/
/*                                                                            */
/* !Layer           : Application (APP)                                       */
/*                                                                            */
/* !Module          : main                                                    */
/* !Description     : main entry                                              */
/*                                                                            */
/* !File            : main.c                                                  */
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

/*! Include compiler types header                                             */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

#include "HAL/COM_UART/INC/COM_UART.h"
#include "HAL/LED/INC/LED.h"
#include "APP/ChatPC/INC/ChatPC.h"

/******************************************************************************/
/************************** GLOBAL VARIABLS Externs ***************************/
/******************************************************************************/
extern uint8_t GlobBufferUART[MSG_MAX];
extern CHAT_state CurrentState  ;
extern COM_UARTstate_t GlobUARTstate ;


int main(void)
{
    ChatPC_vidInit();

    while(1)
    {
        ChatPC_vidCall();
    }

}
