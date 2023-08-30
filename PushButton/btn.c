/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-08-30 14:32:12                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-08-30 18:07:10                              *
 * @FilePath              : btn.c                                            *
 ****************************************************************************/

/**
 * @section Includes
 */

#include "btn.h"


/**
 * @section Definitions
*/

/**
 * @brief First Button Definition
 */

#define FIRST_BTN           0U

/**
 * @brief Button Status
*/

#define BTN_IS_RELEASED     0U
#define BTN_IS_PRESSED      1U  


/**
 * @section Typedefs
*/

typedef uint8_t btn_status_t;


/**
 * @section External Global Variables
 */

extern btn_S BTNs_CFG[BTN_MAX_ID];


/**
 * @brief APIs Implementation
 */


/**
 * @brief This API is used to initialize the button Pin as Input.
 */
void BTN_init(void)
{
    uint8_t btn = FIRST_BTN;

    /* Loop for Button to Initialize them */
    for(btn = FIRST_BTN; btn < BTN_MAX_ID; btn++)
    {
        /* Initialize button Pins as Input */
        /* Check if the Button Connection is Internal or External */
        if((BTNs_CFG[btn].connection == BTN_EXT_PULL_UP) || (BTNs_CFG[btn].connection == BTN_EXT_PULL_DOWN))
        {
            /* Set Pin as floating Input */
            (void)MCAL_GPIO_set_pin_mode(BTNs_CFG[btn].port, BTNs_CFG[btn].pin, MCAL_PIN_INPUT_FLOATING);
        }
        else if(BTNs_CFG[btn].connection == BTN_INT_PULL_UP)
        {
            /* Set Pin as Pull-up Input */
            (void)MCAL_GPIO_set_pin_mode(BTNs_CFG[btn].port, BTNs_CFG[btn].pin, MCAL_PIN_INPUT_PULL_UP);
        }
        else if(BTNs_CFG[btn].connection == BTN_INT_PULL_DOWN)
        {
            /* Set Pin as Pull-up Input */
            (void)MCAL_GPIO_set_pin_mode(BTNs_CFG[btn].port, BTNs_CFG[btn].pin, MCAL_PIN_INPUT_PULL_DOWN);
        }
        else
        {
            /* Do Nothing */
        }
    }
}

/**
 * @brief This API is used to set button state. It Can be used for Dubgging.
 * @param id The ID of the button whose state will be set.
 * @param state The state which will be set to button (BTN_RELEASED, BTN_PREPRESSED, BTN_SHORT_PRESSED, BTN_LONG_PRESSED or BTN_PRERELEASED).
 */
void BTN_set_state(btn_id_t id, btn_state_t state)
{
    /* Check if the button ID and button state exist or not */
    if((id < BTN_MAX_ID)  && (state < BTN_MAX_STATE))
    {
        /* Set the Button state */
        BTNs_CFG[id].state = state;
    }
    else
    {
        /* Do Nothing */
    }
}

btn_state_t BTN_get_state(btn_id_t);
void BTN_update(void);

