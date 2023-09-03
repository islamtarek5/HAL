/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-09-03 13:29:38                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-09-03 17:38:14                              *
 * @FilePath              : SSD.c                                            *
 ****************************************************************************/

/**
 * @section Includes
 */

#include "SSD.h"


/**
 * @section Definitions
 */

/**
 * @brief SSD Definitions
*/
#define FIRST_SSD       0U
#define SSD_MAX_DIGIT   9U

/**
 * @section External Global Variables
 */

/**
 * @brief SSD configuration Array
 */
extern Ssd_S SSDs_CFG[SSD_MAX_ID];


/**
 * @section Static Global Variables
 */

/**
 * @brief SSD Digits Array (Cathode Type)
 */
static uint8_t SSD_Digits[SSD_MAX_DIGIT] =
{
    0x3FU, /* 0 */
    0x06U, /* 1 */
    0x5BU, /* 2 */
    0x4FU, /* 3 */
    0X66U, /* 4 */
    0X6DU, /* 5 */
    0x7DU, /* 6 */
    0x07U, /* 7 */
    0x7FU, /* 8 */
    0x6FU  /* 9 */
};

/**
 * @brief SSD Symbols Array (Cathode Type)
 */
static uint8_t SSD_Symbols[SSD_MAX_SYMBOL]=
{
    0x77U,  /* A */
    0x7CU,  /* b */
    0X39U,  /* C */
    0X5EU,  /* d */
    0X79U,  /* E */
    0X71U,  /* F */
    0X3DU,  /* G */
    0X76U,  /* H */
    0X30U,  /* I */
    0X1FU,  /* J */
    0X38U,  /* L */
    0X37U,  /* n */
    0X3FU,  /* O */
    0X73U,  /* P */
    0X67U,  /* q */
    0X70U,  /* r */
    0X6DU,  /* S */
    0X78U,  /* t */
    0X3EU,  /* U */
    0X6EU   /* y */
};

void SSD_init               (void);
void SSD_set_symbol         (ssd_id_t, ssd_symbol_t);
void SSD_set_number         (ssd_id_t, uint16_t);
void SSD_clear              (ssd_id_t);
void SSD_set_state          (ssd_id_t, ssd_state_t);
ssd_state_t SSD_get_state   (ssd_id_t);
void SSD_update             (void);
