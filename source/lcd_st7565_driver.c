#include "config.h"
#include "font_library.h"

const uint16 FONT_LIB_SIZE = sizeof(HZ_Table) / sizeof(Hz1616_t);
const uint16 FONT_LIB_SIZE_2432 = sizeof(HZ_Table_2432) / sizeof(Hz2432_t);
const uint16 FONT_LIB_SIZE_2132 = sizeof(HZ_Table_2132) / sizeof(Hz2132_t);

/*
void write_data(uint8 data) {
    LCD_CS = 0;

    LCD_A0 = 1;
    LCD_RW = 0;
    LCD_EN = 1;
    LCD_DATA = data;
    _delay_us(10);
    LCD_EN = 0;

    LCD_CS = 1;
}

void write_cmd(uint8 cmd) {
    LCD_CS = 0;

    LCD_A0 = 0;
    LCD_RW = 0;
    LCD_EN = 1;
    LCD_DATA = cmd;
    _delay_us(10);
    LCD_EN = 0;

    LCD_CS = 1;
}
*/

void write_data(uint8 data) {
    uint8 i, temp;

    LCD_AO = 1;
    LCD_CS = 0;
    LCD_SCL = 0;

    for (i = 0; i < 8; i++) {
        LCD_SCL = 0;
        temp = data & 0x80;

        if (temp) {
            LCD_SDA = 1;
        } else {
            LCD_SDA = 0;
        }

        LCD_SCL = 1;

        data = data << 1;
    }
}

void write_cmd(uint8 cmd) {
    uint8 i, temp;

    LCD_AO = 0;
    LCD_CS = 0;
    LCD_SCL = 0;

    for (i = 0; i < 8; i++) {
        LCD_SCL = 0;
        temp = cmd & 0x80;

        if (temp) {
            LCD_SDA = 1;
        } else {
            LCD_SDA = 0;
        }

        LCD_SCL = 1;
        cmd = cmd << 1;
    }
}

void* search_library(const void *pLibrary, char* pChar, uint16 elemSize, uint16 libSize) {
    char charH, charL;
    uint16 index = 0;

    charH = *pChar;
    charL = *(pChar + 1);

    do {
        if (charH == pgm_read_byte(pLibrary) && charL == pgm_read_byte(pLibrary + 1))
            return (char *) (pLibrary + 2);
        pLibrary += elemSize;
    } while (index++ < libSize);

    return NULL;
}

/*
 * 0 : turn off screen
 * 1 : turn on screen
 */
void lcd_display_OnOff(uint8 On) {
    On &= 0x01;
    write_cmd(0xAE | On);
}

void lcd_power_control(uint8 Power) {
    Power &= 0x07;
    write_cmd(0x28 | Power);
}

void lcd_set_startLine(uint8 LineStart) {
    LineStart &= 0x3F;
    write_cmd(0x40 | LineStart);
}

void lcd_set_page_address(uint8 Page) {
    Page &= 0x0F;
    write_cmd(0xB0 | Page);
}

void lcd_set_column_address(uint8 Column) {
    write_cmd(((Column >> 4) | 0xF0) & 0x1F);
    write_cmd(Column & 0x0F);
}

void lcd_setV0_voltage_regulator(uint8 Ratio) {
    Ratio &= 0x07;
    write_cmd(0x20 | Ratio);
}

// Contrast Setting
void lcd_set_electronic_volume(uint8 Volume) {
    Volume &= 0x3F;
    write_cmd(0x81);
    write_cmd(Volume);
}

void lcd_reset() {
    LCD_RST = 0;
    _delay_ms(1);
    LCD_RST = 1;
}

void lcd_init(void) {
    // LCD_CS = 0;

    lcd_reset();
    _delay_us(50);

    // LCD Bias Setting
    write_cmd(0xA2);         // LCD Bias Set: 1/9 bias
    //LCD_WriteCMD(0xA3);       // LCD Bias Set: 1/7 bias
    //LCD_WriteCMD(0xE2);

    ////////////////////////////////////
    // ADC Setting
    // A1: Reverse  A0: Normal
    write_cmd(0xA0);

    ////////////////////////////////////
    // Common ouput mode
    // C8: Reverse  C0: Normal
    write_cmd(0xC8);

    _delay_us(50);

    // V5 Output Voltage
    lcd_setV0_voltage_regulator(0x04);
    _delay_us(50);

    lcd_set_electronic_volume(g_lcd_contrast);
    _delay_us(100);

    write_cmd(0xA2);
    //LCD_WriteCMD(0xA4);       // Display Normal
    //LCD_WriteCMD(0xA5);       // All point On
    _delay_us(50);

    ////////////////////////////////////
    // Display Direction Setting
    // A6: Normal  A7: Reverse
    write_cmd(0xA6);

    write_cmd(0x2B);
    _delay_us(50);

    //LCD_WriteCMD(0xAC);
    //LCD_WriteCMD(0x00);
    write_cmd(0x2E);
    _delay_us(50);

    lcd_power_control(0x07);
    lcd_display_OnOff(1);

    lcd_set_startLine(0x00);
}

void lcd_display_data(uint8 data, uint8 adrPage, uint8 adrColumn) {
    lcd_set_page_address(adrPage);
    lcd_set_column_address(adrColumn);
    for (; adrColumn < MAX_COLUMN; adrColumn++) {
        write_data(data);
    }
}

/*
 * clear the screen with specified data
 */
void lcd_clr(uint8 data) {
    uint8 adrPage, adrLaw;

    for (adrPage = 0; adrPage < MAX_PAGE; adrPage++) {
        lcd_set_page_address(adrPage);
        lcd_set_column_address(0);
        for (adrLaw = 0; adrLaw < MAX_COLUMN; adrLaw++) {
            write_data(data);
        }
    }
}

/*
 * display ASCII.
 */
void lcd_display_ASCII(char ascii, uint8 adrPage, uint8 adrColumn) {
    const uint8 *dptr;
    uint8 i;

    if (ascii < 0x20)
        ascii = 0x20;

    dptr = &ASCII[(ascii - 0x20) * 16];

    lcd_set_page_address(adrPage);
    lcd_set_column_address(adrColumn);
    for (i = 0; i < 8; i++) {
        write_data(pgm_read_byte(dptr ++));
    }

    lcd_set_page_address(adrPage + 1);
    lcd_set_column_address(adrColumn);
    for (i = 0; i < 8; i++) {
        write_data(pgm_read_byte(dptr ++));
    }
}

/*
 * display one Chinese character with specified position
 */
uint8 lcd_display_HZ(char *pszChar, uint8 adrPage, uint8 adrColumn, FontType_t fntType) {
    const int8 *dptr;
    uint8 i, j, uRow, uCol;

    switch (fntType) {
    case FONT1616:
        dptr = (char *) search_library(HZ_Table, pszChar, sizeof(Hz1616_t), FONT_LIB_SIZE);
        uRow = 16;
        uCol = 16;
        break;

    case FONT2432:
        dptr = (char *) search_library(HZ_Table_2432, pszChar, sizeof(Hz2432_t), FONT_LIB_SIZE_2432);
        uRow = 32;
        uCol = 24;
        break;

    case FONT2132:
        dptr = (char *) search_library(HZ_Table_2132, pszChar, sizeof(Hz2132_t), FONT_LIB_SIZE_2432);
        uRow = 32;
        uCol = 21;
        break;

    default:
        dptr = NULL;
        uRow = 0;
        uCol = 0;
        break;
    }

    if (NULL == dptr)
        return FALSE;

    uint8 uPage = uRow / 8;
    for (i = 0; i < uPage; i++) {
        lcd_set_page_address(adrPage + i);
        lcd_set_column_address(adrColumn);
        for (j = 0; j < uCol; j++) {
            write_data(pgm_read_byte(dptr));
            dptr++;
        }
    }

    return TRUE;
}

/*
 * display string
 */
uint8 lcd_display_string(char *pszString, uint8 adrPage, uint8 adrColumn, FontType_t fntType) {
    char cData[2];
    uint8 uLen, uPage, uCol, uWidth, uHeight;

    uLen = strlen(pszString);
    uPage = adrPage;
    uCol = adrColumn;

    switch (fntType) {
    case FONT1616:
        uWidth = 16;
        uHeight = 16;
        break;

    case FONT2432:
        uWidth = 24;
        uHeight = 32;
        break;

    case FONT2132:
        uWidth = 21;
        uHeight = 32;
        break;

    default:
        return 0;
    }

    while (uLen) {
        cData[0] = *pszString++;
        if (cData[0] <= 0x80) {
            lcd_display_ASCII(cData[0], uPage, uCol);
            uCol += 8;
            uLen--;
        } else {
            cData[1] = *pszString++;
            lcd_display_HZ(cData, uPage, uCol, fntType);
            uCol += uWidth;
            uLen -= 2;
        }

        if (uCol >= MAX_COLUMN) {
            uCol = 0;
            uPage += uHeight / 8;
            if (uPage >= MAX_PAGE)
                uPage = 0;
        }
    }

    return uLen;
}

/*
 * display image
 */
uint8 lcd_display_picture(char *pImage, uint8 adrPage, uint8 adrColumn, uint8 Width, uint8 Hight) {
    uint8 *dptr;
    uint8 i, j;

    if ((adrPage + Hight) > MAX_PAGE)
        return FALSE;
    if ((adrColumn + Width) > MAX_COLUMN)
        return FALSE;

    dptr = (uint8 *) pImage;

    for (i = 0; i < Hight; i++) {
        lcd_set_page_address(adrPage + i);
        lcd_set_column_address(adrColumn);
        for (j = 0; j < Width; j++) {
            write_data(pgm_read_byte(dptr));
        }
    }

    return TRUE;
}

uint8 lcd_display_line(uint8 x, uint8 y, uint8 x1, uint8 y1) {
    uint8 adrPage, uContent;

    if (x > MAX_COLUMN)
        return FALSE;
    if (y > MAX_LINE)
        return FALSE;

    adrPage  = y / 8;
    uContent = 1 << (y % 8);

    lcd_display_data(uContent, adrPage, x);

    return TRUE;
}

