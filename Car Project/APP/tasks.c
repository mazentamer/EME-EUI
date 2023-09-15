/*
 * tasks.c
 *
 *  Created on: Sep 14, 2023
 *      Author: Mazen
 */

#include "tasks.h"

extern uint32_t Glob_u32Distance;
extern uint16_t Glob_TickCounts;
extern uint16_t Glob_TimeCount;
extern uint8_t Glob_u8DistanceFlag;

uint8_t Glob_u8ObstacleState;
uint8_t Glob_u8ObstacleCounter;
uint8_t Glob_u8ObstacleTaskFlag;

uint16_t Glob_u16Difference = 0;

uint8_t Glob_u8Sw1 = 0;
uint8_t Glob_u8Sw2 = 0;

void tasks_modulesInit(void)
{
    LDR_vidInit();
    LCD_vidInit();
    Button_vidInit();
    Temperature_vidInit();
    Ultrasonic_vidInit();
    MOTOR_vidInit();
}

void button_scan(void)
{
    if(Button_vidGetButtonValue(BUTTON_PORT, BUTTON_0) == Button_High)
    {
        /*Check Second Time*/
        while (Button_vidGetButtonValue(BUTTON_PORT, BUTTON_0) == Button_High){};
        Glob_u8Sw1 = 1;
        Glob_TimeCount = 0;
        MOTOR_vidForward();
    }

    if(Button_vidGetButtonValue(BUTTON_PORT, BUTTON_1) == Button_High)
    {
        while (Button_vidGetButtonValue(BUTTON_PORT, BUTTON_1) == Button_High){};
        Glob_u8Sw1 = 0;
        MOTOR_vidStop();
    }

    if (Glob_TimeCount % 60 == 0 && Glob_TimeCount > 0)
    {
        Glob_u8Sw1 = 0;
        MOTOR_vidStop();
    }
}

void ldr_swing_car(void)
{
    if(Glob_u8ObstacleTaskFlag == 0 && Glob_u8Sw1 == 1)
    {
        uint16_t Local_u16LDR1 = 0;
        uint16_t Local_u16LDR2 = 0;
        LDR_vidGetLeftBright(&Local_u16LDR1);

        LDR_vidGetRightBright(&Local_u16LDR2);

        if(Local_u16LDR1 > Local_u16LDR2)
        {
            Glob_u16Difference = Local_u16LDR1-Local_u16LDR2;
            if(Glob_u16Difference > 150 )
            {
                /*Turn Right*/

                MOTOR_vidTurnLeft();
            }
            else
            {
                MOTOR_vidForward();
            }
        }
        else
        {
            Glob_u16Difference = Local_u16LDR2-Local_u16LDR1;
            if(Glob_u16Difference > 150 )
            {
                /*Turn Left*/
                MOTOR_vidTurnRight();
            }
            else
            {
                MOTOR_vidForward();
            }
        }
    }
    else
    {
        /* Do Nothing*/
    }
}


void lcd_display(void)
{
    uint8_t Local_u8timeflag = 0;
    uint8_t Local_u8MINCounter = 0;
    uint8_t Local_u8SecCounter = 0;
    uint8_t Local_u8time[6] = "00:00";
    uint16_t Local_u16temp;


    LCD_vidWriteString("Temp:");
    LCD_vidMoveCursor(0,9);
    LCD_vidWriteString("LDR:");
    LCD_vidMoveCursor(1,1);
    LCD_vidWriteString("Time:");
    LCD_vidWriteString(Local_u8time);

    Temperature_vidGetTemperature(&Local_u16temp);

    LCD_vidMoveCursor(0,6);
    LCD_vidWriteNumber(Local_u16temp);

    LCD_vidMoveCursor(0,13);
    LCD_vidWriteNumber(Glob_u16Difference);

    /*check if the systick timer fire interupt*/
    if(Local_u8timeflag == 1)
    {
        /*clear the flag*/
        Local_u8timeflag=0;

        /*check if the seconds exceed 60 second*/
        if(Local_u8SecCounter >= 60)
        {
            /*clear the second counter*/
            Local_u8time[3] = '0';
            Local_u8time[4] = '0';
            Local_u8SecCounter=0;
            /*increment the minutes counter*/
            Local_u8MINCounter++;
            /*convert the minutes to string*/
            Local_u8time[0] = (Local_u8MINCounter%10) +'0';
            Local_u8time[1] = (Local_u8MINCounter/10) +'0';
        }
        else
        {
            /*convert the second to string*/

            Local_u8time[4] = (Local_u8SecCounter%10) +'0';
            Local_u8time[3] = (Local_u8SecCounter/10) +'0';
        }
        //LCD_clear();
        LCD_vidMoveCursor(1,7);
        /*print the time on the lcd */
        LCD_vidWriteString(Local_u8time);
    }
}

void avoid_obstacles(void) /*40ms*/
{
    uint32_t Local_u32Distance = Glob_u32Distance;

    if (Glob_u8DistanceFlag == 1)
    {
        Local_u32Distance = Glob_u32Distance;

        if (Local_u32Distance <= MAX_DISTANCE && Local_u32Distance > 0)
        {
            Glob_u8ObstacleTaskFlag = 1;
        }

        if (Glob_u8ObstacleState == 2)
        {
            Glob_u8ObstacleState = 0;
            MOTOR_vidForward();
        }

        if (Glob_u8ObstacleState < 2 || (Local_u32Distance <= MAX_DISTANCE && Local_u32Distance > 0))
        {
            if (Glob_u8ObstacleTaskFlag == 1 && Glob_u8Sw1 == 1)
            {
                if (Glob_u8ObstacleState == 0)
                {
                    if (Local_u32Distance <= MAX_DISTANCE)
                    {
                        MOTOR_vidBackward();
                    }
                    else
                    {
                        Glob_u8ObstacleState++;
                    }
                }
                else if (Glob_u8ObstacleState == 1)
                {
                    MOTOR_vidTurnRight();
                    Glob_u8ObstacleCounter++;

                    if (Glob_u8ObstacleCounter == 20)
                    {
                        Glob_u8ObstacleState++;
                        Glob_u8ObstacleCounter = 0;
                        Glob_u8ObstacleTaskFlag = 0;
                    }
                }
            }
        }
        Glob_u8DistanceFlag = 0;
    }
    else
    {
        Ultrasonic_vidGetDistance();
    }


}



