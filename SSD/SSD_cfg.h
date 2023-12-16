/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-09-03 13:29:00                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-09-03 17:57:39                              *
 * @FilePath              : SSD_cfg.h                                        *
 ****************************************************************************/

#ifndef SSD_SSD_CFG_H_
#define SSD_SSD_CFG_H_

/**
 * @section Definitions
*/

/**
 * @brief SSD Segments Porting
 * @note Configure Each segment Port and Pin.
 * !note: Names used must not be changes as they are used in code.
*/

//* Segment A
#define SSD_SEGMENT_A_PORT  MCAL_PORT_D
#define SSD_SEGMENT_A_PIN   MCAL_PIN_0 
//* Segment B
#define SSD_SEGMENT_B_PORT  MCAL_PORT_D
#define SSD_SEGMENT_B_PIN   MCAL_PIN_1 
//* Segment C
#define SSD_SEGMENT_C_PORT  MCAL_PORT_D
#define SSD_SEGMENT_C_PIN   MCAL_PIN_2 
//* Segment D
#define SSD_SEGMENT_D_PORT  MCAL_PORT_D
#define SSD_SEGMENT_D_PIN   MCAL_PIN_3 
//* Segment E
#define SSD_SEGMENT_E_PORT  MCAL_PORT_D
#define SSD_SEGMENT_E_PIN   MCAL_PIN_4 
//* Segment F
#define SSD_SEGMENT_F_PORT  MCAL_PORT_D
#define SSD_SEGMENT_F_PIN   MCAL_PIN_5 
//* Segment G
#define SSD_SEGMENT_G_PORT  MCAL_PORT_D
#define SSD_SEGMENT_G_PIN   MCAL_PIN_6 


/**
 * @section typedefs
 */

/**
 * @brief SSD ID
 * @note This Enum will contain the SSDs' IDs in project.
 * !note SSD_Max_ID must not deleted as it's used in code.
 */
typedef enum
{
    // TODO: Add SSDs' IDs
    SSD_MAX_ID
}ssd_id_t;

#endif