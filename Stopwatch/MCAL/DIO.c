#include "DIO.h"

void DIO_init(GPIO_PORT port)
{
    SET_BIT(SYSCTL_RCGCGPIO_R, port);

    while (GET_BIT(SYSCTL_PRGPIO_R, port) == 0){};

    if (port == PORTC)
    {
        GPIO_PORTC_LOCK_R = 0x4C4F434B;
        GPIO_PORTC_CR_R = 0x1F;
    }
    else if (port == PORTD)
    {
        GPIO_PORTD_LOCK_R = 0x4C4F434B;
        GPIO_PORTD_CR_R = 0xFF;
    }
    else if (port == PORTF)
    {
        GPIO_PORTF_LOCK_R = 0x4C4F434B;
        GPIO_PORTF_CR_R = 0x1F;
    }
}
void DIO_WritePin(GPIO_PORT port, PORT_BIT bit, GPIO_STATES state)
{
    switch(port)
    {
    case PORTA:
        if (state == HIGH)
        {
            SET_BIT(GPIO_PORTA_DATA_R, bit);
        }
        else if (state == LOW)
        {
            CLEAR_BIT(GPIO_PORTA_DATA_R, bit);
        }
        break;
    case PORTB:
        if (state == HIGH)
        {
            SET_BIT(GPIO_PORTB_DATA_R, bit);
        }
        else if (state == LOW)
        {
            CLEAR_BIT(GPIO_PORTB_DATA_R, bit);
        }
        break;
    case PORTC:
        if (state == HIGH)
        {
            SET_BIT(GPIO_PORTC_DATA_R, bit);
        }
        else if (state == LOW)
        {
            CLEAR_BIT(GPIO_PORTC_DATA_R, bit);
        }
        break;
    case PORTD:
        if (state == HIGH)
        {
            SET_BIT(GPIO_PORTD_DATA_R, bit);
        }
        else if (state == LOW)
        {
            CLEAR_BIT(GPIO_PORTD_DATA_R, bit);
        }
        break;
    case PORTE:
        if (state == HIGH)
        {
            SET_BIT(GPIO_PORTE_DATA_R, bit);
        }
        else if (state == LOW)
        {
            CLEAR_BIT(GPIO_PORTE_DATA_R, bit);
        }
        break;
    case PORTF:
        if (state == HIGH)
        {
            SET_BIT(GPIO_PORTF_DATA_R, bit);
        }
        else if (state == LOW)
        {
            CLEAR_BIT(GPIO_PORTF_DATA_R, bit);
        }
        break;
    }
}
void DIO_WritePORT(GPIO_PORT port, uint8 byte)
{
    switch (port)
    {
    case PORTA:
        GPIO_PORTA_DATA_R = byte;
        break;
    case PORTB:
        GPIO_PORTB_DATA_R = byte;
        break;
    case PORTC:
        GPIO_PORTC_DATA_R = byte;
        break;
    case PORTD:
        GPIO_PORTD_DATA_R = byte;
        break;
    case PORTE:
        GPIO_PORTE_DATA_R = byte;
        break;
    case PORTF:
        GPIO_PORTF_DATA_R = byte;
        break;
    }
}
uint8 DIO_ReadPin(GPIO_PORT port, PORT_BIT bit)
{
    uint8 state;
    switch(port)
    {
    case PORTA:
        state = GET_BIT(GPIO_PORTA_DATA_R, bit);
        break;
    case PORTB:
        state = GET_BIT(GPIO_PORTB_DATA_R, bit);
        break;
    case PORTC:
        state = GET_BIT(GPIO_PORTC_DATA_R, bit);
        break;
    case PORTD:
        state = GET_BIT(GPIO_PORTD_DATA_R, bit);
        break;
    case PORTE:
        state = GET_BIT(GPIO_PORTE_DATA_R, bit);
        break;
    case PORTF:
        state = GET_BIT(GPIO_PORTF_DATA_R, bit);
        break;
    }
    return state;
}
uint8 DIO_ReadPort(GPIO_PORT port)
{
    uint8 byte = 0;
    switch(port)
    {
    case PORTA:
        byte = GPIO_PORTA_DATA_R;
        break;
    case PORTB:
        byte = GPIO_PORTB_DATA_R;
        break;
    case PORTC:
        byte = GPIO_PORTC_DATA_R;
        break;
    case PORTD:
        byte = GPIO_PORTD_DATA_R;
        break;
    case PORTE:
        byte = GPIO_PORTE_DATA_R;
        break;
    case PORTF:
        byte = GPIO_PORTF_DATA_R;
        break;
    }
    return byte;
}
void DIO_SetPinDirection(GPIO_PORT port, PORT_BIT bit, GPIO_IO io)
{
    switch(port)
    {
    case PORTA:
        SET_BIT(GPIO_PORTA_DEN_R, bit);
        if (io == OUTPUT)
        {
            SET_BIT(GPIO_PORTA_DIR_R, bit);
        }
        else if (io == INPUT)
        {
            CLEAR_BIT(GPIO_PORTA_DIR_R, bit);
        }
        break;
    case PORTB:
        SET_BIT(GPIO_PORTB_DEN_R, bit);
        if (io == OUTPUT)
        {
            SET_BIT(GPIO_PORTB_DIR_R, bit);
        }
        else if (io == INPUT)
        {
            CLEAR_BIT(GPIO_PORTB_DIR_R, bit);
        }
    case PORTC:
        SET_BIT(GPIO_PORTC_DEN_R, bit);
        if (io == OUTPUT)
        {
            SET_BIT(GPIO_PORTC_DIR_R, bit);
        }
        else if (io == INPUT)
        {
            CLEAR_BIT(GPIO_PORTC_DIR_R, bit);
        }
    case PORTD:
        SET_BIT(GPIO_PORTD_DEN_R, bit);
        if (io == OUTPUT)
        {
            SET_BIT(GPIO_PORTD_DIR_R, bit);
        }
        else if (io == INPUT)
        {
            CLEAR_BIT(GPIO_PORTD_DIR_R, bit);
        }
    case PORTE:
        SET_BIT(GPIO_PORTE_DEN_R, bit);
        if (io == OUTPUT)
        {
            SET_BIT(GPIO_PORTE_DIR_R, bit);
        }
        else if (io == INPUT)
        {
            CLEAR_BIT(GPIO_PORTE_DIR_R, bit);
        }
    case PORTF:
        if (io == OUTPUT)
        {
            SET_BIT(GPIO_PORTF_DIR_R, bit);
        }
        else if (io == INPUT)
        {
            CLEAR_BIT(GPIO_PORTF_DIR_R, bit);
        }
        SET_BIT(GPIO_PORTF_DEN_R, bit);
    }
}
void DIO_SetPortDirection(GPIO_PORT port, uint8 byte)
{
    switch(port)
    {
    case PORTA:
        GPIO_PORTA_DEN_R = 0xFF;
        GPIO_PORTA_DIR_R = byte;
        break;
    case PORTB:
        GPIO_PORTB_DEN_R = 0xFF;
        GPIO_PORTB_DIR_R = byte;
        break;
    case PORTC:
        GPIO_PORTC_DEN_R = 0xFF;
        GPIO_PORTC_DIR_R = byte;
        break;
    case PORTD:
        GPIO_PORTD_DEN_R = 0xFF;
        GPIO_PORTD_DIR_R = byte;
        break;
    case PORTE:
        GPIO_PORTE_DEN_R = 0xFF;
        GPIO_PORTE_DIR_R = byte;
        break;
    case PORTF:
        GPIO_PORTF_DEN_R = 0xFF;
        GPIO_PORTF_DIR_R = byte;
        break;
    }
}

void DIO_SetResistorMode(GPIO_PORT port, PORT_BIT bit, DIO_RESISTOR_MODE resistor)
{
    switch(port)
    {
    case PORTA:
        if (resistor == PULL_UP)
        {
            SET_BIT(GPIO_PORTA_PUR_R, bit);
        }
        else if (resistor == PULL_DOWN)
        {
            SET_BIT(GPIO_PORTA_PDR_R, bit);
        }
        break;
    case PORTB:
        if (resistor == PULL_UP)
        {
            SET_BIT(GPIO_PORTB_PUR_R, bit);
        }
        else if (resistor == PULL_DOWN)
        {
            SET_BIT(GPIO_PORTB_PDR_R, bit);
        }
        break;
    case PORTC:
        if (resistor == PULL_UP)
        {
            SET_BIT(GPIO_PORTC_PUR_R, bit);
        }
        else if (resistor == PULL_DOWN)
        {
            SET_BIT(GPIO_PORTC_PDR_R, bit);
        }
        break;
    case PORTD:
        if (resistor == PULL_UP)
        {
            SET_BIT(GPIO_PORTD_PUR_R, bit);
        }
        else if (resistor == PULL_DOWN)
        {
            SET_BIT(GPIO_PORTD_PDR_R, bit);
        }
        break;
    case PORTE:
        if (resistor == PULL_UP)
        {
            SET_BIT(GPIO_PORTE_PUR_R, bit);
        }
        else if (resistor == PULL_DOWN)
        {
            SET_BIT(GPIO_PORTE_PDR_R, bit);
        }
        break;
    case PORTF:
        if (resistor == PULL_UP)
        {
            SET_BIT(GPIO_PORTF_PUR_R, bit);
        }
        else if (resistor == PULL_DOWN)
        {
            SET_BIT(GPIO_PORTF_PDR_R, bit);
        }
        break;
    }
}

void DIO_EnableInterrupt(GPIO_PORT port, PORT_BIT bit, DIO_INTERRUPT_SENSE sense, DIO_EDGE edge)
{

    switch(port)
    {
    case PORTA:
        if (sense == EDGE)
        {
            CLEAR_BIT(GPIO_PORTA_IS_R, bit);
            CLEAR_BIT(GPIO_PORTA_IBE_R, bit);
            if (edge == FALLING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTA_IEV_R, bit);
            }
            else if (edge == RISING_EDGE)
            {
                SET_BIT(GPIO_PORTA_IEV_R, bit);
            }
        }
        else if (sense == LEVEL)
        {
            SET_BIT(GPIO_PORTA_IS_R, bit);
            if (edge == FALLING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTA_IEV_R, bit);
            }
            else if (edge == RISING_EDGE)
            {
                SET_BIT(GPIO_PORTA_IEV_R, bit);
            }
        }
        else if (sense == BOTH_EDGES)
        {
            CLEAR_BIT(GPIO_PORTA_IS_R, bit);
            SET_BIT(GPIO_PORTA_IBE_R, bit);
        }
        SET_BIT(GPIO_PORTA_ICR_R, bit);
        SET_BIT(GPIO_PORTA_IM_R, bit);
        NVIC_EN0_R |= (1 << 0);
        break;
    case PORTF:
        if (sense == EDGE)
        {
            CLEAR_BIT(GPIO_PORTF_IS_R, bit);
            CLEAR_BIT(GPIO_PORTF_IBE_R, bit);
            if (edge == FALLING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTF_IEV_R, bit);
            }
            else if (edge == RISING_EDGE)
            {
                SET_BIT(GPIO_PORTF_IEV_R, bit);
            }
        }
        else if (sense == LEVEL)
        {
            SET_BIT(GPIO_PORTF_IS_R, bit);
        }
        else if (sense == BOTH_EDGES)
        {
            CLEAR_BIT(GPIO_PORTF_IS_R, bit);
            SET_BIT(GPIO_PORTF_IBE_R, bit);
        }
        SET_BIT(GPIO_PORTF_ICR_R, bit);
        SET_BIT(GPIO_PORTF_IM_R, bit);
        NVIC_EN0_R |= (1 << 30);
        break;
    }
}
