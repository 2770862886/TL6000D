#ifndef _UTILS_H__
#define _UTILS_H__

typedef struct _bit_struct {
    unsigned bit0 :1;
    unsigned bit1 :1;
    unsigned bit2 :1;
    unsigned bit3 :1;
    unsigned bit4 :1;
    unsigned bit5 :1;
    unsigned bit6 :1;
    unsigned bit7 :1;
} Bit_Field_t;

#define GET_BIT(adr)   (*(( volatile Bit_Field_t * )(&adr)))

#define PA(n)           GET_BIT(PORTA).bit##n
#define PB(n)           GET_BIT(PORTB).bit##n
#define PC(n)           GET_BIT(PORTC).bit##n
#define PD(n)           GET_BIT(PORTD).bit##n

enum {
    LOG_FATAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_DEBUG,
    LOG_INFO
} DBG_LVL;

#if !defined(LOG_NO_DEBUG_INFO)
    #if LOG_DBG_LVL >= LOG_FATAL
        #define LOG_PRINT_FATAL(msg, arg...) printf("[FATAL] - %s\n", msg, ##arg)
    #else
        #define LOG_PRINT_FATAL(msg, arg...)
    #endif

    #if LOG_DBG_LVL >= LOG_ERROR
        #define LOG_PRINT_ERROR(msg, arg...) printf("[ERROR] - %s\n", msg, ##arg)
    #else
        #define LOG_PRINT_ERROR(msg, arg...)
    #endif

    #if LOG_DBG_LVL >= LOG_WARNING
        #define LOG_PRINT_WARNING(msg, arg...) printf("[WARNING] - %s\n", msg, ##arg)
    #else
        #define LOG_PRINT_WARNING(msg, arg...)
    #endif

    #if LOG_DBG_LVL >= LOG_DEBUG
        #define LOG_PRINT_DEBUG(msg, arg...) printf("[DEBUG] - %s\n", msg, ##arg)
    #else
        #define LOG_PRINT_DEBUG(msg, arg...)
    #endif

    #if LOG_DBG_LVL >= LOG_INFO
        #define LOG_PRINT_INFO(msg, arg...) printf("[INFO] - %s\n", msg, ##arg)
    #else
        #define LOG_PRINT_INFO(msg, arg...)
    #endif
#else
    #define LOG_PRINT_FATAL(msg, arg...)
    #define LOG_PRINT_ERROR(msg, arg...)
    #define LOG_PRINT_WARNING(msg, arg...)
    #define LOG_PRINT_DEBUG(msg, arg...)
    #define LOG_PRINT_INFO(msg, arg...)
#endif

extern uint8 t_u8_1;
extern uint8 t_u8_2;
extern uint8 t_u8_3;
extern uint8 t_u8_4;

extern uint32 t_u32_1;
extern uint32 t_u32_2;
extern uint32 t_u32_3;
extern uint32 t_u32_4;

void display_number_u8(uint8 value1, uint8 value2, uint8 value3, uint8 value4);
void display_number_u32(uint32 value1, uint32 value2, uint32 value3, uint32 value4);

#endif /* UTILS_H_ */
