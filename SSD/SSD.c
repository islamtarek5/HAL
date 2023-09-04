/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-09-03 13:29:38                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-09-04 11:22:08                              *
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
 * @brief Segments shifting
*/
#define SEG_A_SHIFT     0U
#define SEG_B_SHIFT     1U
#define SEG_C_SHIFT     2U
#define SEG_D_SHIFT     3U
#define SEG_E_SHIFT     4U
#define SEG_F_SHIFT     5U
#define SEG_G_SHIFT     6U

/**
 * @brief Segment Mask
*/
#define SEG_Mask        0x01U

/**
 * @brief SSD Initial Value in case that initial state was ON and can be used as clear value.
*/
#define SSD_INITIAL_VALUE   0U

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

/**
 * @section Static Function Prototype.
*/

static void SSD_control_segments(ssd_id_t , uint8_t);


/**
 * @section Static Function Implementation.
*/

/**
 * @brief This API is used to control SSD segments and drive them with the right value.
 * @param id The ID of SSD whose segments will be controlled.
 * @param symbol The symbol that will be displayed on the SSD.
 */
static void SSD_control_segments(ssd_id_t id, uint8_t symbol)
{
    /* Control Segments' levels depending on the symbol */
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_A_PORT, SSD_SEGMENT_A_PIN, (((symbol >> SEG_A_SHIFT) & SEG_Mask) ^ SSDs_CFG[id].type));
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_B_PORT, SSD_SEGMENT_B_PIN, (((symbol >> SEG_B_SHIFT) & SEG_Mask) ^ SSDs_CFG[id].type));
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_C_PORT, SSD_SEGMENT_C_PIN, (((symbol >> SEG_C_SHIFT) & SEG_Mask) ^ SSDs_CFG[id].type));
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_D_PORT, SSD_SEGMENT_D_PIN, (((symbol >> SEG_D_SHIFT) & SEG_Mask) ^ SSDs_CFG[id].type));
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_E_PORT, SSD_SEGMENT_E_PIN, (((symbol >> SEG_E_SHIFT) & SEG_Mask) ^ SSDs_CFG[id].type));
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_F_PORT, SSD_SEGMENT_F_PIN, (((symbol >> SEG_F_SHIFT) & SEG_Mask) ^ SSDs_CFG[id].type));
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_G_PORT, SSD_SEGMENT_G_PIN, (((symbol >> SEG_G_SHIFT) & SEG_Mask) ^ SSDs_CFG[id].type));
}

/**
 * @brief This API is used to Initialize SSD Pins and SSD Segments' Pins as output.
 */
void SSD_init(void)
{
    uint8_t ssd = FIRST_SSD;

    /* Initialize Segements' Pins as output */
    MCAL_GPIO_set_pin_mode(SSD_SEGMENT_A_PORT, SSD_SEGMENT_A_PIN, MCAL_PIN_OUTPUT);
    MCAL_GPIO_set_pin_mode(SSD_SEGMENT_B_PORT, SSD_SEGMENT_B_PIN, MCAL_PIN_OUTPUT);
    MCAL_GPIO_set_pin_mode(SSD_SEGMENT_C_PORT, SSD_SEGMENT_C_PIN, MCAL_PIN_OUTPUT);
    MCAL_GPIO_set_pin_mode(SSD_SEGMENT_D_PORT, SSD_SEGMENT_D_PIN, MCAL_PIN_OUTPUT);
    MCAL_GPIO_set_pin_mode(SSD_SEGMENT_E_PORT, SSD_SEGMENT_E_PIN, MCAL_PIN_OUTPUT);
    MCAL_GPIO_set_pin_mode(SSD_SEGMENT_F_PORT, SSD_SEGMENT_F_PIN, MCAL_PIN_OUTPUT);
    MCAL_GPIO_set_pin_mode(SSD_SEGMENT_G_PORT, SSD_SEGMENT_G_PIN, MCAL_PIN_OUTPUT);

    /* Initialize SSD Pins as output and initialize their states */
    for(ssd = FIRST_SSD; ssd < SSD_MAX_ID; ssd++)
    {
        /* Set SSD Pins as output */
        MCAL_GPIO_set_pin_mode(SSDs_CFG[ssd].port, SSDs_CFG[ssd].pin, MCAL_PIN_OUTPUT);
        /* Control Segments By initial Value */
        SSD_control_segments(ssd, SSD_INITIAL_VALUE);
        /* Set SSD level */
        MCAL_GPIO_set_pin_level(SSDs_CFG[ssd].port, SSDs_CFG[ssd].pin, (SSDs_CFG[ssd].type ^ SSDs_CFG[ssd].state));
    }
}

void SSD_set_symbol         (ssd_id_t, ssd_symbol_t);
void SSD_set_number         (ssd_id_t, uint16_t);
void SSD_clear              (ssd_id_t);
void SSD_set_state          (ssd_id_t, ssd_state_t);
ssd_state_t SSD_get_state   (ssd_id_t);
void SSD_update             (void);
