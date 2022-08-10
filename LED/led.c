/*********************************************************************************************************************************************/
/*                                                          Author      : Islam Tarek                                                        */
/*                                                          SW Module   : LED                                                                */
/*                                                          Last Update : 10 / 8 /2022                                                       */
/*********************************************************************************************************************************************/

/* Includes */
#include "led.h"

/* Global variables */

/**
 * @brief exists in proj_config.c file
 */
extern led_t LEDS[LED_MAX];
const uint8_t FIRST_LED = 0;

/* Static functions */

static void led_control(led_id_t id, led_state_t state);

/**
 * @brief This function is used to cotrol LED state depending on the LED direction
 * @param id The ID of led which will be controlled
 * @param state The state of the led (LED_ON, LED_OFF or LED_TOG)
 */
static void led_control(led_id_t id, led_state_t state)
{
    switch (state)
    {
    case LED_ON:
        if(LEDS[id].led_direction == LED_FORWARD)
            mcal_gpio_set_pin_level(LEDS[id].led_port , LEDS[id].led_pin, PIN_HIGH);
        else if(LEDS[id].led_direction == LED_REVERSE)
            mcal_gpio_set_pin_level(LEDS[id].led_port , LEDS[id].led_pin, PIN_LOW);
        break;
    case LED_OFF:
        if(LEDS[id].led_direction == LED_FORWARD)
            mcal_gpio_set_pin_level(LEDS[id].led_port , LEDS[id].led_pin, PIN_LOW);
        else if(LEDS[id].led_direction == LED_REVERSE)
            mcal_gpio_set_pin_level(LEDS[id].led_port , LEDS[id].led_pin, PIN_HIGH);
        break;
    case LED_TOG:
        mcal_gpio_toggle_pin(LEDS[id].led_port , LEDS[id].led_pin);
        break;
    }
}
/**
 * @brief This API initialize directions of LEDS
 */
void led_init(void)
{
    uint8_t led;
    for(led = FIRST_LED ; led < LED_MAX; led ++)
    {
        mcal_gpio_set_pin_direction(LEDS[led].led_port , LEDS[led].led_pin, PIN_OUTPUT);
        if (LEDS[led].led_state != LED_TOG)
            led_control(LEDS[led].led_id, LEDS[led].led_state);
    }
}
/**
 * @brief This API set the state of chosen LED
 * @param id The ID of led which its state will be set
 * @param state The state of the led (LED_ON, LED_OFF or LED_TOG)
 */
void led_set_state(led_id_t id, led_state_t state)
{
    if(id < LED_MAX)
        LEDS[id].led_state = state;
}
/**
 * @brief This API get the stat of the chosen LED if it's on , off or toggle
 * @param id The ID of the led which its state will be gotten
 * @return the state of chosen LED (LED_ON, LED_OFF or LED_TOG)
 */
led_state_t led_get_state(led_id_t id)
{
    return LEDS[id].led_state;
}
/**
 * @brief This API is responsible for running LED
 */
void led_update(void)
{
    /* Timing characterstics will be added */
    led_id_t led ; 
    for(led = FIRST_LED ; led < LED_MAX; led++)
        led_control(led, LEDS[led].led_state);
}