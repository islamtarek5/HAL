/*********************************************************************************************************************************************/
/*                                                          Author      : Islam Tarek                                                        */
/*                                                          SW Module   : SSD                                                                */
/*                                                          Last Update : 10 / 8 /2022                                                       */
/*********************************************************************************************************************************************/
#ifndef SSD_SSD_H_
#define SSD_SSD_H_

/* Includes */
#include "../../mcal/MCAL_GPIO/mcal_gpio.h"
#include "../hal.h"

/* Definitions */

/* SSD Timing characteristics */
#define SSD_FIRST_DELAY_MS   5
#define SSD_PERIOD_MS        5

/* SSD Type */
typedef uint8_t ssd_type_t;
#define COMMON_ANODE           0
#define COMMON_CATHODE         1

/* Transistor Type */
typedef uint8_t ssd_trans_t;
#define PNP_TRANSISTOR         0
#define NPN_TRANSISTOR         1
#define NO_TRANSISTOR          2

/* SSD State */
typedef uint8_t ssd_state_t;
#define SSD_ON              0
#define SSD_OFF             1

/* LED Port */
typedef mcal_gpio_t ssd_port_t;

/* LED pin */
typedef mcal_gpio_pin_t ssd_pin_t;

/* LED Structure */
typedef struct 
{
    ssd_id_t        ssd_id;
    ssd_port_t      ssd_port;
    ssd_pin_t       ssd_pin;
    ssd_type_t      ssd_type;
    ssd_state_t     ssd_state;
    ssd_trans_t     ssd_transistor;
}ssd_t;

/* APIs */

void ssd_init            (void);
void ssd_set_state       (ssd_id_t id, ssd_state_t state);
ssd_state_t ssd_get_state(ssd_id_t id);
void ssd_set_number      (ssd_id_t ones_id, uint16_t number);
void ssd_set_symbol      (ssd_id_t id, uint8_t symbol);
void ssd_update          (void);
void ssd_clear           (void);
 
#endif