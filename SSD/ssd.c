/*********************************************************************************************************************************************/
/*                                                          Author      : Islam Tarek                                                        */
/*                                                          SW Module   : SSD                                                                */
/*                                                          Last Update : 10 / 8 /2022                                                       */
/*********************************************************************************************************************************************/
/* Includes */
#include "ssd.h"
#include "ssd_const.h"

/* Global Variables */

/**
 * @brief exists in proj_config.c file
 */
extern ssd_t SSDS[SSD_MAX];
static const uint8_t SSD_DIGITS[DIGITS] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x00};
static uint8_t NUMBER_DIGITS[SSD_MAX] ={0};
const uint8_t SSD_LAST  = SSD_MAX - 1;

/* Static Functions */

static void ssd_control(ssd_id_t id, ssd_state_t state);
static void ssd_set_segments(ssd_id_t id);

/**
 * @brief This function is used to set segments with their expected output
 * @param id  The ID of the SSD which its segments will be set
 */
static void ssd_set_segments(ssd_id_t id)
{
    if(SSDS[id].ssd_type == COMMON_ANODE)
    {
        mcal_gpio_set_pin_level(A_SEGMENT_PORT, A_SEGMENT_PIN, !((NUMBER_DIGITS[id]>> A_SEGMENT) & DE_MASK));
        mcal_gpio_set_pin_level(B_SEGMENT_PORT, B_SEGMENT_PIN, !((NUMBER_DIGITS[id]>> B_SEGMENT) & DE_MASK));
        mcal_gpio_set_pin_level(C_SEGMENT_PORT, C_SEGMENT_PIN, !((NUMBER_DIGITS[id]>> C_SEGMENT) & DE_MASK));
        mcal_gpio_set_pin_level(D_SEGMENT_PORT, D_SEGMENT_PIN, !((NUMBER_DIGITS[id]>> D_SEGMENT) & DE_MASK));
        mcal_gpio_set_pin_level(E_SEGMENT_PORT, E_SEGMENT_PIN, !((NUMBER_DIGITS[id]>> E_SEGMENT) & DE_MASK));
        mcal_gpio_set_pin_level(F_SEGMENT_PORT, F_SEGMENT_PIN, !((NUMBER_DIGITS[id]>> F_SEGMENT) & DE_MASK));
        mcal_gpio_set_pin_level(G_SEGMENT_PORT, G_SEGMENT_PIN, !((NUMBER_DIGITS[id]>> G_SEGMENT) & DE_MASK));
    }
    else if(SSDS[id].ssd_type == COMMON_CATHODE)
    {
        mcal_gpio_set_pin_level(A_SEGMENT_PORT, A_SEGMENT_PIN, ((NUMBER_DIGITS[id]>> A_SEGMENT) & DE_MASK));
        mcal_gpio_set_pin_level(B_SEGMENT_PORT, B_SEGMENT_PIN, ((NUMBER_DIGITS[id]>> B_SEGMENT) & DE_MASK));
        mcal_gpio_set_pin_level(C_SEGMENT_PORT, C_SEGMENT_PIN, ((NUMBER_DIGITS[id]>> C_SEGMENT) & DE_MASK));
        mcal_gpio_set_pin_level(D_SEGMENT_PORT, D_SEGMENT_PIN, ((NUMBER_DIGITS[id]>> D_SEGMENT) & DE_MASK));
        mcal_gpio_set_pin_level(E_SEGMENT_PORT, E_SEGMENT_PIN, ((NUMBER_DIGITS[id]>> E_SEGMENT) & DE_MASK));
        mcal_gpio_set_pin_level(F_SEGMENT_PORT, F_SEGMENT_PIN, ((NUMBER_DIGITS[id]>> F_SEGMENT) & DE_MASK));
        mcal_gpio_set_pin_level(G_SEGMENT_PORT, G_SEGMENT_PIN, ((NUMBER_DIGITS[id]>> G_SEGMENT) & DE_MASK));
    }
}

/**
 * @brief This function is used to control the state of SSD depending on Type of SSD and transistor type (if existed)
 * @param id The ID of the SSD which its state will be controlled
 * @param state The state of SSD (SSD_ON or SSD_OFF)
 */
static void ssd_control(ssd_id_t id, ssd_state_t state)
{
    switch (state)
    {
    case SSD_ON:
        if(SSDS[id].ssd_transistor == PNP_TRANSISTOR)
            mcal_gpio_set_pin_level(SSDS[id].ssd_port, SSDS[id].ssd_pin, PIN_LOW);
        else if(SSDS[id].ssd_transistor == NPN_TRANSISTOR)
            mcal_gpio_set_pin_level(SSDS[id].ssd_port, SSDS[id].ssd_pin, PIN_HIGH);
        else if(SSDS[id].ssd_transistor == NO_TRANSISTOR)
        {
            if(SSDS[id].ssd_type == COMMON_ANODE)
                mcal_gpio_set_pin_level(SSDS[id].ssd_port, SSDS[id].ssd_pin, PIN_HIGH);
            else if(SSDS[id].ssd_type == COMMON_CATHODE)
                mcal_gpio_set_pin_level(SSDS[id].ssd_port, SSDS[id].ssd_pin, PIN_LOW);
        }
        break;
    case SSD_OFF:
        if(SSDS[id].ssd_transistor == PNP_TRANSISTOR)
        {
            mcal_gpio_set_pin_level(SSDS[id].ssd_port, SSDS[id].ssd_pin, PIN_HIGH);
        }
        else if(SSDS[id].ssd_transistor == NPN_TRANSISTOR)
        {
            mcal_gpio_set_pin_level(SSDS[id].ssd_port, SSDS[id].ssd_pin, PIN_LOW);
        }
        else if(SSDS[id].ssd_transistor == NO_TRANSISTOR)
        {
            if(SSDS[id].ssd_type == COMMON_ANODE)
                mcal_gpio_set_pin_level(SSDS[id].ssd_port, SSDS[id].ssd_pin, PIN_LOW);
            else if(SSDS[id].ssd_type == COMMON_CATHODE)
                mcal_gpio_set_pin_level(SSDS[id].ssd_port, SSDS[id].ssd_pin, PIN_HIGH);
        }
        break;
    }
}
/**
 * @brief This API is used to initialize direction of segments and control pins of SSDs
 */
void ssd_init(void)
{
    uint8_t ssd;
    mcal_gpio_set_pin_direction(A_SEGMENT_PORT, A_SEGMENT_PIN, PIN_OUTPUT);
    mcal_gpio_set_pin_direction(B_SEGMENT_PORT, B_SEGMENT_PIN, PIN_OUTPUT);
    mcal_gpio_set_pin_direction(C_SEGMENT_PORT, C_SEGMENT_PIN, PIN_OUTPUT);
    mcal_gpio_set_pin_direction(D_SEGMENT_PORT, D_SEGMENT_PIN, PIN_OUTPUT);
    mcal_gpio_set_pin_direction(E_SEGMENT_PORT, E_SEGMENT_PIN, PIN_OUTPUT);
    mcal_gpio_set_pin_direction(F_SEGMENT_PORT, F_SEGMENT_PIN, PIN_OUTPUT);
    mcal_gpio_set_pin_direction(G_SEGMENT_PORT, G_SEGMENT_PIN, PIN_OUTPUT);
    for(ssd = SSD_FIRST; ssd < SSD_MAX; ssd++)
    {
        mcal_gpio_set_pin_direction(SSDS[ssd].ssd_port, SSDS[ssd].ssd_pin, PIN_OUTPUT);
        ssd_control(SSDS[ssd].ssd_id, SSDS[ssd].ssd_state);
    }
}
/**
 * @brief This API is used to set the state of a chosen SSD
 * @param id The ID of the SSD which its state will be set
 * @param state The state of SSD (SSD_ON or SSD_OFF)
 */
void ssd_set_state(ssd_id_t id, ssd_state_t state)
{
    if(id < SSD_MAX)
        SSDS[id].ssd_state = state;
}
/**
 * @brief This API is used to get the state of chosen SSD if it's ON or OFF
 * @param id The ID of the SSD which its state will be gotten
 * @return the state of the chosen SSD (SSD_ON or SSD_OFF) 
 */
ssd_state_t ssd_get_state(ssd_id_t id)
{
    return SSDS[id].ssd_state;
}
/**
 * @brief This API is used to set the number that will be displayed on SSDs
 * @param ones_id The ID of the first SSD from which display will start the ones SSD
 * @param number The number that will be displayed on SSDs
 * @example if we want to display 1234 and we have 4 SSDS then we will use API as: ssd_set_number(SSD_1, 1234) where SSD_1 is the most right SSD
 */
void ssd_set_number(ssd_id_t ones_id, uint16_t number)
{
    while((number >= NUMBER_END) && (ones_id < SSD_MAX))
    {
        ssd_set_symbol(ones_id++, (number % NUMBER_DIVIDOR));
        number /= NUMBER_DIVIDOR;
    }
}
/**
 * @brief This API is used to set a symbol that will be displayed on chosen SSD
 * @param id The ID of the SSD which will be used to display symbol
 * @param symbol The symbol that will be displayed (may be a digit or character(not supported yet))
 */
void ssd_set_symbol(ssd_id_t id, uint8_t symbol)
{
    NUMBER_DIGITS[id] = SSD_DIGITS[symbol];
}
/**
 * @brief This API is responsible for running SSDs
 */
void ssd_update(void)
{
    /* Timing characterstics will be added */
    static uint8_t current_ssd = SSD_FIRST;
    ssd_control(current_ssd, SSD_OFF);
    if(current_ssd == SSD_LAST)
    {
        current_ssd = SSD_FIRST;
    } 
    else
    {
        current_ssd ++;
    }
    ssd_set_segments(current_ssd);
    ssd_control(current_ssd, SSD_ON);
}
/**
 * @brief This API is used to clear SSDs
 */
void ssd_clear(void)
{
    uint8_t ssd;
    for(ssd = SSD_FIRST; ssd < SSD_MAX; ssd++)
    {
        ssd_set_symbol(ssd, SSD_CLEAR);
    }
}