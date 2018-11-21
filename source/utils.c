/*
 * utils.c
 *
 *  Created on: Oct 25, 2013
 *      Author: albert
 */
#include "config.h"

uint8 t_u8_1 = 0;
uint8 t_u8_2 = 0;
uint8 t_u8_3 = 0;
uint8 t_u8_4 = 0;

uint32 t_u32_1 = 0;
uint32 t_u32_2 = 0;
uint32 t_u32_3 = 0;
uint32 t_u32_4 = 0;

void display_number_u8(uint8 value, uint8 value1, uint8 value2, uint8 value3) {
    char str[8] = { 0 };
    char str1[8] = { 0 };
    char str2[8] = { 0 };
    char str3[8] = { 0 };

    utoa(value, str, 10);
    utoa(value1, str1, 10);
    utoa(value2, str2, 10);
    utoa(value3, str3, 10);

    display_clear_2N();

    lcd_display_string(str, 2, LCD_START_COLUMN, FONT1616);
    lcd_display_string(str1, 2, LCD_START_COLUMN + 48, FONT1616);
    lcd_display_string(str2, 4, LCD_START_COLUMN, FONT1616);
    lcd_display_string(str3, 4, LCD_START_COLUMN + 48, FONT1616);
}

void display_number_u32(uint32 value, uint32 value1, uint32 value2, uint32 value3) {
    char str[8] = { 0 };
    char str1[8] = { 0 };
    char str2[8] = { 0 };
    char str3[8] = { 0 };

    utoa(value, str, 10);
    utoa(value1, str1, 10);
    utoa(value2, str2, 10);
    utoa(value3, str3, 10);

    display_clear_2N();

    lcd_display_string(str, 2, LCD_START_COLUMN, FONT1616);
    lcd_display_string(str1, 2, LCD_START_COLUMN + 48, FONT1616);
    lcd_display_string(str2, 4, LCD_START_COLUMN, FONT1616);
    lcd_display_string(str3, 4, LCD_START_COLUMN + 48, FONT1616);
}

