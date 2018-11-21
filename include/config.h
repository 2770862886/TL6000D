#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/twi.h>
#include <util/delay.h>

typedef char int8;
typedef unsigned char uint8;
typedef int int16;
typedef unsigned int uint16;
typedef long int32;
typedef unsigned long uint32;

#define BIT(x)  (1<<(x))
#define NOP()   asm("nop")
#define WDR()   asm("wdr")

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#define UART_BAUD_RATE  9600
#define UBRR_VALUE      (((F_CPU / (UART_BAUD_RATE * 16UL))) - 1)

#define FCLK_IO         (F_CPU)
#define TIMER0_TICK     0.01
#define TIMER0_DATA     (FCLK_IO*TIMER0_TICK/1024)

#include "build_config.h"
#include "const.h"
#include "utils.h"
#include "lcd_st7565_driver.h"
#include "board_func.h"
#include "icc_card.h"
#include "strings.h"
#include "func_wrapper.h"
