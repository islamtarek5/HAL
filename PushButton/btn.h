/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-08-30 14:32:37                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-08-30 16:17:03                              *
 * @FilePath              : btn.h                                            *
 ****************************************************************************/

#ifndef BTN_BTN_H_
#define BTN_BTN_H_

/**
 * @section Includes
 */

#include "../MCAL/MCAL.h"
#include "btn_cfg.h"


/**
 * @section Typedefs
 */

/**
 * @brief BTN Port
 */

typedef mcal_port_t btn_port_t;

/**
 * @brief BTN Pin
 */

typedef mcal_pin_t btn_pin_t;

/**
 * @brief BTN State
 * !note: These Values must not be changed.
 */

typedef enum
{
    BTN_RELEASED = (uint8_t) 0,
    BTN_PREPRESSED            ,
    BTN_SHORT_PRESSED         ,
    BTN_LONG_PRESSED          ,
    BTN_PRERELEASED           ,
    BTN_MAX_STATE
}btn_state_t;

/**
 * @brief BTN Connection
 * !note: These Values must not be changed.
 */

typedef enum
{
    BTN_EXT_PULL_DOWN = (uint8_t) 0,
    BTN_EXT_PULL_UP                ,
    BTN_INT_PULL_DOWN              ,           
    BTN_INT_PULL_UP                ,
    BTN_MAX_CONNECTION
}btn_connection_t;

/**
 * @brief BTN Structure
 */

typedef struct 
{
    btn_id_t         id;
    btn_port_t       port;
    btn_pin_t        pin;
    btn_connection_t connection;
    btn_state_t      state;
}btn_S;


/**
 * @section APIs
 */

void BTN_init               (void);
void BTN_set_state          (btn_id_t, btn_state_t);
btn_state_t BTN_get_state   (btn_id_t);
void BTN_update             (void);

#endif