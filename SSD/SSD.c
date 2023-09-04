/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-09-03 13:29:38                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-09-04 12:40:46                              *
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
 * @brief SSD clear value.
*/
#define SSD_CLEAR_VALUE   0U

/**
 * @brief Division Factor
*/
#define DIVIDE_BY_10    10U

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
 * @brief SSDs Symbols or Digits
 */
static uint8_t SSD_Value[SSD_MAX_ID] = {SSD_CLEAR_VALUE};


/**
 * @section Static Function Prototype.
*/

static void SSD_control_segments(ssd_id_t);


/**
 * @section Static Function Implementation.
*/

/**
 * @brief This API is used to control SSD segments and drive them with the right value.
 * @param id The ID of SSD whose segments will be controlled.
 */
static void SSD_control_segments(ssd_id_t id)
{
    /* Control Segments' levels depending on the symbol */
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_A_PORT, SSD_SEGMENT_A_PIN, (((SSD_Value[id] >> SEG_A_SHIFT) & SEG_Mask) ^ (SSDs_CFG[id].type)));
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_B_PORT, SSD_SEGMENT_B_PIN, (((SSD_Value[id] >> SEG_B_SHIFT) & SEG_Mask) ^ (SSDs_CFG[id].type)));
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_C_PORT, SSD_SEGMENT_C_PIN, (((SSD_Value[id] >> SEG_C_SHIFT) & SEG_Mask) ^ (SSDs_CFG[id].type)));
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_D_PORT, SSD_SEGMENT_D_PIN, (((SSD_Value[id] >> SEG_D_SHIFT) & SEG_Mask) ^ (SSDs_CFG[id].type)));
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_E_PORT, SSD_SEGMENT_E_PIN, (((SSD_Value[id] >> SEG_E_SHIFT) & SEG_Mask) ^ (SSDs_CFG[id].type)));
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_F_PORT, SSD_SEGMENT_F_PIN, (((SSD_Value[id] >> SEG_F_SHIFT) & SEG_Mask) ^ (SSDs_CFG[id].type)));
    MCAL_GPIO_set_pin_level(SSD_SEGMENT_G_PORT, SSD_SEGMENT_G_PIN, (((SSD_Value[id] >> SEG_G_SHIFT) & SEG_Mask) ^ (SSDs_CFG[id].type)));
}

/**
 * @section Implementation of APIs
*/

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
        MCAL_GPIO_set_pin_mode((SSDs_CFG[ssd].port), (SSDs_CFG[ssd].pin), MCAL_PIN_OUTPUT);
        /* Control Segments By initial Value */
        SSD_control_segments(ssd);
        /* Set SSD level */
        MCAL_GPIO_set_pin_level((SSDs_CFG[ssd].port), (SSDs_CFG[ssd].pin), ((SSDs_CFG[ssd].type) ^ (SSDs_CFG[ssd].state)));
    }
}

/**
 * @brief This API is used to set symbol to be displayed on SSD.
 * @param id The ID of SSD on which symbol will be displayed.
 * @param symbol The symbol that will displayed on SSD.
 */
void SSD_set_symbol(ssd_id_t id, ssd_symbol_t symbol)
{
    /* Check if the SSD and Symbol exist or not */
    if((id < SSD_MAX_ID) && (symbol < SSD_MAX_SYMBOL))
    {
        /* Set the given symbol to its SSD */
        SSD_Value[id] = SSD_Symbols[symbol];
    }
    else
    {
        /* Do Nothing */
    }
}

/**
 * @brief This API is used to set number that will be displayed on SSDs.
 * @param ones_id The ID of SSD that will be used as ones digit of the given number.
 * @param number The number that will be displayed on SSDs.
 */
void SSD_set_number(ssd_id_t ones_id, uint16_t number)
{
    /* Check if SSD exists or not */
    if(ones_id < SSD_MAX_ID)
    {
        do
        {
            /* Set Digit to  its SSD */
            SSD_Value[ones_id++] = SSD_Digits[(number % DIVIDE_BY_10)];
        
        } while ((number / DIVIDE_BY_10 != SSD_CLEAR_VALUE) && (ones_id < SSD_MAX_ID));
    }
    else
    {
        /* Do Nothing */
    }      
}

/**
 * @brief This API is used to clear SSD. 
 * @param id The ID of the SSD which will be cleared.
 */
void SSD_clear(ssd_id_t id)
{
    /* Check if the SSD exists or not */
    if(id < SSD_MAX_ID)
    {
        /* Set the clear value to the given SSD */
        SSD_Value[id] = SSD_CLEAR_VALUE;
    }
    else
    {
        /* Do Nothing */
    }
}

/**
 * @brief This API is used to set the state of SSD.
 * @param id The ID of the SSD whose state will be set.
 * @param state The to which the SSD will be set (SSD_OFF or SSD_ON).
 */
void SSD_set_state(ssd_id_t id, ssd_state_t state)
{
    /* Check if the SSD and state exist or not */
    if((id < SSD_MAX_ID) && (state < SSD_MAX_STATE))
    {
        /* Set the state of the given SSD */
        SSDs_CFG[id].state = state;
    }
    else
    {
        /* Do Nothing */
    }
}

/**
 * @brief This API is used to get the state of SSD.
 * @param id The ID whose state will be got.
 * @return The state of SSD (SSD_OFF or SSD_ON).
 */
ssd_state_t SSD_get_state(ssd_id_t id)
{
    ssd_state_t state = SSD_MAX_STATE;

    if(id < SSD_MAX_ID)
    {
        /* Get the state of the given SSD */
        state = (SSDs_CFG[id].state);
    }
    else
    {
        /* Do Nothing */
    }

    return state;    
}

void SSD_update             (void);
