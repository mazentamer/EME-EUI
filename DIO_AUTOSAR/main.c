

/**
 * main.c
 */
#include "MCAL/Dio/Dio.h"

int main(void)
{
    Port_Init(STD_OUTPUT, 41);
    Port_Init(STD_OUTPUT, 42);
    Port_Init(STD_OUTPUT, 43);
    while (1)
    {
        Dio_WritePort(PORTF, 0x0E);
    }
}
