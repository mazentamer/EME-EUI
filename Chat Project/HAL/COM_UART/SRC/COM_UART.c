/******************************************************************************/
/*                                                                            */
/* !Layer           : Hardware Abstraction Layer (HAL)                        */
/*                                                                            */
/* !Module          : UART Communication                                      */
/* !Description     : UART Communication Module implementation                */
/*                                                                            */
/* !File            : COM_UART.c                                              */
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
#include "../INC/COM_UART.h"

/*! Include compiler types header                                             */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

/******************************************************************************/
/******************************** GLOBAL VARIABLS *****************************/
/******************************************************************************/
uint8_t GlobBufferUART[MSG_MAX];
extern bool keyPressed ;

/******************************************************************************/
/*! \Description : Initialise the UART Peripheral and GPIO Pins used in UART  */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void COM_UARTvidInit(void)
{
    /*****  UART pins Configuration                    *****/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    /*****  UART pin Configuration and initialisation  *****/
    /* Enable the UART0 module.*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    /* Wait for the UART0 module to be ready. */
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
    {
    }
    /* Initialize the UART. Set the baud rate, number of data bits, turn off
       parity, number of stop bits, and stick mode. The UART is enabled by the
       function call. */

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 38400,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                UART_CONFIG_PAR_NONE));

    /*****  UART pins Configuration                    *****/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeUART(GPIO_PORTE_BASE,GPIO_PIN_4|GPIO_PIN_5);
    GPIOPinConfigure(GPIO_PE4_U5RX);
    GPIOPinConfigure(GPIO_PE5_U5TX);

    /*****  UART pin Configuration and initialisation  *****/
    /* Enable the UART0 module.*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);

    /* Wait for the UART0 module to be ready. */
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART5))
    {
    }
    /* Initialize the UART. Set the baud rate, number of data bits, turn off
           parity, number of stop bits, and stick mode. The UART is enabled by the
           function call. */

    UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), 38400,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                UART_CONFIG_PAR_NONE));
}

/******************************************************************************/
/*! \Description : Receive data from UART and Save it in a Buffer             */
/*! \return      : COM_UARTstate_t (NOT_OK, OK, LONG_MSG_ERROR,               */
/*                                  NOT_SEND_ERROR, COM_TYPE_ERROR)           */
/*! \arguments   :  COM_type_t Copy_COM ,  uint8_t*  Copy_Data                */
/******************************************************************************/
COM_UARTstate_t COM_UARTenuRecieveMSG(COM_type_t Copy_COM ,  uint8_t *  Copy_Data)
{
    int16_t i=-1 ;
    COM_UARTstate_t Local_state = NOT_OK ;
    if(Copy_COM == Tiva2PC)
    {
        if(UARTCharsAvail(UART0_BASE))
        {
            while(Copy_Data[i]!=13 && i<(MSG_MAX-1) && !keyPressed)
            {

                Copy_Data[++i] = UARTCharGet(UART0_BASE);
                UARTCharPut(UART0_BASE, Copy_Data[i]);
                if(Copy_Data[i] == 127)
                { i-=2;}

            }
            if(i >= (MSG_MAX-1))
            {
                Local_state = LONG_MSG_ERROR;
            }
            else
            {
                Local_state = OK;
            }
            UARTCharPut(UART0_BASE, '\n');
        }
    }
    else if(Copy_COM == Tiva2Tiva)
    {
        if(UARTCharsAvail(UART5_BASE))
        {
            while(Copy_Data[i]!=13 && i<(MSG_MAX-1) && !keyPressed)
            {

                Copy_Data[++i] = UARTCharGet(UART5_BASE);


            }
            if(i >= (MSG_MAX-1))
            {
                Local_state = LONG_MSG_ERROR;
            }
            else
            {
                Local_state = OK;
            }
        }

    }
    else
    {
        Local_state = COM_TYPE_ERROR;
    }
    return Local_state;
}


/******************************************************************************/
/*! \Description : Send data by UART from a Buffer                            */
/*! \return      : COM_UARTstate_t (NOT_OK, OK, LONG_MSG_ERROR,               */
/*                                  NOT_SEND_ERROR, COM_TYPE_ERROR)           */
/*! \arguments   :  COM_type_t Copy_COM ,  uint8_t*  Copy_Data                */
/******************************************************************************/
COM_UARTstate_t COM_UARTenuSendMSG(COM_type_t Copy_COM , uint8_t * Copy_Data)
{
    int16_t i=-1;
    COM_UARTstate_t Local_state = NOT_OK ;
    if(Copy_COM == Tiva2PC)
    {
        while(Copy_Data[i]!=13 && i<(MSG_MAX-1) && !keyPressed)
        {

            UARTCharPut(UART0_BASE, Copy_Data[++i]);

        }
        UARTCharPut(UART0_BASE, '\n');
        UARTCharPut(UART0_BASE, '\r');
        if(i >= (MSG_MAX-1))
        {
            Local_state = LONG_MSG_ERROR;
        }
        else
        {
            Local_state = OK;
        }
    }
    else if(Copy_COM == Tiva2Tiva)
    {
        while(Copy_Data[i]!=13 && i<(MSG_MAX-1) && !keyPressed)
        {
            UARTCharPut(UART5_BASE, Copy_Data[++i]);
        }
        if(i >= (MSG_MAX-1))
        {
            Local_state = LONG_MSG_ERROR;
        }
        else
        {
            Local_state = OK;
        }
    }
    else
    {
        Local_state = COM_TYPE_ERROR;
    }
    return Local_state;
}

/******************************************************************************/
/*! \Description : Send a String by UART given as paramter                    */
/*! \return      : COM_UARTstate_t (NOT_OK, OK, LONG_MSG_ERROR,               */
/*                                  NOT_SEND_ERROR, COM_TYPE_ERROR)           */
/*! \arguments   : COM_type_t Copy_COM , const uint8_t * Copy_Data            */
/******************************************************************************/
COM_UARTstate_t COM_UARTenuSendString(COM_type_t Copy_COM , const uint8_t * Copy_Data)
{
    int16_t i=-1;
    COM_UARTstate_t Local_state = NOT_OK ;
    if(Copy_COM == Tiva2PC)
    {
        while(Copy_Data[i]!='\0' && i<(MSG_MAX-1))
        {

            UARTCharPut(UART0_BASE, Copy_Data[++i]);

        }
        if(i >= (MSG_MAX-1))
        {
            Local_state = LONG_MSG_ERROR;
        }
        else
        {
            Local_state = OK;
        }
        UARTCharPut(UART0_BASE, '\n');
        UARTCharPut(UART0_BASE, '\r');
    }
    else if(Copy_COM == Tiva2Tiva)
    {
        while(Copy_Data[i]!='\0' && i<(MSG_MAX-1))
        {
            UARTCharPut(UART5_BASE, Copy_Data[++i]);
        }
        if(i >= (MSG_MAX-1))
        {
            Local_state = LONG_MSG_ERROR;
        }
        else
        {
            Local_state = OK;
        }
        UARTCharPut(UART0_BASE, '\n');
        UARTCharPut(UART0_BASE, '\r');
    }
    else
    {
        Local_state = COM_TYPE_ERROR;
    }
    return Local_state;
}

/******************************************************************************/
/*! \Description : Clear a given Buffer                                       */
/*! \return      : none                                                       */
/*! \arguments   : const uint8_t * Copy_Data                                  */
/******************************************************************************/
void COM_UARTvidClearBuffer(uint8_t* Copy_Buffer)
{
    int16_t i = 0;
    while(i < MSG_MAX)
    {
        Copy_Buffer[i++]=0;
    }
}
