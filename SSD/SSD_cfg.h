/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-09-03 13:29:00                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-09-03 15:26:29                              *
 * @FilePath              : SSD_cfg.h                                        *
 ****************************************************************************/

#ifndef SSD_SSD_CFG_H_
#define SSD_SSD_CFG_H_

/**
 * @section Defnitions
*/

/**
 * @brief SSD Segments Porting
 * @note Configure Each segment Port and Pin.
 * !note: Names used must not be changes as they are used in code.
*/

//* Segment A
#define SSD_SEGMENT_A_PORT 
#define SSD_SEGMENT_A_PIN
//* Segment B
#define SSD_SEGMENT_B_PORT      
#define SSD_SEGMENT_B_PIN
//* Segment C
#define SSD_SEGMENT_C_PORT      
#define SSD_SEGMENT_C_PIN
//* Segment D
#define SSD_SEGMENT_D_PORT      
#define SSD_SEGMENT_D_PIN
//* Segment E
#define SSD_SEGMENT_E_PORT      
#define SSD_SEGMENT_E_PIN
//* Segment F
#define SSD_SEGMENT_F_PORT      
#define SSD_SEGMENT_F_PIN
//* Segment G
#define SSD_SEGMENT_G_PORT      
#define SSD_SEGMENT_G_PIN


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