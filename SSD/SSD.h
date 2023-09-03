/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-09-03 13:30:19                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-09-03 15:20:26                              *
 * @FilePath              : SSD.h                                            *
 ****************************************************************************/

#ifndef SSD_SSD_H_
#define SSD_SSD_H_

/**
 * @section Includes
 */

#include "../MCAL/MCAL.h"
#include "SSD_cfg.h"


/**
 * @section Typedefs
 */

/**
 * @brief SSD Port
 */
typedef mcal_port_t ssd_port_t;

/**
 * @brief SSD Pin
 */
typedef mcal_pin_t ssd_pin_t;

/**
 * @brief SSD Symboles
 */

typedef enum
{
    SSD_SYMBOL_A   = (uint8_t)0,
    SSD_SYMBOL_b               ,
    SSD_SYMBOL_C               ,
    SSD_SYMBOL_d               ,
    SSD_SYMBOL_E               ,
    SSD_SYMBOL_F               ,
    SSD_SYMBOL_G               ,
    SSD_SYMBOL_H               ,
    SSD_SYMBOL_I               ,
    SSD_SYMBOL_J               ,
    SSD_SYMBOL_L               ,
    SSD_SYMBOL_n               ,
    SSD_SYMBOL_O               ,
    SSD_SYMBOL_P               ,
    SSD_SYMBOL_q               ,
    SSD_SYMBOL_r               ,
    SSD_SYMBOL_S               ,
    SSD_SYMBOL_t               ,
    SSD_SYMBOL_U               ,
    SSD_SYMBOL_y               ,
    SSD_MAX_SYMBOL
}ssd_symbol_t;

/**
 * @brief SSD state
 * !note: These Values must not be changed.
 */
typedef enum
{
    SSD_OFF = (uint8_t)0,
    SSD_ON              ,
    SSD_MAX_STATE
}ssd_state_t;

/**
 * @brief SSD type
 * !note: These Values must not be changed
 */
typedef enum
{
    SSD_CATHODE = (uint8_t)0,
    SSD_ANODE               ,
    SSD_MAX_TYPE
}ssd_type_t;

/**
 * @brief SSD Structure
 */
typedef struct 
{
    ssd_id_t    id;
    ssd_port_t  port;
    ssd_pin_t   pin;
    ssd_type_t  type;
    ssd_state_t state;
}Ssd_S;

/**
 * @section APIs
 */

void SSD_init               (void);
void SSD_set_symbol         (ssd_id_t, ssd_symbol_t);
void SSD_set_number         (ssd_id_t, uint16_t);
void SSD_set_state          (ssd_id_t, ssd_state_t);
ssd_state_t SSD_get_state   (ssd_id_t);
void SSD_update             (void);

#endif