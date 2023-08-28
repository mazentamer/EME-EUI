/**
 * main.c
 */
#include "Libraries/bitwise_operation.h"
#include "Libraries/hw_gpio.h"
#include "MCAL/DIO.h"
#include "MCAL/TIMER_Interface.h"

void delay(uint32 ms);

int main(void)
{
    Timer_PWM_Config(TIMER1, TIMERA_PORT1, TIMER1_PIN0, TIMERA, EDGE_COUNT, PERIODIC, NOT_INVERTED, 16000U);

    uint16 test = 16000U;
    uint8 flag = 0;

    while (1)
    {
        if (flag == 0)
        {
            test--;
            if (test == 0)
            {
                flag = 1;
            }
        }
        else
        {
            test++;
            if (test == 16000)
            {
                flag = 0;
            }
        }
        Timer_PWM_setDutyCycle(TIMER1, TIMERA, test);
        delay(1);
    }
}

void delay(uint32 ms)
{
    unsigned long volatile t;
    t = 1524*ms;
    while(t){
        t--;
    }
}
