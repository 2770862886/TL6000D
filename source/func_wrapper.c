#include "config.h"

const uint32 B_COMMON_ITEMS = B_MODE | B_VOTE | B_SIGN | B_REMARK | B_LOCK | B_VOTED;

inline void enable_led() {
    LED_BACK_ON();
    g_led_enabled = TRUE;

    g_timer2 = 0;
}

inline void disable_led() {
    LED_BACK_OFF();
    g_led_enabled = FALSE;
}

inline void operate_laser(Laser_mode_t mode) {
    if (g_laser_mode == mode)
        return;

    g_laser_mode = mode;

    switch (mode) {
    case LASER_OFF:
        LASER_OFF();
        g_laser_on = FALSE;
        break;

    case LASER_BLINK:
    case LASER_BLINK_SPEC_TIMES:
        g_laser_blink_num = 0;
        g_timer4 = 0;
        break;

    default:
        break;
    }
}

inline void operate_audio(Audio_mode_t mode) {
    if (g_audio_on == mode)
        return;

    g_audio_on = mode;

    if (AUDIO_ON == mode) {
        AUDIO_ON();
    } else {
        AUDIO_OFF();
    }
}

void close_phone() {
    g_discuss_state = DISCUSS_STATE_CLOSE;

    operate_laser(LASER_OFF);
    operate_audio(AUDIO_OFF);
}

void display_clear_pages(uint8 start, uint8 count) {
    while (count--) {
        lcd_display_data(0x00, start++, 0);
    }
}

/*
 * 清除第一，第二行的显示
 */
void display_clear_1N() {
    display_clear_pages(0, 2);
}

/*
 * 清除第三，第四，第五，第六行的显示
 */
void display_clear_2N() {
    display_clear_pages(2, 4);
}

void display_line() {
#if LANG_SET == 1
    lcd_display_data(0x01, 3, 0);
#endif
}

void display_address() {
    uint8 start = 58;

    char szContent[8];

    char role = g_cameraNo & 0xF0;
    if (0x20 == role && (MODEL_VOTE != g_model)) {
        lcd_display_string("C", 0, start, FONT1616);
    } else if (0x10 == role && (MODEL_VOTE != g_model)) {
        lcd_display_string("A", 0, start, FONT1616);
    } else {
        lcd_display_string(" ", 0, start, FONT1616);
    }

    sprintf(szContent, "%04d", g_addr_full);
    lcd_display_string(szContent, 0, start + 8, FONT1616);
}

/*
 * 液晶显示函数封装
 */
void display_logo() {
    display_clear_1N();
    lcd_display_string(STR_LOGO, 0, LCD_START_COLUMN, FONT1616);
    display_address();
}

void display_welcome() {
    display_clear_2N();
    display_line();
#if LANG_SET == 0
    lcd_display_string(STR_WELCOME, 2, LCD_START_COLUMN + 6, FONT2132);
#else
    lcd_display_string(STR_WELCOME, 2, LCD_START_COLUMN, FONT2132);
#endif
}

void display_not_connected() {
    display_clear_pages(6, 1);
    lcd_display_string(STR_NOT_CONNECTED, 6, LCD_START_COLUMN, FONT1616);
}

void display_connected() {
    display_clear_pages(6, 1);
    lcd_display_string(STR_CONNECTED, 6, LCD_START_COLUMN, FONT1616);
}

/*
 * 显示"按报到键"
 */
void display_press_to_sign() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_SIGN_PRESS, 2, LCD_START_COLUMN, FONT2432);
}

/*
 * 显示"请插卡"
 */
void display_insert_card_to_sign() {
    display_clear_1N();
    lcd_display_string(STR_SIGN_CARD, 0, LCD_START_COLUMN, FONT1616);
    display_address();
}

/* 显示"请按键" */
void display_press_key() {
    display_clear_1N();
    lcd_display_string(STR_INPUT, 0, LCD_START_COLUMN, FONT1616);
    display_address();
}

/* 显示"请按数字键" */
void display_press_number() {
    display_clear_1N();
    lcd_display_string(STR_INPUT_NUMBER, 0, LCD_START_COLUMN, FONT1616);
}

void display_signed() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_SIGNED, 2, LCD_START_COLUMN, FONT2432);
}

void display_not_signed() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_NOT_SIGNED, 2, LCD_START_COLUMN, FONT2432);
}

void display_signed_fail() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_SIGN_FAIL, 2, LCD_START_COLUMN, FONT2432);
}

void display_sign_end() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_SIGN_END, 2, LCD_START_COLUMN, FONT2432);
}

void display_discuss_apply() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_DISCUSS_APPLY, 2, LCD_START_COLUMN, FONT2432);
}

void display_discuss_open() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_DISCUSS_OPEN, 2, LCD_START_COLUMN, FONT2432);
}

void display_discuss_ongoing() {
    display_clear_1N();
    lcd_display_string(STR_DISCUSS_ONGOING, 0, LCD_START_COLUMN, FONT1616);
    display_address();
}

void display_discuss_close() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_DISCUSS_CLOSE, 2, LCD_START_COLUMN, FONT2432);
}

void display_vote_number() {
    display_clear_1N();

    char szContent[16];
    sprintf(szContent, STR_VOTE_REMAIN, g_available);
    lcd_display_string(szContent, 0, LCD_START_COLUMN, FONT1616);
}

void display_vote_please() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_VOTE_START, 2, LCD_START_COLUMN, FONT2432);
}

void display_vote_end() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_VOTE_END, 2, LCD_START_COLUMN, FONT2432);
}

void display_vote5_please() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_VOTE5_START, 2, LCD_START_COLUMN, FONT2432);
}

void display_vote5_end() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_VOTE5_END, 2, LCD_START_COLUMN, FONT2432);
}

void display_valid_on_first_press() {
    display_clear_1N();
    lcd_display_string(STR_VALID_ON_FIRST, 0, LCD_START_COLUMN, FONT1616);
}

void display_valid_on_last_press() {
    display_clear_1N();
    lcd_display_string(STR_VALID_ON_LAST, 0, LCD_START_COLUMN, FONT1616);
}

void display_remark_please() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_REMARK_START, 2, LCD_START_COLUMN, FONT2432);
}

void display_remark_end() {
    display_clear_2N();
    display_line();
    lcd_display_string(STR_REMARK_END, 2, LCD_START_COLUMN, FONT2432);
}

void display_icc_ok() {
    display_clear_1N();
    lcd_display_string(STR_CARD_VALID, 0, LCD_START_COLUMN, FONT1616);
    display_address();
}

void display_icc_no_card() {
    display_clear_1N();
    lcd_display_string(STR_CARD_NONE, 0, LCD_START_COLUMN, FONT1616);
    display_address();
}

void display_icc_err_wrong_no() {
    display_clear_1N();
    lcd_display_string(STR_CARD_ERR, 0, LCD_START_COLUMN, FONT1616);
    display_address();
}

void display_icc_err_invalid() {
    display_clear_1N();
    lcd_display_string(STR_CARD_INVALID, 0, LCD_START_COLUMN, FONT1616);
    display_address();
}

void display_vote5(uint8 value) {
    display_clear_2N();
    display_line();

    switch (value) {
    case 1:
        lcd_display_string(STR_CANDIDATE_1, 2, LCD_START_COLUMN, FONT2432);
        break;
    case 2:
        lcd_display_string(STR_CANDIDATE_2, 2, LCD_START_COLUMN, FONT2432);
        break;
    case 3:
        lcd_display_string(STR_CANDIDATE_3, 2, LCD_START_COLUMN, FONT2432);
        break;
    case 4:
        lcd_display_string(STR_CANDIDATE_4, 2, LCD_START_COLUMN, FONT2432);
        break;
    case 5:
        lcd_display_string(STR_CANDIDATE_5, 2, LCD_START_COLUMN, FONT2432);
        break;
    default:
        break;
    }
}

void display_plugin_earphone() {
    display_clear_pages(6, 1);
    lcd_display_string(STR_PLUG_EARPHONE, 6, LCD_START_COLUMN, FONT1616);
}

/**
 * 串口发包
 *
 * @param data1
 * @param data2
 * @param data3
 * @param data4
 * @param data5
 */
void send_package(uint8 data1, uint8 data2, uint8 data3, uint8 data4, uint8 data5) {
    UCSRB &= ~(1 << RXCIE);

//#ifdef CHAIRMAN_VERSION
//    uint8 chk_sum = data1 + data2 + data3 + data4 + data5;
//    uint8 seq[] = { 0xAA, 0xAA, data1, data2, data3, data4, data5, chk_sum, 0, chk_sum };
//#else
    uint8 chk_sum = data1 + data2 + 0xFF + data3 + data4;
    uint8 chk_sum1 = chk_sum + data5;
    uint8 seq[] = { 0xAA, 0xAA, data1, data2, 0xFF, data3, data4, chk_sum, data5, chk_sum1 };
//#endif

    MAX487_TXD_EN();

    usart_sendSeq(seq, 10);

    _delay_ms(8);

    MAX487_RXD_EN();

    UCSRB |= (1 << RXCIE);
}

void send_package_1(uint8 data1, uint8 data2, uint8 data3, uint8 data4, uint8 data5, uint8 data6) {
    UCSRB &= ~(1 << RXCIE);

//#ifdef CHAIRMAN_VERSION
//    uint8 chk_sum = data1 + data2 + data3 + data4 + data5;
//    uint8 seq[] = { 0xAA, 0xAA, data1, data2, data3, data4, data5, chk_sum, 0, chk_sum };
//#else
    uint8 chk_sum = data1 + data2 + data3 + data4 + data5;
    uint8 chk_sum1 = chk_sum + data6;
    uint8 seq[] = { 0xAA, 0xAA, data1, data2, data3, data4, data5, chk_sum, data6, chk_sum1 };
//#endif

    MAX487_TXD_EN();

    usart_sendSeq(seq, 10);

    _delay_ms(8);

    MAX487_RXD_EN();

    UCSRB |= (1 << RXCIE);
}

/*
 * Return value:
 * 0: no card
 * 1: both address and password pair
 * 2: only password pair
 * 3: none pair
 */
uint8 check_card_valid(void) {
    uint8 ret = 0xFF;

    if (CARD_INSERTED()) {
        _delay_ms(20);

        if (CARD_INSERTED()) {
            ICC_BUF[0] = 0;
            ICC_BUF[1] = 0;
            ICC_BUF[2] = 0;

            ICC_PWR = 1;
            _delay_us(10);
            ResetCard();

            ReadMainMem(0x29, ICC_BUF, 4);
            BreakOperate();

            _delay_us(10);
            ResetCard();

            if (ICC_BUF[0] == g_addr_l && ICC_BUF[1] == g_password1 && ICC_BUF[2] == g_password2) {
                ret = 1;
            } else if (ICC_BUF[1] == g_password1 && ICC_BUF[2] == g_password2) {
                ret = 2;
            } else {
                ret = 3;
            }

            _delay_us(20);

            ICC_PWR = 0;
        } else {
            ret = 0;
        }
    } else {
        ret = 0;
    }

    return ret;
}

void function_init(uint8 addr_l, uint8 addr_h) {
    display_connected();

    g_online = TRUE;

    if (0 == addr_l && 0 == addr_h) {       // 总自检
        if (0x00 == g_cameraNo_vice) {
            close_phone();
        }

        g_mode = MODE_INIT;

        g_send_permit = FALSE;
        g_send_enable = FALSE;
        g_timer6 = 0;

        g_signIn = FALSE;
        g_vote = VOTE_NOT_PRESS;
        g_hasVoted = FALSE;
        g_remark = 0;
        g_lock = FALSE;
        g_chairman_press = 0;

        g_group_sign = FALSE;
        g_group_vote = FALSE;

        display_logo();
        display_welcome();

        save_status(B_MODE | B_SIGN);
    } else if (addr_l == g_addr_l && addr_h == g_addr_h) {      // 单机自检
        send_package(addr_l, g_addr_back, g_cameraNo_vice, g_model, addr_h);

        g_mode = MODE_INIT;

        g_signIn = FALSE;
        g_lock = TRUE;

        g_hasVoted = TRUE;

        g_group_sign = FALSE;
        g_group_vote = FALSE;

        save_status(B_MODE | B_SIGN);
    }
}

void function_sign_key(uint8 addr_l, uint8 addr_h, uint8 type) {
    if (0 == addr_l && 0 == addr_h) {
        if (0 == type && !g_group_sign) { // 总按键签到
            g_mode = MODE_SIGN_KEY;
            g_sign_mode = SIGN_MODE_PRESS;

            g_signIn = FALSE;
            g_lock = FALSE;
            g_lock_sign = FALSE;
            g_hasVoted = FALSE;
            g_chairman_press = 0;

            g_pressKeyNeeded = TRUE;
            g_group_sign = TRUE;

            operate_laser(LASER_BLINK);

            display_press_to_sign();
            display_press_key();

            enable_led();

            save_status(B_MODE | B_SIGN_MODE | B_SIGN | B_LOCK);
        } else if (1 == type) { // 总结束按键签到
            g_mode = MODE_SIGN_KEY;

            g_group_sign = FALSE;
            g_lock = TRUE;
            g_lock_sign = TRUE;

            display_sign_end();
            display_logo();

            save_status(B_MODE | B_LOCK | B_LOCK_SIGN);
        }
    } else if (addr_l == g_addr_l && addr_h == g_addr_h) {
        if (1 == type) { // 单机按键报到
            g_mode = MODE_SIGN_KEY;
            g_sign_mode = SIGN_MODE_PRESS;

            g_signIn = FALSE;
            g_lock = FALSE;
            g_lock_sign = FALSE;
            g_hasVoted = FALSE;

            g_chairman_press = 0;

            display_press_to_sign();
            display_press_key();

            save_status(B_MODE | B_SIGN_MODE | B_LOCK | B_LOCK_SIGN);
        } else { // 报到查询
            g_mode = MODE_SIGN_KEY;

            if (g_signIn) {
                send_package(addr_l, g_addr_back, 0, DATA_SIGNED, addr_h);
            } else {
                send_package(addr_l, g_addr_back, 0, DATA_NOSIGNED, addr_h);
            }
        }
    }
}

void function_sign_card(uint8 addr_l, uint8 addr_h, uint8 password1, uint8 password2) {
    if (0 == addr_l && !g_group_sign) { // 总开始插卡签到核对密码卡号
        g_mode = MODE_SIGN_CARD1;
        g_sign_mode = SIGN_MODE_ICC;

        g_signIn = FALSE;
        g_lock = FALSE;
        g_lock_sign = FALSE;
        g_hasVoted = FALSE;

        g_group_sign = TRUE;

        g_show_status = 0;

        g_password1 = password1;
        g_password2 = password2;

        display_insert_card_to_sign();
        enable_led();

        save_status(B_MODE | B_SIGN_MODE | B_LOCK | B_LOCK_SIGN | B_PASSWORD1 | B_PASSWORD2);
    } else if (addr_l == g_addr_l && addr_h == g_addr_h) { // 插卡签到查询
        g_lock_sign = FALSE;

        if (g_signIn) {
            send_package(addr_l, g_addr_back, 0, 0x12, addr_h);
        } else {
            send_package(addr_l, g_addr_back, 0, 0x13, addr_h);
        }
    }
}

void function_sign_card_back(uint8 addr_l, uint8 addr_h, uint8 password1, uint8 password2) {
    if (0 == addr_l && 0 == addr_h && !g_group_sign) {
        g_mode = MODE_SIGN_CARD2;
        g_sign_mode = SIGN_MODE_ICC_BACK;

        g_signIn = FALSE;
        g_lock = FALSE;
        g_lock_sign = FALSE;
        g_hasVoted = FALSE;

        g_group_sign = TRUE;

        g_show_status = 0;

        g_password1 = password1;
        g_password2 = password2;

        display_insert_card_to_sign();
        enable_led();

        save_status(
        B_MODE | B_SIGN_MODE | B_LOCK | B_LOCK_SIGN | B_PASSWORD1 | B_PASSWORD2);
    } else if (addr_l == g_addr_l && addr_h == g_addr_h) {
        g_lock_sign = FALSE;

        if (g_signIn) {
            g_cardNo_h = ICC_BUF[0];
            g_cardNo_l = ICC_BUF[1];
            send_package(addr_l, g_addr_back, g_cardNo_h, g_cardNo_l, addr_h);
        } else {
            send_package(addr_l, g_addr_back, COM_ANSWER, 0xFF, addr_h);
        }
    }
}

void function_sign_end(uint8 addr_l, uint8 addr_h) {
    if ((0 == addr_l && 0 == addr_h) || (addr_l == g_addr_l && addr_h == g_addr_h)) {
        g_lock = TRUE;
        g_lock_sign = TRUE;
        g_group_sign = FALSE;

        display_sign_end();
        display_logo();

        save_status(B_MODE | B_LOCK | B_LOCK_SIGN);
    }

    if (g_signIn) {
        check_card_valid();

        g_cardNo_h = ICC_BUF[0];
        g_cardNo_l = ICC_BUF[1];
        g_password1 = ICC_BUF[2];
        g_password2 = ICC_BUF[3];

        save_status(B_CARD_NO_H | B_CARD_NO_L | B_PASSWORD1 | B_PASSWORD2);
    }
}

void function_download_camera_vice_chairman(uint8 addr_l, uint8 addr_h, uint8 cameraNo) {
    if (addr_l == g_addr_l && addr_h == g_addr_h) {
        g_cameraNo_vice = cameraNo & 0xF0;
        send_package(addr_l, g_addr_back, g_cameraNo_vice, g_position, addr_h);

        save_status(B_CAMERA_NO_VICE);
    }
}

void function_download_camera(uint8 addr_l, uint8 addr_h, uint8 cameraNo, uint8 position) {
    if (addr_l == g_addr_l && addr_h == g_addr_h) {
        g_cameraNo = cameraNo | g_cameraNo_vice;
        g_position = position;

        send_package(addr_l, g_addr_back, cameraNo, position, addr_h);

        display_address();

        save_status(B_CAMERA_NO | B_POSITION);
    }
}

void function_clear_screen() {
    if (g_signIn) {
        g_lock = TRUE;
        g_show_wait = FALSE;
        g_hasVoted = FALSE;
        g_group_vote = FALSE;

        display_clear_2N();
        display_line();
        display_logo();
    } else {
        g_mode = MODE_INIT;
        g_lock = TRUE;

        display_logo();
        display_not_signed();
    }
}

void function_contrast_default(uint8 addr_l, uint8 addr_h) {
    if (addr_l == g_addr_l && addr_h == g_addr_h) {
        g_lcd_contrast = DEFAULT_CONTRAST;
        lcd_set_electronic_volume(DEFAULT_CONTRAST);

        save_status(B_CONTRAST);
    }
}

void function_contrast_up(uint8 addr_l, uint8 addr_h) {
    if (addr_l == g_addr_l && addr_h == g_addr_h) {
        if (g_lcd_contrast < MAX_CONTRAST) {
            g_lcd_contrast ++;
            lcd_set_electronic_volume(g_lcd_contrast);

            save_status(B_CONTRAST);
        }
    }
}

void function_contrast_down(uint8 addr_l, uint8 addr_h) {
    if (addr_l == g_addr_l && addr_h == g_addr_h) {
        if (g_lcd_contrast > MIN_CONTRAST) {
            g_lcd_contrast --;
            lcd_set_electronic_volume(g_lcd_contrast);

            save_status(B_CONTRAST);
        }
    }
}

void function_search(uint8 addr_l, uint8 addr_h) {
    if (0 == addr_l && 0 == addr_h) { // 总搜索
        display_logo();
        display_welcome();
    } else if (addr_l == g_addr_l && addr_h == g_addr_h) { // 单机搜索
        send_package(addr_l, g_addr_back, 0x00, 0xF6, addr_h);
    }
}

void function_one_sign(uint8 addr_l, uint8 addr_h, uint8 password1, uint8 password2) {
    if (addr_l == g_addr_l && addr_h == g_addr_h) {
        g_mode = MODE_SIGN_CARD1;
        g_sign_mode = SIGN_MODE_ICC;

        g_signIn = FALSE;
        g_lock = FALSE;
        g_lock_sign = FALSE;
        g_hasVoted = FALSE;

        g_show_status = 0;

        g_password1 = password1;
        g_password2 = password2;

        display_insert_card_to_sign();
        enable_led();

        save_status(B_MODE | B_LOCK | B_LOCK_SIGN | B_PASSWORD1 | B_PASSWORD2);
    }
}

void function_one_sign_back(uint8 addr_l, uint8 addr_h, uint8 password1, uint8 password2) {
    if (addr_l == g_addr_l && addr_h == g_addr_h) {
        g_mode = MODE_SIGN_CARD2;
        g_sign_mode = SIGN_MODE_ICC_BACK;

        g_signIn = FALSE;
        g_lock = FALSE;
        g_lock_sign = FALSE;
        g_hasVoted = FALSE;

        g_show_status = 0;

        g_password1 = password1;
        g_password2 = password2;

        display_insert_card_to_sign();
        enable_led();

        save_status(B_MODE | B_SIGN_MODE | B_LOCK | B_LOCK_SIGN | B_PASSWORD1 | B_PASSWORD2);
    }
}

void function_change_address(uint8 addr_l, uint8 addr_h, uint8 data) {
    g_mode = MODE_CHG_ADDR;

    uint8 model = data & 0x0F;
    uint8 si_model = data & 0xF0;

    g_lock = FALSE;
    g_pressKeyNeeded = TRUE;

    g_model_buf = model;
    g_si_model_buf = si_model;

    operate_laser(LASER_BLINK);

    char addr_ori[6], addr_new[6];

    g_addr_l_buf = addr_l;
    g_addr_h_buf = addr_h;
    g_addr_full_buf = (addr_h << 8) + addr_l;

    sprintf(addr_ori, "%04d", g_addr_full);
    sprintf(addr_new, "%04d", g_addr_full_buf);

    display_clear_2N();

    lcd_display_string(addr_ori, 2, LCD_START_COLUMN, FONT1616);
    lcd_display_string(STR_CHANGE_ADDR, 4, LCD_START_COLUMN + 24, FONT1616);
    lcd_display_string(addr_new, 2, 64, FONT1616);

    save_status(B_MODE);
}

void function_pass(uint8 addr_l, uint8 addr_h) {
    if ((g_mode == MODE_DISCUSS) && (addr_l != g_addr_l || addr_h != g_addr_h)) {
        g_obj_addr_l = addr_l;
        g_obj_addr_h = addr_h;

        g_chairman_press = 1;

        operate_laser(LASER_BLINK);
    } else if (0 == addr_l) {
        operate_laser(LASER_BLINK_SPEC_TIMES);
    }
}

void function_discuss_open(uint8 addr_l, uint8 addr_h) {
    if (addr_l == g_addr_l && addr_h == g_addr_h) {
        g_mode = MODE_DISCUSS;
        g_discuss_state = DISCUSS_STATE_OPEN;
        g_lock = FALSE;

        g_send_permit = FALSE;
        g_send_enable = FALSE;
        g_timer6 = 0;

        send_package(addr_l, DATA_OPEN_TALL, g_cameraNo, g_position, addr_h);

        display_discuss_open();

        operate_laser(LASER_STATIC);
        operate_audio(AUDIO_ON);
    }
}

void function_discuss_start(uint8 addr_l, uint8 addr_h, uint8 type) {
    if (0 == addr_l && 0 == addr_h) {
        display_connected();

        if (0 == type) { // 总开始讨论
            g_mode = MODE_DISCUSS;
            g_lock = FALSE;
            g_chairman_press = 0;

            if (0x00 == g_cameraNo_vice) {
                close_phone();
                display_discuss_close();
            }

            if (DISCUSS_STATE_OPEN == g_discuss_state) {
                display_discuss_open();
            } else if (DISCUSS_STATE_APPLY == g_discuss_state) {
                display_discuss_apply();
            } else {
                display_discuss_close();
            }

            display_discuss_ongoing();

            save_status(B_MODE | B_DISCUSS_STATE | B_LOCK);
        } else if (1 == type) { // 总结束讨论
            g_mode = MODE_DISCUSS;
            g_lock = TRUE;
            g_chairman_press = 0;

            if (0x00 == g_cameraNo_vice) {
                close_phone();
                display_discuss_close();
            }

            display_discuss_close();
            display_logo();

            save_status(B_MODE | B_LOCK | B_DISCUSS_STATE);
        }
    } else if (addr_l == g_addr_l && addr_h == g_addr_h) { // 讨论状态查询
        if (0x20 == g_cameraNo_vice) {
            if (g_clear_phone) {
                g_clear_phone = FALSE;

                send_package(g_addr_l, 0x40, g_cameraNo, g_position, addr_h);
            } else {
                if (DISCUSS_STATE_CLOSE == g_discuss_state) {
                    send_package(g_addr_l, DATA_CLOSE_TALL, g_cameraNo, g_position, addr_h);
                } else if (DISCUSS_STATE_OPEN == g_discuss_state) {
                    send_package(g_addr_l, DATA_OPEN_TALL, g_cameraNo, g_position, addr_h);
                }
            }
        } else {
            if (DISCUSS_STATE_CLOSE == g_discuss_state) {
                send_package(addr_l, DATA_CLOSE_TALL, g_cameraNo, g_position, addr_h);
            } else if (DISCUSS_STATE_OPEN == g_discuss_state) {
                send_package(addr_l, DATA_OPEN_TALL, g_cameraNo, g_position, addr_h);
            } else if (DISCUSS_STATE_APPLY == g_discuss_state) {
                send_package(addr_l, DATA_APPLY_TALL, g_cameraNo, g_position, addr_h);
            }
        }
    }
}

void function_discuss_close(uint8 addr_l, uint8 addr_h) {
    if (0x20 == g_cameraNo_vice || 0x10 == g_cameraNo_vice) {
        if (addr_l == g_obj_addr_l && addr_h == g_obj_addr_h) {
            g_mode = MODE_DISCUSS;
            g_lock = FALSE;

            g_send_enable = FALSE;
            g_send_permit = FALSE;

            g_timer6 = 0;
        } else if (addr_l == g_addr_l && addr_h == g_addr_h) {
            g_mode = MODE_DISCUSS;
            g_lock = FALSE;

            g_send_enable = FALSE;
            g_send_permit = FALSE;

            g_timer6 = 0;

            if (g_discuss_state != DISCUSS_STATE_CLOSE) {
                g_discuss_state = DISCUSS_STATE_CLOSE;

                close_phone();
                display_discuss_close();
            }
        }
    } else {
        if (addr_l == g_addr_l && addr_h == g_addr_h) {
            g_mode = MODE_DISCUSS;
            g_lock = FALSE;

            g_send_permit = FALSE;
            g_send_enable = FALSE;
            g_timer6 = 0;

            if (g_discuss_state != DISCUSS_STATE_CLOSE) {
                g_discuss_state = DISCUSS_STATE_CLOSE;

                close_phone();
                display_discuss_close();
            }
        } else if (0 == addr_l && 0 == addr_h) {
            g_mode = MODE_DISCUSS;
            g_lock = FALSE;

            g_send_permit = FALSE;
            g_send_enable = FALSE;
            g_timer6 = 0;

            if (g_discuss_state != DISCUSS_STATE_CLOSE) {
                g_discuss_state = DISCUSS_STATE_CLOSE;

                close_phone();
                display_discuss_close();
            }
        }
    }
}

void function_discuss_wait(uint8 addr_l, uint8 addr_h) {
    if (addr_l == g_addr_l && addr_h == g_addr_h) {
        g_discuss_state = DISCUSS_STATE_APPLY;

        g_send_permit = FALSE;
        g_send_enable = FALSE;
        g_timer6 = 0;
    }
}

void function_discuss_wait2(uint8 addr_l, uint8 addr_h) {
    if (addr_l == g_addr_l && addr_h == g_addr_h) {
        g_discuss_state = DISCUSS_STATE_APPLY;

        g_send_permit = FALSE;
        g_send_enable = FALSE;
        g_timer6 = 0;

        // don't blink while searching
        operate_laser(LASER_OFF);
    } else if (0 == addr_l && 0 == addr_h) {
        g_send_permit = FALSE;
        g_send_enable = FALSE;
        g_timer6 = 0;

        // don't blink while searching
        operate_laser(LASER_OFF);
    }
}

void function_vote(uint8 addr_l, uint8 addr_h, uint8 data1, uint8 data2) {
    if (0 == addr_l) {
        if (g_signIn) {
            g_mode = MODE_VOTE;

            enable_led();

            if (data1 & 0x01) { // 第一次有效
                g_limit_one_action = TRUE;
            } else {            // 最后一次有效
                g_limit_one_action = FALSE;
            }

            if (data1 & 0x10) { // 多选表决
                g_vote_mode = VOTE_MODE_MULTIPLE;

                if (0xFF == data2) { // 选举结束
                    g_vote = VOTE_NOT_PRESS;
                    g_lock = TRUE;
                    g_hasVoted = TRUE;

                    display_vote_end();
                    display_logo();
                } else if (0 == data2) { // 选举过程中
                    if (!g_group_vote) {
                        if (VOTE_APPROVE == g_vote) {
                            g_available --;
                        }

                        g_group_vote = TRUE;
                        g_vote = VOTE_NOT_PRESS;
                        g_lock = FALSE;
                        g_hasVoted = FALSE;
                        g_card_inserted = 0;

                        display_vote_number();
                        display_vote_please();
                    }
                } else { // 选举开始
                    g_available = data2;

                    g_vote = VOTE_NOT_PRESS;
                    g_lock = FALSE;
                    g_hasVoted = FALSE;

                    g_card_inserted = 0;

                    display_vote_number();
                    display_vote_please();
                }
            } else { // 普通表决
                g_vote_mode = 0;
                if (0 == data2) { // 普通表决开始
                    g_vote = VOTE_NOT_PRESS;
                    g_lock = FALSE;
                    g_hasVoted = FALSE;
                    g_card_inserted = 0;

                    if (g_limit_one_action) {
                        display_valid_on_first_press();
                    } else {
                        display_valid_on_last_press();
                    }

                    display_vote_please();
                } else if (1 == data2) { // 普通表决结束
                    g_vote = VOTE_NOT_PRESS;
                    g_lock = TRUE;
                    g_hasVoted = TRUE;

                    display_vote_end();
                    display_logo();
                }
            }

            save_status(B_COMMON_ITEMS | B_VOTE_MODE | B_AVAILABLE | B_VALID_ON_FIRST);
        } else { // not signed in
            g_lock = TRUE;
            display_not_signed();
        }
    } else if (addr_l == g_addr_l && addr_h == g_addr_h) {
        g_mode = MODE_VOTE;

        if (VOTE_NOT_PRESS == g_vote) {
            send_package(addr_l, g_addr_back, 0, DATA_VOTE1_NOPRESS, addr_h);
        } else if (VOTE_APPROVE == g_vote) {
            send_package(addr_l, g_addr_back, 0, DATA_VOTE1_YES, addr_h);
        } else if (VOTE_ABSTAIN == g_vote) {
            send_package(addr_l, g_addr_back, 0, DATA_VOTE1_ABSTAIN, addr_h);
        } else if (VOTE_REJECT == g_vote) {
            send_package(addr_l, g_addr_back, 0, DATA_VOTE1_NO, addr_h);
        }
    }
}

void function_vote5(uint8 addr_l, uint8 addr_h, uint8 data1, uint8 data2) {
    if (0 == addr_l) {
        if (g_signIn /*&& !g_group_vote*/) {
            g_mode = MODE_VOTE5;

            g_card_inserted = 0;
            g_group_vote = TRUE;
            g_lock = FALSE;
            g_vote = VOTE5_NOT_PRESS;
            g_hasVoted = FALSE;
            g_candidate = data1;
            g_available = data2;

            enable_led();
            display_vote5_please();
            display_press_number();

            save_status(B_CANDIDATE | B_AVAILABLE);
        } else { // not signed in
            g_lock = TRUE;
            display_not_signed();
        }
    } else if (addr_l == g_addr_l && addr_h == g_addr_h) {
        g_mode = MODE_VOTE5;

        if (VOTE5_NOT_PRESS == g_vote) {
            send_package(addr_l, g_addr_back, 0, DATA_VOTE5_NOPRESS, addr_h);
        } else if (VOTE5_1 == g_vote) {
            send_package(addr_l, g_addr_back, 0, DATA_VOTE5_NO1, addr_h);
        } else if (VOTE5_2 == g_vote) {
            send_package(addr_l, g_addr_back, 0, DATA_VOTE5_NO2, addr_h);
        } else if (VOTE5_3 == g_vote) {
            send_package(addr_l, g_addr_back, 0, DATA_VOTE5_NO3, addr_h);
        } else if (VOTE5_4 == g_vote) {
            send_package(addr_l, g_addr_back, 0, DATA_VOTE5_NO4, addr_h);
        } else if (VOTE5_5 == g_vote) {
            send_package(addr_l, g_addr_back, 0, DATA_VOTE5_NO5, addr_h);
        }
    }
}

void function_vote5_end(uint8 addr_l, uint8 addr_h) {
    if (g_signIn) {
        g_mode = MODE_VOTE5;

        g_lock = TRUE;
        g_vote = VOTE5_NOT_PRESS;
        g_hasVoted = TRUE;
        g_group_sign = FALSE;

        display_logo();
        display_vote5_end();

        save_status(B_COMMON_ITEMS);
    } else {
        g_lock = TRUE;
        display_not_signed();
    }
}

void function_remark(uint8 addr_l, uint8 addr_h, uint8 data1, uint8 data2) {
    if (0 == addr_l) {
        if (g_signIn) { // signed
            if (0 == data2 && !g_group_vote) { // start to remark
                g_mode = MODE_REMARK;

                g_card_inserted = 0;

                g_group_vote = TRUE;
                g_remark = 0;
                g_lock = FALSE;
                g_hasVoted = FALSE;

                enable_led();
                display_remark_please();

                if (0x01 == data1) { // 首次按键有效
                    g_limit_one_action = 1;
                    display_valid_on_first_press();
                } else {
                    g_limit_one_action = 0;
                    display_valid_on_last_press();
                }

                save_status(B_COMMON_ITEMS | B_VALID_ON_FIRST);
            } else if (1 == data2) { // end remark
                g_mode = MODE_REMARK;

                g_group_vote = FALSE;
                g_remark = 0;
                g_lock = TRUE;
                g_hasVoted = TRUE;

                display_logo();
                display_remark_end();

                save_status(B_COMMON_ITEMS);
            }
        } else { // no sign
            g_lock = TRUE;
            display_not_signed();
        }
    } else if (addr_l == g_addr_l && addr_h == g_addr_h) {
        g_mode = MODE_REMARK;

        if (REMARK_NOT_PRESS == g_remark) {
            send_package(addr_l, g_addr_back, 0, DATA_REMARK_NOPRESS, addr_h);
        } else if (REMARK_SATISFIED == g_remark) {
            send_package(addr_l, g_addr_back, 0, DATA_REMARK_NO2, addr_h);
        } else if (REMARK_ADEQUATE == g_remark) {
            send_package(addr_l, g_addr_back, 0, DATA_REMARK_NO3, addr_h);
        } else if (REMARK_DISAPPOINTED == g_remark) {
            send_package(addr_l, g_addr_back, 0, DATA_REMARK_NO4, addr_h);
        }
    }
}

void process_sign_key() {
    if (!g_lock_sign) {
        if (!g_signIn && KEYCODE_KEY1 == g_keyValue) {
            g_keyValue = 0;

            g_signIn = TRUE;
            g_pressKeyNeeded = FALSE;

            operate_laser(LASER_OFF);

            enable_led();
            display_signed();

            save_status(B_SIGN);
        }
    }
}

void process_sign_card1() {
    if (!g_lock_sign) {
        uint8 result;
        result = check_card_valid();
        switch (result) {
        case 0:
            if (g_show_status != 4) {
                g_show_status = 4;

                display_not_signed();
                display_clear_1N();
                display_icc_no_card();
            }

            if (g_signIn) {
                g_signIn = FALSE;

                save_status(B_SIGN);
            }
            break;

        case 1:
            if (g_show_status != 3) {
                g_show_status = 3;

                enable_led();
                display_signed();
                display_clear_1N();
                display_icc_ok();
            }

            if (!g_signIn) {
                g_signIn = TRUE;

                save_status(B_SIGN);
            }
            break;

        case 2:
            if (g_show_status != 2) {
                g_show_status = 2;

                display_icc_no_card();
                display_clear_1N();
                display_icc_err_wrong_no();
            }

            if (g_signIn) {
                g_signIn = FALSE;

                save_status(B_SIGN);
            }
            break;

        default:
            if (g_show_status != 1) {
                g_show_status = 1;

                display_not_signed();
                display_clear_1N();
                display_icc_err_invalid();
            }

            if (g_signIn) {
                g_signIn = FALSE;

                save_status(B_SIGN);
            }
            break;
        }
    }
}

void process_sign_card2() {
    if (!g_lock_sign) {
        uint8 result = check_card_valid();

        switch (result) {
        case 0:
            if (g_show_status != 4) {
                g_show_status = 4;

                display_not_signed();
                display_clear_1N();
                display_icc_no_card();
            }

            if (g_signIn) {
                g_signIn = FALSE;
                g_cardNo_l = 0;
                g_cardNo_h = 0;

                save_status(B_SIGN);
            }
            break;

        case 1:
            if (g_show_status != 3) {
                g_show_status = 3;

                enable_led();
                display_signed();
                display_clear_1N();
                display_icc_ok();
            }

            if (!g_signIn) {
                g_signIn = TRUE;

                save_status(B_SIGN);
            }
            break;

        case 2:
            if (g_show_status != 2) {
                g_show_status = 2;

                enable_led();
                display_signed();
                display_clear_1N();
                display_icc_ok();
            }

            if (!g_signIn) {
                g_signIn = TRUE;

                save_status(B_SIGN);
            }
            break;

        default:
            if (g_show_status != 1) {
                g_show_status = 1;

                display_not_signed();
                display_clear_1N();
                display_icc_err_invalid();
            }

            if (g_signIn) {
                g_signIn = FALSE;

                save_status(B_SIGN);
            }
            break;
        }
    }
}

void test_card() {
    if (MODE_REMARK == g_mode || MODE_VOTE == g_mode || MODE_VOTE5 == g_mode) {
        if (g_signIn && SIGN_MODE_ICC == g_sign_mode) { // 核对卡号机号密码
            if (!CARD_INSERTED() && !g_hasVoted) { // 无卡
                g_card_inserted = 0;
                g_lock = TRUE;

                if (++g_timer3 >= 65500) {
                    g_timer3 = 0;

                    display_clear_1N();
                    display_icc_no_card();
                }
            }

            if (CARD_INSERTED() && 0 == g_card_inserted) { // 插卡
                uint8 result = check_card_valid();
                switch (result) {
                case 1:
                    g_card_inserted = 1;
                    g_card_valid = 1;

                    if (!g_hasVoted) {
                        g_lock = FALSE;
                        if (MODE_VOTE5 == g_mode) { // 快速选举
                            display_press_number();
                        } else if (MODE_REMARK == g_mode
                                || (MODE_VOTE == g_mode && 0 == g_vote_mode)) { // 评议或普通表决
                            if (1 == g_limit_one_action) {
                                display_valid_on_first_press();
                            } else {
                                display_valid_on_last_press();
                            }
                        } else if (MODE_VOTE == g_mode && 1 == g_vote_mode) { // 普通选举
                            display_vote_number();
                        }
                    }
                    break;

                case 2:
                    g_card_inserted = 1;
                    g_card_valid = 0;
                    if (!g_hasVoted) {
                        g_lock = TRUE;

                        display_icc_err_wrong_no();
                    }
                    break;

                case 3:
                    g_card_inserted = 1;
                    g_card_valid = 0;
                    if (!g_hasVoted) {
                        g_lock = TRUE;
                        display_clear_1N();
                        display_icc_err_invalid();
                    }
                    break;

                default:
                    break;
                }
            }
        } else if (g_signIn && SIGN_MODE_ICC_BACK == g_sign_mode) {
            if (!CARD_INSERTED() && !g_hasVoted) { // 无卡
                g_card_inserted = 0;
                g_lock = FALSE;

                if (++g_timer3 >= 65500) {
                    g_timer3 = 0;

                    display_clear_1N();
                    display_icc_no_card();
                }
            }

            if (CARD_INSERTED() && 0 == g_card_inserted) { // 插卡
                uint8 result = check_card_valid();
                switch (result) {
                case 1:
                    g_card_inserted = 1;
                    if (!g_hasVoted) {
                        if (ICC_BUF[0] == g_cardNo_h && ICC_BUF[1] == g_cardNo_l) {
                            g_lock = FALSE;
                            if (MODE_VOTE5 == g_mode) { // 快速选举
                                display_press_number();
                            } else if (MODE_REMARK == g_mode
                                    || (MODE_VOTE == g_mode && 0 == g_vote_mode)) { //评议或普通表决
                                if (1 == g_limit_one_action) {
                                    display_valid_on_first_press();
                                } else {
                                    display_valid_on_last_press();
                                }
                            } else if (MODE_VOTE == g_mode && 1 == g_vote_mode) { // 普通选举
                                display_vote_number();
                            }
                        } else {
                            g_lock = TRUE;
                            display_clear_1N();
                            display_icc_err_wrong_no();
                        }
                    }
                    break;

                case 2:
                    g_card_inserted = 1;
                    if (!g_hasVoted) {
                        if (ICC_BUF[0] == g_cardNo_h && ICC_BUF[1] == g_cardNo_l) {
                            g_lock = FALSE;
                            if (MODE_VOTE5 == g_mode) { // 快速选举
                                display_press_number();
                            } else if (MODE_REMARK == g_mode
                                    || (MODE_VOTE == g_mode && 0 == g_vote_mode)) { //评议或普通表决
                                if (1 == g_limit_one_action) {
                                    display_valid_on_first_press();
                                } else {
                                    display_valid_on_last_press();
                                }
                            } else if (MODE_VOTE == g_mode && 1 == g_vote_mode) { // 普通选举
                                display_vote_number();
                            }
                        } else {
                            g_lock = TRUE;
                            display_clear_1N();
                            display_icc_err_wrong_no();
                        }
                    }
                    break;

                case 3:
                    g_card_inserted = 1;
                    if (!g_hasVoted) {
                        g_lock = TRUE;
                        display_clear_1N();
                        display_icc_err_invalid();
                    }
                    break;

                default:
                    break;
                }
            }
        }
    }
}

void process_vote() {
    if (!g_lock) {
        if (KEYCODE_KEY2 == g_keyValue) { // 赞成
            g_keyValue = 0;

            enable_led();

            if (g_available > 0) { // 表决
                if (g_vote != VOTE_APPROVE) {
                    g_vote = VOTE_APPROVE;

                    g_show_wait = TRUE;
                    g_timer1 = 0;

                    if (g_limit_one_action) {
                        g_lock = TRUE;
                    }

                    display_clear_2N();
                    display_line();
                    lcd_display_string(STR_VOTE_YES, 2, LCD_START_COLUMN, FONT2432);

                    save_status(B_VOTE);
                }
            }
        } else if (KEYCODE_KEY3 == g_keyValue) { // 反对
            g_keyValue = 0;

            enable_led();

            if (g_vote != VOTE_REJECT) {
                g_vote = VOTE_REJECT;

                g_show_wait = TRUE;
                g_timer1 = 0;

                if (g_limit_one_action) {
                    g_lock = TRUE;
                }

                display_clear_2N();
                display_line();
                lcd_display_string(STR_VOTE_NO, 2, LCD_START_COLUMN, FONT2432);

                save_status(B_VOTE);
            }
        } else if (KEYCODE_KEY4 == g_keyValue) { // 弃权
            g_keyValue = 0;

            enable_led();

            if (g_vote != VOTE_ABSTAIN) {
                g_vote = VOTE_ABSTAIN;

                g_show_wait = TRUE;
                g_timer1 = 0;

                if (g_limit_one_action) {
                    g_lock = TRUE;
                }

                display_clear_2N();
                display_line();
                lcd_display_string(STR_VOTE_ABSTAIN, 2, LCD_START_COLUMN, FONT2432);

                save_status(B_VOTE);
            }
        }
    }
}

void process_vote5() {
    if (!g_lock) {
        if (MODE_VOTE5 == g_mode) { // 选举
            if (KEYCODE_KEY1 == g_keyValue) {
                g_keyValue = 0;

                enable_led();

                if (g_candidate >= 1) {
                    if (g_vote != VOTE5_1) {
                        g_vote = VOTE5_1;
                        g_show_wait = TRUE;
                        g_timer1 = 0;

                        display_vote5(1);
                        save_status(B_VOTE);
                    }
                }
            } else if (KEYCODE_KEY2 == g_keyValue) {
                g_keyValue = 0;

                enable_led();

                if (g_candidate >= 2) {
                    if (g_vote != VOTE5_2) {
                        g_vote = VOTE5_2;
                        g_show_wait = TRUE;
                        g_timer1 = 0;

                        display_vote5(2);
                        save_status(B_VOTE);
                    }
                }
            } else if (KEYCODE_KEY3 == g_keyValue) {
                g_keyValue = 0;

                enable_led();

                if (g_candidate >= 3) {
                    if (g_vote != VOTE5_3) {
                        g_vote = VOTE5_3;
                        g_show_wait = TRUE;
                        g_timer1 = 0;

                        display_vote5(3);
                        save_status(B_VOTE);
                    }
                }
            } else if (KEYCODE_KEY4 == g_keyValue) {
                g_keyValue = 0;

                enable_led();

                if (g_candidate >= 4) {
                    if (g_vote != VOTE5_4) {
                        g_vote = VOTE5_4;
                        g_show_wait = TRUE;
                        g_timer1 = 0;

                        display_vote5(4);
                        save_status(B_VOTE);
                    }
                }
            } else if (KEYCODE_KEY5 == g_keyValue) {
                g_keyValue = 0;

                enable_led();

                if (g_candidate >= 5) {
                    if (g_vote != VOTE5_5) {
                        g_vote = VOTE5_5;
                        g_show_wait = TRUE;
                        g_timer1 = 0;

                        display_vote5(5);
                        save_status(B_VOTE);
                    }
                }
            }
        }
    }
}

void process_remark() {
    if (!g_lock) {
        if (MODE_REMARK == g_mode) {
            if (KEYCODE_KEY2 == g_keyValue) { // SATISFIED
                g_keyValue = 0;

                enable_led();

                if (g_remark != REMARK_SATISFIED) {
                    g_remark = REMARK_SATISFIED;
                    g_show_wait = TRUE;
                    g_timer1 = 0;

                    if (g_limit_one_action) {
                        g_lock = TRUE;
                    }

                    display_clear_2N();
                    display_line();
                    lcd_display_string(STR_REMARK_SATISFIED, 2, LCD_START_COLUMN, FONT2432);

                    save_status(B_REMARK);
                }
            } else if (KEYCODE_KEY3 == g_keyValue) { // ADEQUATE
                g_keyValue = 0;

                enable_led();

                if (g_remark != REMARK_ADEQUATE) {
                    g_remark = REMARK_ADEQUATE;
                    g_show_wait = TRUE;
                    g_timer1 = 0;

                    if (g_limit_one_action) {
                        g_lock = TRUE;
                    }

                    display_clear_2N();
                    display_line();
                    lcd_display_string(STR_REMARK_ADEQUATE, 2, LCD_START_COLUMN, FONT2432);

                    save_status(B_REMARK);
                }
            } else if (KEYCODE_KEY4 == g_keyValue) { // DISAPPOINTED
                g_keyValue = 0;

                enable_led();

                if (g_remark != REMARK_DISAPPOINTED) {
                    g_remark = REMARK_DISAPPOINTED;
                    g_show_wait = TRUE;
                    g_timer1 = 0;

                    if (g_limit_one_action) {
                        g_lock = TRUE;
                    }

                    display_clear_2N();
                    display_line();
                    lcd_display_string(STR_REMARK_DISAPPOINTED, 2, LCD_START_COLUMN, FONT2432);

                    save_status(B_REMARK);
                }
            }
        }
    }
}

void process_discuss_clear() {
    if (g_lock)
        return;

    if (MODE_DISCUSS == g_mode && KEYCODE_KEY7 == g_keyValue && 0x20 == g_cameraNo_vice) { // 打断按键
        g_keyValue = 0;

        if (g_chairman_press) {
            g_chairman_press = FALSE;
            operate_laser(LASER_STATIC);
            send_package(0xFB, 0xFC, 0x2C, 0x00, 0x00);
        } else {
            uint8 i;
            for (i = 0; i < 10; i++) {
                send_package_1(0xFB, 0x00, 0x0C, 0x00, 0x00, 0x00);
                _delay_ms(50);
            }
        }

        g_clear_phone = TRUE;
    }
}

void process_discuss() {
    if (MODE_DISCUSS == g_mode && (KEYCODE_KEY6 == g_keyValue || (KEYCODE_KEY7 == g_keyValue && (0x10 == g_cameraNo_vice || 0x00 == g_cameraNo_vice)))) {
        g_keyValue = 0;

        enable_led();

        if (!g_lock) {
            if (DISCUSS_STATE_CLOSE == g_discuss_state
                    || DISCUSS_STATE_APPLY == g_discuss_state) {
                g_discuss_state = DISCUSS_STATE_APPLY;

                display_discuss_apply();
            } else if (DISCUSS_STATE_OPEN == g_discuss_state) {
                // do nothing
            }

            g_send_enable = TRUE;
            // g_send_permit = TRUE;
            g_retry = 0;
        }
    }
}

void process_change_address() {
    if (KEYCODE_KEY6 == g_keyValue || KEYCODE_KEY7 == g_keyValue) {
        g_keyValue = 0;
        g_pressKeyNeeded = FALSE;

        g_model = g_model_buf;
        g_si_model = g_si_model_buf;

        operate_laser(LASER_OFF);

        char szContent[6];

        g_addr_l = g_addr_l_buf;
        g_addr_h = g_addr_h_buf;
        g_addr_full = g_addr_full_buf;

        sprintf(szContent, "%04d", g_addr_full);

        save_status(B_MODEL | B_SI_MODEL | B_ADDR_L | B_ADDR_H);

        display_clear_2N();
        lcd_display_string(szContent, 2, LCD_START_COLUMN, FONT1616);
    }
}
