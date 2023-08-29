/**
 * main.c
 */
#include "Libraries/bitwise_operation.h"
#include "Libraries/hw_gpio.h"
#include "MCAL/DIO.h"
#include "MCAL/TIMER_Interface.h"

void delay(uint32 ms);      /*Software delay function for noticing the change in brightness of LED*/

int main(void)
{
    /**********************Function for configuring any timer to be in PWM mode***********************/
    Timer_PWM_Config(TIMER1, TIMERA_PORT1, TIMER1_PIN0, TIMERA, EDGE_COUNT, PERIODIC, NOT_INVERTED, 8000U);

    uint32 test = 8000U;    /*The variable that will be assigned to the match register for duty cycle change*/
    uint8 flag = 0;         /*Flag for allowing for the brightness of the controlled LED to be smooth*/

    while (1)
    {
        if (flag == 0)
        {
            test--;             /*Decrement the match register value*/
            if (test == 0)
            {
                flag = 1;       /*Raise flag to indicate value of variable has reached zero*/
            }
        }
        else
        {
            test++;             /*If the flag is set, this means that the variable is zero, starts incrementing*/
            if (test == 8000)
            {
                flag = 0;       /*Lower the flag if variable has reached the interval load value*/
            }
        }
        Timer_PWM_setDutyCycle(TIMER1, TIMERA, test);   /*Function call for changing the duty cycle*/
        delay(1);                                       /*Delay function to see effect of duty cycle change*/
    }
}

void delay(uint32 ms)
{
    unsigned long volatile t;
    t = 762*ms;
    while(t){
        t--;
    }
}
