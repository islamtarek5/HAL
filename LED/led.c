/*********************************************************************************************************************************************/
/*                                                          Author      : Islam Tarek                                                        */
/*                                                          SW Module   : LED                                                                */
/*                                                          Last Update : 13 / 7 /2022                                                       */
/*********************************************************************************************************************************************/

/* Includes */
#include "led.h"

/* Global variables */
extern led_t LEDS[LED_MAX];

hal_err_t led_init(led_id_t id)
{
    if (id >= LED_MAX)
    {
        return HAL_FAIL;
    }
    else
    {
        mcal_gpio_set_pin_direction(LEDS[id].led_port , LEDS[id].led_pin, PIN_OUTPUT);
        switch (LEDS[id].led_state)
        {
        case LED_ON:
            if(LEDS[id].led_direction == LED_FORWARD)
                mcal_gpio_set_pin_level(LEDS[id].led_port , LEDS[id].led_pin, PIN_HIGH);
            else if(LEDS[id].led_direction == LED_REVERSE)
                mcal_gpio_set_pin_level(LEDS[id].led_port , LEDS[id].led_pin, PIN_LOW);
            else
                return HAL_FAIL;
            break;
        case LED_OFF:
            if(LEDS[id].led_direction == LED_FORWARD)
                mcal_gpio_set_pin_level(LEDS[id].led_port , LEDS[id].led_pin, PIN_LOW);
            else if(LEDS[id].led_direction == LED_REVERSE)
                mcal_gpio_set_pin_level(LEDS[id].led_port , LEDS[id].led_pin, PIN_HIGH);
            else
                return HAL_FAIL;
            break;
        default:
            return HAL_FAIL;
        }
    }
    return HAL_OK;
    
}

hal_err_t led_set_state (led_id_t id, led_state_t state);
hal_err_t led_get_state (led_id_t id, led_state_t* state);
