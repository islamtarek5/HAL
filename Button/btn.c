/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-08-30 14:32:12                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-09-03 13:25:38                              *
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
 * @brief Button Status Mask
 */

#define BTN_STATUS_MASK     0x01U

/**
 * @brief Long Cycles
*/
#define ZERO_LONG_CYCLES    0U


/**
 * @section Typedefs
*/

typedef uint8_t btn_status_t;


/**
 * @section External Global Variables
 */

extern btn_S BTNs_CFG[BTN_MAX_ID];

/**
 * @section Static Global Variables
*/

/**
 * @brief Long Press Cycles 
 */

static uint8_t long_press_cycles  = ZERO_LONG_CYCLES;

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

/**
 * @brief This API is used to get the state of the button.
 * @param id The ID of the button whose state will be got.
 * @return The state of the button (BTN_RELEASED, BTN_PREPRESSED, BTN_SHORT_PRESSED, BTN_LONG_PRESSED or BTN_PRERELEASED).
 */
btn_state_t BTN_get_state(btn_id_t id)
{
    btn_state_t state = BTN_MAX_STATE;
    /* Check if the button ID exists or not */
    if(id < BTN_MAX_ID)
    {
        /* Get the state of the given button */
        state = BTNs_CFG[id].state;
    }
    else
    {
        /* Do Nothing */
    }

    /* Return the state of the button */
    return state;
}

/**
 * @brief This API is used to update button state in way that overcomes debouncing. 
 */
void BTN_update(void)
{
    uint8_t pin_level = MCAL_PIN_LOW;
    btn_status_t status = BTN_IS_RELEASED;
    uint8_t btn = FIRST_BTN;

    /* Loop for buttons to update their states */
    for(btn = FIRST_BTN; btn < BTN_MAX_ID; btn++)
    {
        /* Get the Pin Value of the button */
        MCAL_GPIO_get_pin_level(BTNs_CFG[btn].port, BTNs_CFG[btn].pin, &pin_level);
        
        /* Get the status of the Button (Pressed or Released) */
        status = (pin_level ^ BTNs_CFG[btn].connection) & BTN_STATUS_MASK;

        /* Update Push Button state */
        switch (BTNs_CFG[btn].state)
        {
        case BTN_RELEASED:
        {
            if(status == BTN_IS_PRESSED)
            {
                /* Update state to Pre-Pressed state */
                BTNs_CFG[btn].state = BTN_PREPRESSED;
            }
            else if(status == BTN_IS_RELEASED)
            {
                /* Keep state as Released state */
                BTNs_CFG[btn].state = BTN_RELEASED; 
            }
            else
            {
                /* Do Nothing */
            }

            break;
        }
        case BTN_PREPRESSED:
        {
            if(status == BTN_IS_PRESSED)
            {
                /* Update state to short pressed state */
                BTNs_CFG[btn].state = BTN_SHORT_PRESSED;
                /* Update number of long press cycles */
                long_press_cycles ++;
            }
            else if(status == BTN_IS_RELEASED)
            {
                /* Update state to pre-released state */
                BTNs_CFG[btn].state = BTN_PRERELEASED; 
            }
            else
            {
                /* Do Nothing */
            }

            break;
        }
        case BTN_SHORT_PRESSED:
        {
            if(status == BTN_IS_PRESSED)
            {
                if(long_press_cycles >= LONG_PRESS_CYCLES)
                {
                    /* Update state to Long Pressed state */
                    BTNs_CFG[btn].state = BTN_LONG_PRESSED;
                    /* Reset number of long press cycles */
                    long_press_cycles = ZERO_LONG_CYCLES;
                }
                else
                {
                    /* Increment number of long cycles */
                    long_press_cycles ++;
                    /* Keep state as short Pressed state */
                    BTNs_CFG[btn].state = BTN_SHORT_PRESSED;
                }
            }
            else if(status == BTN_IS_RELEASED)
            {
                /* Reset number of long press cycles */
                long_press_cycles = ZERO_LONG_CYCLES;
                /* Update state to pre-released state */
                BTNs_CFG[btn].state = BTN_PRERELEASED; 
            }
            else
            {
                /* Do Nothing */
            }

            break;
        }
        case BTN_LONG_PRESSED:
        {
            if(status == BTN_IS_PRESSED)
            {
                /* Keep state as long pressed state */
                BTNs_CFG[btn].state = BTN_LONG_PRESSED;
            }
            else if(status == BTN_IS_RELEASED)
            {
                /* Update state to pre-released state */
                BTNs_CFG[btn].state = BTN_PRERELEASED; 
            }
            else
            {
                /* Do Nothing */
            }

            break;
        }
        case BTN_PRERELEASED:
        {
            if(status == BTN_IS_PRESSED)
            {
                /* Update state to pre-pressed state */
                BTNs_CFG[btn].state = BTN_PREPRESSED;
            }
            else if(status == BTN_IS_RELEASED)
            {
                /* Update state to Released state */
                BTNs_CFG[btn].state = BTN_RELEASED; 
            }
            else
            {
                /* Do Nothing */
            }

            break;
        }
        default:
            /* Do Nothing */
            break;
        }    
    }
}

