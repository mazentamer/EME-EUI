/*
 * LED.h
 *
 *  Created on: 3 Sep 2023
 *      Author: dell
 */

#ifndef HAL_LED_INC_LED_H_
#define HAL_LED_INC_LED_H_

typedef enum
{
    RED_LED,
    BLUE_LED,
    GREEN_LED
}LED_type_t;

void LEDvidInit(void);
void LEDvidON(LED_type_t Copy_LEDid);
void LEDvidOFF(LED_type_t Copy_LEDid);
void LEDvidAllLedOFF(void);

#endif /* HAL_LED_INC_LED_H_ */
