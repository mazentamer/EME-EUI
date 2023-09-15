/**
 * main.c
 */

#include "APP/tasks.h"
#include "OS/scheduler.h"

int main(void)
{
    tasks_modulesInit();
    create_task(button_scan, 1);
    create_task(avoid_obstacles, 2);
    create_task(ldr_swing_car, 3);
    create_task(lcd_display, 7);
    OS_Start();

    tasks_scheduler();

    while (1)
    {

    }
}
