/*********************************************************************************************************************************************/
/*                                                          Author      : Islam Tarek                                                        */
/*                                                          SW Module   : config file                                                        */
/*                                                          Last Update : 13 / 7 /2022                                                       */
/*********************************************************************************************************************************************/

/* Definitions */
#define LED     1

/**
 * @brief  This is the LED Array which contains configuration of LEDs in project
 * the format of Array element is like this {LED_ID, LED_PORT, LED_PIN, LED_DIRECTION, LED_STATE}
 * @example {LED_RED, MCAL_GPIO_A, MCAL_PIN_0, LED_FORWARD, LED_OFF}
 * @note Order of leds inside Array is same as order of ID inside the enum
 */
#if LED == 1
    #include "LED/led.h"
    led_t LEDS[LED_MAX] =
    {
        /* Enter the Leds in your project following the instructions above */
    };
#endif