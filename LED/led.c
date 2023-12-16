/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-08-28 15:06:37                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-12-16 16:53:01                              *
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
#define LED_STATE_IS_NOT_INITIAL 0U
#define LED_STATE_IS_INITIAL     1U

/**
 * @section External Global Variables
 */

extern Led_S LEDs_CFG[LED_MAX_ID];

/**
 * @section Static Global Variables
*/

/**
 * @brief This Variable is used to indicate the initial state.
*/
static uint8_t LED_INITIAL_STATE_FLAG = LED_STATE_IS_NOT_INITIAL;

/**
 * @section Static function prototype.
 */

static void LED_control_state(led_id_t);


/**
 * @section Static function Implementation
 */

/**
 * @brief This API is used to control LED state and drive MCU Pin with suitable output to achieve required state.
 * @param id The ID of the led whose state will be controlled.
 */
static void LED_control_state(led_id_t id)
{
    /* Check if the LED state is toggle or not */
    if(LEDs_CFG[id].state == LED_TOG)
    {
        if(LED_INITIAL_STATE_FLAG == LED_STATE_IS_INITIAL)
        {
            /* Update GPIO Pin level to OFF state */
            (void)MCAL_GPIO_set_pin_level(LEDs_CFG[id].port, LEDs_CFG[id].pin, (LEDs_CFG[id].bias ^ MCAL_PIN_LOW));
            /* Reset LED Initial State flag */
            LED_INITIAL_STATE_FLAG = LED_STATE_IS_NOT_INITIAL;
            
        }
        else
        {
            /* Do Nothing */
        }
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
 * @brief This API is used to Initialize MCU Pins that are connected to LEDs as output and to initialize LEDs State.
 */
void LED_init(void)
{
    /* Loop for LEDs to initialize them */
    uint8_t led = FIRST_LED;
    for(led = FIRST_LED; led < LED_MAX_ID; led ++)
    {
        /* Initialize LEDs Pins as output */
        (void)MCAL_GPIO_set_pin_mode(LEDs_CFG[led].port, LEDs_CFG[led].pin, MCAL_PIN_OUTPUT);
        /* Check if the state exists or not and that initial state isn't toggle */
        if(LEDs_CFG[led].state < LED_MAX_STATE)
        {
            /* Check the LED state */
            if(LEDs_CFG[led].state == LED_TOG)
            {
                /* Set LED Initial state flag */
                LED_INITIAL_STATE_FLAG = LED_STATE_IS_INITIAL;
            }
            else
            {
                /* Do Nothing */
            }
            /* Control LED State */
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

/**
 * @brief This API is used to update the LED state and drive MCU output to achieve the LED state.
 */
void LED_update(void)
{
    uint8_t led = FIRST_LED;
    /* Loop for LEDs to update their states */
    for(led = FIRST_LED; led < LED_MAX_ID; led ++)
    {
        /* Check if the LED state exists or not */
        if(LEDs_CFG[led].state < LED_MAX_STATE)
        {
            /* Control LED state */
            LED_control_state(led);
        }
        else
        {
            /* Do Nothing */
        }
    }
}