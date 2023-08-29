/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-08-28 15:06:37                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-08-29 11:17:32                              *
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

void LED_init(void);
void LED_set_state(led_id_t, led_state_t);
led_state_t LED_get_state(led_id_t);
void LED_update(void);
