/*********************************************************************************************************************************************/
/*                                                          Author      : Islam Tarek                                                        */
/*                                                          SW Module   : LED                                                                */
/*                                                          Last Update : 13 / 7 /2022                                                       */
/*********************************************************************************************************************************************/

#ifndef LED_LED_H_
#define LED_LED_H_

/* Includes */
#include "../../mcal/MCAL_GPIO/mcal_gpio.h"
#include "../hal.h"

/* Definitions */

/* LED Direction */
typedef uint8_t led_direction_t;
#define LED_FORWARD         0
#define LED_REVERSE         1

/* LED State */
typedef uint8_t led_state_t;
#define LED_ON              0
#define LED_OFF             1
#define LED_TOG             2

/* LED Port */
typedef mcal_gpio_t led_port_t;

/* LED pin */
typedef mcal_gpio_pin_t led_pin_t;

/* LED Structure */
typedef struct 
{
    led_id_t        led_id;
    led_port_t      led_port;
    led_pin_t       led_pin;
    led_direction_t led_direction;
    led_state_t     led_state;
}led_t;

/* APIs */
hal_err_t led_init      (led_id_t id);
hal_err_t led_set_state (led_id_t id, led_state_t state);
hal_err_t led_get_state (led_id_t id, led_state_t* state);
 
#endif 