/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-08-28 15:06:31                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-08-29 10:39:02                              *
 * @FilePath              : led.h                                            *
 ****************************************************************************/

#ifndef LED_LED_H_
#define LED_LED_H_

/**
 * @section Includes
 */

#include "../MCAL/MCAL.h"
#include "led_cfg.h"


/**
 * @section typedefs
 */

/**
 * @brief LED port
 */

typedef mcal_port_t led_port_t;

/**
 * @brief LED pin
 */
typedef mcal_pin_t led_pin_t;

/**
 * @brief LED state
 * !note : Theses Values must not be changed.
 */

typedef enum
{
    LED_OFF = (uint8_t) 0,
    LED_ON               ,
    LED_TOG              ,
    LED_MAX_STATE
}led_state_t;

/**
 * @brief LED Bias
 * !note : Theses Values must not be changed.
 */

typedef enum
{
    LED_FORWARD = (uint8_t) 0,
    LED_REVERSE              ,
    LED_MAX_BIAS     
}led_bias_t;

/**
 * @brief LED structure
 */

typedef struct 
{
    led_id_t    id;
    led_port_t  port;
    led_pin_t   pin;
    led_bias_t  bias;
    led_state_t state;
}Led_S;


/**
 * @section APIs
 */

void LED_init               (void);
void LED_set_state          (led_id_t, led_state_t);
led_state_t LED_get_state   (led_id_t);
void LED_update             (void);

#endif
