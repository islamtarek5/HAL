/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-08-28 15:06:37                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-08-29 11:38:23                              *
 * @FilePath              : led.c                                            *
 ****************************************************************************/

/**
 * @section Includes
 */

#include "led.h"


/**
 * @section Definitions
 */

#define FIRST_LED   0U

/**
 * @section External Global Variables
 */

extern Led_S LEDs_CFG[LED_MAX_ID];


/**
 * @section Static function prototype.
 */

static void LED_control_state(led_id_t);


/**
 * @section Static function Implementation
 */

/**
 * @brief This API is used to control LED state and drive MCU Pin with suitable output to achieve required state.
 * @param id The ID of th led whose state will be controlled.
 */
static void LED_control_state(led_id_t id)
{
    /* Check if the LED state is toggle or not */
    if(LEDs_CFG[id].state == LED_TOG)
    {
        /* Toggle LED state */
        (void)MCAL_GPIO_toggle_pin_level(LEDs_CFG[id].port, LEDs_CFG[id].pin);
    }
    else
    {
        /* Control the state of the given LED */
        /* XOR between Bias and state is used to get suitable GPIO output */
        (void)MCAL_GPIO_set_pin_level(LEDs_CFG[id].port, LEDs_CFG[id].pin, (LEDs_CFG[id].bias ^ LEDs_CFG[id].state));
    }
}

/**
 * @brief This API is used to Initialze MCU Pins that are connected to LEDs as output and to initialize LEDs State.
 */
void LED_init(void)
{
    /* Loop for LEDs to initialze them */
    uint8_t led = FIRST_LED;
    for(led = FIRST_LED, led < LED_MAX_ID, led ++)
    {
        /* Initialize LEDs Pins as output */
        (void)MCAL_GPIO_set_pin_mode(LEDs_CFG[led].port, LEDs_CFG[led].pin, MCAL_PIN_OUTPUT);
        /* Check if the state exists or not and that initial state isn't toggle */
        if((LEDs_CFG[led].state < LED_MAX_STATE) && (LEDs_CFG[led].state != LED_TOG))
        {
            LED_control_state(led);   
        }
        else
        {
            /* Do Nothing */
        }
    }
}

/**
 * @brief This API is used to set LED state.
 * @param id The ID of LED whose state will be set.
 * @param state The state to which LED will be set (LED_OFF, LED_ON, LED_TOG).
 */
void LED_set_state(led_id_t id, led_state_t state)
{
    /* Check if the LED ID and LED state exist or not */
    if((id < LED_MAX_ID) && (state < LED_MAX_STATE))
    {
        /* update the state of the LED */
        LEDs_CFG[id].state = state;
    }
    else
    {
        /* Do Nothing */
    }
}

/**
 * @brief This API is used to get the state of the LED.
 * @param id The ID of LED whose state will be got.
 * @return The state of the LED (LED_OFF, LED_ON or LED_TOG).
 */
led_state_t LED_get_state(led_id_t id)
{
    led_state_t state = LED_MAX_STATE;
    /* Check if the LED exists or not */
    if(id < LED_MAX_ID)
    {
        /* Get the LED state */
        state = LEDs_CFG[id].state;
    }
    else
    {
        /* Do Nothing */
    }
    return state;
}

void LED_update(void);
