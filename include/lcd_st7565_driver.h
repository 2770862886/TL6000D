#ifndef LCD_ST7565_H
#define LCD_ST7565_H

/*******************************************************************************
  No  | A0 | RW | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
 -------------------------------------------------------------
  1     0    0    1    0    1    0    1    1    1    0/1      Display On[1], Off[0]
  2     0    0    0    1    x    x    x    x    x    x        Set start line
  3     0    0    1    0    1    1    x    x    x    x        Set page address
  4     0    0    0    0    0    1    x    x    x    x        High byte column address
  5     0    0    0    0    0    0    x    x    x    x        Low byte column address
  6     0    1    x    x    x    x    0    0    0    0        Read status
  7     1    0    x    x    x    x    x    x    x    x        Write display data
  8     1    1    x    x    x    x    x    x    x    x        Read display data
  9     0    0    1    0    1    0    0    0    0    0/1      Display RAM address Normal[0], Reverse[1]
  10    0    0    1    0    1    0    0    1    0    0/1      Display all points Normal[0], All points[1]
  11    0    0    1    0    1    0    0    0    1    0/1      LCD drive voltage bias ratio 1/9[0], 1/7[1]
  12    0    0    1    1    1    0    0    0    0    0        Column address increment
  13    0    0    1    1    1    0    1    1    1    0        Clear read/modify/write
  14    0    0    1    1    1    0    0    0    1    0        Internal reset
  15    0    0    1    1    0    0    0/1  *    *    *        Select COM output scan direction Normal[0], Reverse[1]
  16    0    0    0    0    1    0    1    x    x    x        Select internal power supply operation mode
  17    0    0    0    0    1    0    0    x    x    x        Select internal resistor ratio mode
  18    0    0    1    0    0    0    0    0    0    1        Set V5 output voltage electronic volume register
        0    0    *    *    x    x    x    x    x    x
  19    0    0    1    0    1    0    1    1    0    0/1      Static indicator ON[1], OFF[0]
        0    0    *    *    *    *    *    *    x    x        Set flashing mode
  20                                                               Display OFF and display all points ON
  21    0    0    1    1    1    0    0    0    1    1        Non-operation
  22    0    0    1    1    1    1    *    *    *    *        Command for IC test, Do not use this command
  23    0    0    1    1    1    1    0    0    0    0        Enter during the refresh sequence
 *******************************************************************************/
#define LCD_START_COLUMN            (0)
#define MAX_LINE                    (64)
#define MAX_COLUMN	                (98)
#define MAX_PAGE                    (MAX_LINE/8)
#define MIN_CONTRAST                0x01
#define MAX_CONTRAST                0x3F
#define DEFAULT_CONTRAST            0x20

#define EN_FONT0816	                (1)

/*
parallel mode
#define LCD_RST                     PD(3)
#define LCD_CS                      PD(4)
#define LCD_A0                      PD(5)
#define LCD_RW                      PD(6)
#define LCD_EN                      PD(7)
#define LCD_DATA                    PORTC
*/

#define LCD_CS                      PD(5)
#define LCD_RST                     PD(6)
#define LCD_AO                      PD(7)

#define LCD_SCL                     PC(0)
#define LCD_SDA                     PC(1)

typedef enum {
    FONT1616,
    FONT2132,
    FONT2432,
} FontType_t;

/*
 * initialize lcd device and configuration
 */
extern void lcd_init(void);

/*
 * write the whole screen with given data
 */
extern void lcd_clr(uint8 data);

/*
 * write the specified page with given data
 */
extern void lcd_display_data(uint8 data, uint8 adrPage, uint8 adrColumn);

/*
 * reset lcd device
 */
extern void lcd_reset();

/*
 * adjust the contrast level
 */
extern void lcd_set_electronic_volume(uint8 Volume);

/*
 * display ascii code, with fixed dimension 8 * 16
 */
extern void lcd_display_ASCII(char ascii, uint8 adrPage, uint8 adrColumn);

/*
 * display Chinese character with specified font size via enum FontType
 */
extern uint8 lcd_display_HZ(char *pszChar, uint8 adrPage, uint8 adrColumn, FontType_t fntType);

/*
 * display string with specified font size, but ascii only support 8 * 16 font size
 */
extern uint8 lcd_display_string(char *pszString, uint8 adrPage, uint8 adrColumn, FontType_t fntType);

/*
 * display the content of bitmap
 */
extern uint8 lcd_display_picture(char *pImage, uint8 adrPage, uint8 adrColumn, uint8 Weight, uint8 Hight);

/*
 * draw line from point 1 to point 2
 */
extern uint8 lcd_display_line(uint8 x, uint8 y, uint8 x2, uint8 y2);

#endif
