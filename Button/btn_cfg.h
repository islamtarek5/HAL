/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-08-30 14:32:04                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-12-16 17:33:17                              *
 * @FilePath              : btn_cfg.h                                        *
 ****************************************************************************/

#ifndef BTN_BTN_CFG_H_
#define BTN_BTN_CFG_H_

/**
 * @section Definitions 
*/

/**
 * @brief Long Press cycles.
 * @note Number of cycles = long press time (in ms) / button main cycle (in ms).
 * @example if long press time is 2s (2000 ms) and button main cycle is 20 ms then long press cycles = 100.
*/
#define LONG_PRESS_CYCLES     100U  


/**
 * @section typedefs
 */

/**
 * @brief BTN ID
 * @note This Enum will contain the BTNs' IDs in project.
 * !note BTN_Max_ID must not deleted as it's used in code.
 */
typedef enum
{
    // TODO: Add BTNs' IDs
    BTN_MAX_ID
}btn_id_t;

#endif