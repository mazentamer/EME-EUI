/******************************************************************************/
/*                                                                            */
/* !Layer           : Application (APP)                                       */
/*                                                                            */
/* !Module          : Chat PC                                                 */
/* !Description     : Chat PC Module implementation                           */
/*                                                                            */
/* !File            : ChatPC.h                                                */
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

#ifndef APP_CHATPC_INC_CHATPC_H_
#define APP_CHATPC_INC_CHATPC_H_

/******************************************************************************/
/******************************** Local Type **********************************/
/******************************************************************************/
typedef enum
{
    OFFLINE,
    LESTIN,
    ONLINE
}CHAT_state;

/******************************************************************************/
/*************************** Functions Declaration ****************************/
/******************************************************************************/

/******************************************************************************/
/*! \Description : Initialise the used Modules in the application             */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void ChatPC_vidInit(void);

/******************************************************************************/
/*! \Description : The Runnable function that handle the chat                 */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void ChatPC_vidCall(void);

/******************************************************************************/
/*! \Description : function Send by callback to the Pushbutton module to      */
/*                 to handle changing (incrementing) of the chat states       */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void PB1_Function(void);

/******************************************************************************/
/*! \Description : function Send by callback to the Pushbutton module to      */
/*                 to handle changing (decrementing) of the chat states       */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void PB2_Function(void);

#endif /* APP_CHATPC_INC_CHATPC_H_ */
