/******************************************************************************/
/*                                                                            */
/* !Layer           : Application (APP)                                       */
/*                                                                            */
/* !Module          : Chat PC                                                 */
/* !Description     : Chat PC Module implementation                           */
/*                                                                            */
/* !File            : ChatPC.c                                                */
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

/*! Include the module header file                                            */
#include "../INC/ChatPC.h"

/*! Include compiler types header                                             */
#include <stdbool.h>
#include <stdint.h>
#include "../../../HAL/COM_UART/INC/COM_UART.h"
#include "../../../HAL/LED/INC/LED.h"
#include "../../../HAL/PushButton/INC/push_button.h"

/******************************************************************************/
/******************************** GLOBAL VARIABLS *****************************/
/******************************************************************************/
extern uint8_t GlobBufferUART[MSG_MAX];
CHAT_state CurrentState = ONLINE ;
COM_UARTstate_t GlobUARTstate ;
uint8_t keyPressed = 0 ;

/******************************************************************************/
/*! \Description : Initialise the used Modules in the application             */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void ChatPC_vidInit(void)
{
    LEDvidInit();
    COM_UARTvidInit();
    pushButton_init();
    pushButton_CallBackFunction(PB1_Function, PB2_Function);
}

/******************************************************************************/
/*! \Description : The Runnable function that handle the chat                 */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void ChatPC_vidCall(void)
{
    switch(CurrentState)
    {
    case OFFLINE:
        LEDvidOFF(BLUE_LED);
        LEDvidOFF(GREEN_LED);
        LEDvidON(RED_LED);
        keyPressed = 0 ;
        break;
    case LESTIN:
        LEDvidOFF(RED_LED);
        LEDvidOFF(GREEN_LED);
        LEDvidON(BLUE_LED);
        GlobUARTstate = COM_UARTenuRecieveMSG(Tiva2Tiva, GlobBufferUART);
        if(GlobUARTstate == LONG_MSG_ERROR)
        {
            COM_UARTenuSendString(Tiva2PC, "Long MSG");
            COM_UARTenuSendMSG(Tiva2PC,GlobBufferUART);
        }
        else if(GlobUARTstate == OK)
        {
            COM_UARTenuSendMSG(Tiva2PC,GlobBufferUART);
        }
        else
        {
            /*  DO NOTHING  */
        }

        GlobUARTstate = COM_UARTenuRecieveMSG(Tiva2PC, GlobBufferUART);
        if(GlobUARTstate == LONG_MSG_ERROR)
        {
            COM_UARTenuSendString(Tiva2PC, "Long MSG");
            COM_UARTvidClearBuffer(GlobBufferUART);
            //COM_UARTenuSendMSG(Tiva2PC,GlobBufferUART);
        }
        else if(GlobUARTstate == OK)
        {
            COM_UARTvidClearBuffer(GlobBufferUART);
        }
        else
        {
            /*  DO NOTHING  */
        }
        keyPressed = 0 ;
        break;
    case ONLINE:
        LEDvidOFF(BLUE_LED);
        LEDvidOFF(RED_LED);
        LEDvidON(GREEN_LED);

        GlobUARTstate = COM_UARTenuRecieveMSG(Tiva2PC, GlobBufferUART);
        if(GlobUARTstate == LONG_MSG_ERROR)
        {
            COM_UARTenuSendString(Tiva2PC, "Long MSG");
            COM_UARTenuSendMSG(Tiva2Tiva,GlobBufferUART);
            COM_UARTvidClearBuffer(GlobBufferUART);
        }
        else if(GlobUARTstate == OK)
        {
            COM_UARTenuSendMSG(Tiva2Tiva,GlobBufferUART);
            COM_UARTvidClearBuffer(GlobBufferUART);
        }
        else
        {
            /*  DO NOTHING  */
        }
        GlobUARTstate = COM_UARTenuRecieveMSG(Tiva2Tiva, GlobBufferUART);
        if(GlobUARTstate == LONG_MSG_ERROR)
        {
            //COM_UARTenuSendString(Tiva2PC, "Long MSG");
            COM_UARTenuSendMSG(Tiva2PC,GlobBufferUART);
            COM_UARTvidClearBuffer(GlobBufferUART);
        }
        else if(GlobUARTstate == OK)
        {
            COM_UARTenuSendMSG(Tiva2PC,GlobBufferUART);
            COM_UARTvidClearBuffer(GlobBufferUART);
        }
        else
        {
            /*  DO NOTHING  */
        }
        keyPressed = 0 ;
        break;
    default:
        break;
    }
}

/******************************************************************************/
/*! \Description : function Send by callback to the Pushbutton module to      */
/*                 to handle changing (incrementing) of the chat states       */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void PB1_Function(void)
{
    keyPressed = 1;

    if(CurrentState == ONLINE)
    {
        CurrentState = OFFLINE;
    }
    else
    {
        CurrentState++;
    }
}

/******************************************************************************/
/*! \Description : function Send by callback to the Pushbutton module to      */
/*                 to handle changing (decrementing) of the chat states       */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void PB2_Function(void)
{
    keyPressed = 1;
    if(CurrentState == OFFLINE)
    {
        CurrentState = ONLINE;
    }
    else
    {
        CurrentState--;
    }
}
