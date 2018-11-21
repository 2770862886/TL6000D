#include "config.h"

#define USART_RXD_BUF_SIZE (10)
#define USART_CMD_BUF_SIZE (8)

const uint8 CHECKSUM_ITEMS[] = { 2, 3, 4, 5, 6, 8, 9 };
/* Uart 数据缓冲区 */
uint8 USART_RXD_BUF[USART_RXD_BUF_SIZE];
/*
 * 指令缓冲区
 * 0: addr_host
 * 1: addr_l
 * 2: command
 * 3: data
 * 4: data
 * 5: data
 * 6: addr_h
 * 7: check sum
 */
uint8 CMD_BUF[USART_CMD_BUF_SIZE];
/* 缓冲区指针 */
uint8 g_rxd_pointer = 0;
/* 标志接收完成一个完整包 */
uint8 g_new_frame;      // just received an complete frame
/* icc card read buffer */
uint8 ICC_BUF[16];
/* indicate the device is in online state*/
uint8 g_online;
/* 按下表决键后等待时间 200 */
uint8 g_timer1 = 0;     // times1
/* 背光延时关闭 400 */
uint16 g_timer2 = 0;    // times4
/* icc卡检测计时 65500 */
uint16 g_timer3 = 0;    // times3
/* 咪灯闪烁计时 40 */
uint8 g_timer4 = 0;     // times6
/* 按下签到键计时 250 */
uint8 g_timer5 = 0;     // times7
/* 代表版本发言申请延时 */
uint8 g_timer6 = 0;
/*
 * 咪灯模式
 * LASER_OFF:               关闭
 * LASER_STATIC:            不闪烁
 * LASER_BLINK:             一直闪烁
 * LASER_BLINK_SPEC_TIMES:  闪烁16次后停止
 */
Laser_mode_t g_laser_mode = 0;
/* 咪灯状态 1:亮 0:熄 */
uint8 g_laser_on = 0;
/* 咪灯闪烁次数 */
uint8 g_laser_blink_num = 0;
/* 话筒开关 */
Audio_mode_t g_audio_on = AUDIO_OFF;
/* 是否收到总签到 TRUE: 收到; FALSE: 未收到 */
uint8 g_group_sign = 0;
/* 是否收到总表决 TRUE: 收到 FALSE: 未收到 */
uint8 g_group_vote = 0;
/* 是否显示信息 */
uint8 g_show_info = 0;
/* 显示智能卡状态信息 */
uint8 g_show_status;
/* 显示等待提示 */
uint8 g_show_wait = 0;
/* 是否需要按键按下 */
uint8 g_pressKeyNeeded = 0;
/* 按键键值 */
uint8 g_keyValue = 0;
/* LED背光是否打开 */
uint8 g_led_enabled = 0;
/* 修改工作模式和同传类型的缓存变量 */
uint8 g_model_buf;
uint8 g_si_model_buf;
/* 全地址变量 */
uint16 g_addr_full;
/* 修改地址缓存变量 */
uint8 g_addr_l_buf;
uint8 g_addr_h_buf;
uint16 g_addr_full_buf;
/* 主席表决对象地址 */
uint8 g_obj_addr_l;
uint8 g_obj_addr_h;
/* 是否发送指令关闭其它话筒 */
uint8 g_clear_phone;
/* 智能卡是否插入 */
uint8 g_card_inserted;
/* 卡是否有效 */
uint8 g_card_valid;
/* 主席批准功能 1: 进入主席批准功能 0：未进入主席批准功能*/
uint8 g_chairman_press;
/* 重试次数 */
uint8 g_retry;
/* 是否可以发送 */
uint8 g_send_permit;
/* 发送使能 */
uint8 g_send_enable;

/****************************************************************
 * 函数定义
 ****************************************************************/
inline uint8 make_checksum(uint8 *pBuf) {
    uint8 cs = 0, i;

    const uint8 addr_bck = pBuf[CHECKSUM_ITEMS[0]];

    for (i = 0; i < 6; i++) {
        cs += pBuf[CHECKSUM_ITEMS[i]];
    }

    return (cs == pBuf[CHECKSUM_ITEMS[i]])
            && (0xFB == addr_bck || 0xFC == addr_bck);
}

ISR(TIMER0_OVF_vect) {
    g_timer1 ++;
    g_timer2 ++;

    if (g_send_enable && MODE_DISCUSS == g_mode) {
        g_timer6 ++;

        if (g_retry <= 3) {
            if (g_timer6 > ((g_addr_l & 0x08) + 25)) {
                g_send_permit = TRUE;
                g_timer6 = 0;
            }
        } else {
            if (g_timer6 > (g_addr_l + 25)) {
                g_send_permit = TRUE;
                g_timer6 = 0;
            }
        }
    }

    if (LASER_BLINK == g_laser_mode) {
        g_timer4 ++;
        if (g_timer4 >= 40) {
            if (g_laser_on) {
                LASER_OFF();
                g_laser_on = FALSE;
            } else {
                LASER_ON();
                g_laser_on = TRUE;
            }
            g_timer4 = 0;
        }
    } else if (LASER_BLINK_SPEC_TIMES == g_laser_mode) {
        g_timer4 ++;
        if (g_laser_blink_num > 16) {
            g_laser_mode = LASER_OFF;
            g_laser_blink_num = 0;

            LASER_OFF();
            g_laser_on = FALSE;

            LED_BACK_OFF();
        } else {
            if (g_timer4 >= 40) {
                g_laser_blink_num ++;
                if (g_laser_on) {
                    LASER_OFF();
                    g_laser_on = FALSE;

                    // LED_BACK_OFF();
                } else {
                    LASER_ON();
                    g_laser_on = TRUE;

                    // LED_BACK_ON();
                }
                g_timer4 = 0;
            }
        }
    } else if (LASER_STATIC == g_laser_mode) {
        if (DISCUSS_STATE_OPEN == g_discuss_state) {
            LASER_ON();
            g_laser_on = TRUE;
        } else {
            LASER_OFF();
            g_laser_on = FALSE;

            g_laser_mode = LASER_OFF;
        }
    }

    // FIXME
    /*
    if (g_pressKeyNeeded) {
        g_timer5 ++;
        if (g_timer5 > 250) {
            g_sign_press = 1;

//            operate_laser(LASER_STATIC);

            g_timer5 = 0;
        }
    } else {
        g_timer5 = 0;

//        operate_laser(LASER_OFF);
    }
    */

    TCNT0 = 200;
}

ISR(USART_RXC_vect) {
    UCSRB &= ~(1 << RXCIE);

    uint8 data = UDR;

    switch (g_rxd_pointer) {
    case 0:
    case 1:
        if (0xAA == data) {
            g_rxd_pointer ++;
        } else {
            g_rxd_pointer = 0;
        }
        break;

    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        USART_RXD_BUF[g_rxd_pointer++] = data;

        if (g_rxd_pointer > 9 && make_checksum(USART_RXD_BUF)) {
            // skip two sync byte
            memcpy(CMD_BUF, USART_RXD_BUF + 2, USART_CMD_BUF_SIZE);

            g_new_frame = TRUE;
            g_rxd_pointer = 0;
        }
        break;

    default:
        g_rxd_pointer = 0;
        break;
    }

    UCSRB |= (1 << RXCIE);
}

uint8 onCommand() {
    if (!g_new_frame)
        return FALSE;

    g_addr_back = CMD_BUF[0];               // addr host

    const uint8 addr_l = CMD_BUF[1];        // addr low
    const uint8 addr_h = CMD_BUF[6];        // addr high

    const uint8 cmd = CMD_BUF[2];           // cmd
    const uint8 data1 = CMD_BUF[3];         // data1
    const uint8 data2 = CMD_BUF[4];         // data2
//    const uint8 data3 = CMD_BUF[5];         // data3

    switch (cmd) {
    case COM_ONLINE:
        LOG_PRINT_INFO("COM_ONLINE");
        display_connected();
        g_online = TRUE;
        g_keyValue = 0;
        break;

    case COM_OFFLINE:
        LOG_PRINT_INFO("COM_OFFLINE");
        display_not_connected();
        g_online = FALSE;
        g_keyValue = 0;
        break;

    case COM_INIT:
        LOG_PRINT_INFO("COM_INIT");
        function_init(addr_l, addr_h);
        break;

    case COM_SIGN_KEY:
        LOG_PRINT_INFO("COM_SIGN_KEY");
        function_sign_key(addr_l, addr_h, data2);
        break;

#ifdef WITH_SMART_CARD
    case COM_SIGN_CARD:
        LOG_PRINT_INFO("COM_SIGN_CARD");
        function_sign_card(addr_l, addr_h, data1, data2);
        break;

    case COM_SIGN_CARD_BACK:
        LOG_PRINT_INFO("COM_SIGN_CARD_BACK");
        function_sign_card_back(addr_l, addr_h, data1, data2);
        break;
#endif

    case COM_SIGN_END:
        LOG_PRINT_INFO("COM_SIGN_END");
        function_sign_end(addr_l, addr_h);
        break;

    case COM_DOWNLOAD_CAMERA:
        LOG_PRINT_INFO("COMD_DOWNLOAD_CAMERA");
        function_download_camera(addr_l, addr_h, data1, data2);
        break;

    case COM_DOWNLOAD_CAMERA_VICE_CHAIRMAN:
        LOG_PRINT_INFO("COM_DOWNLOAD_CAMERA_VICE_CHAIRMAN");
        function_download_camera_vice_chairman(addr_l, addr_h, data1);
        break;

    case COM_CLS_SCREEN:
        LOG_PRINT_INFO("COM_CLS_SCREEN");
        function_clear_screen();
        break;

    case COM_CONTRAST_DEFAULT:
        LOG_PRINT_INFO("COM_DEFAULT_CONTRAST");
        function_contrast_default(addr_l, addr_h);
        break;

    case COM_CONTRAST_INC:
        LOG_PRINT_INFO("COM_UP_CONTRAST");
        function_contrast_up(addr_l, addr_h);
        break;

    case COM_CONTRAST_DEC:
        LOG_PRINT_INFO("COM_DOWN_CONTRAST");
        function_contrast_down(addr_l, addr_h);
        break;

    case COM_SEARCH:
        LOG_PRINT_INFO("COM_SEARCH");
        function_search(addr_l, addr_h);
        break;

#ifdef WITH_SMART_CARD
    case COM_ONE_SIGN:
        LOG_PRINT_INFO("COM_ONE_SIGN");
        function_one_sign(addr_l, addr_h, data1, data2);
        break;

    case COM_ONE_SIGN_BACK:
        LOG_PRINT_INFO("COM_ONE_SIGN_BACK");
        function_one_sign_back(addr_l, addr_h, data1, data2);
        break;
#endif

    case COM_CHG_ADDRESS:
        LOG_PRINT_INFO("COM_CHG_ADDRESS");
        function_change_address(data2, addr_h, data1);
        break;

    case COM_PASS:
        LOG_PRINT_INFO("COM_PASS");
        function_pass(addr_l, addr_h);
        break;

    default:
        break;
    }

    if (MODEL_DISCUSS == g_model || MODEL_ALL_IN_ONE == g_model) {
        switch (cmd) {
        case COM_DISCUSS_START:
            LOG_PRINT_INFO("COM_DISCUSS_START");
            function_discuss_start(addr_l, addr_h, data2);
            break;

        case COM_DISCUSS_OPEN:
            LOG_PRINT_INFO("COM_DISCUSS_OPEN");
            function_discuss_open(addr_l, addr_h);
            break;

        case COM_DISCUSS_CLOSE:
            LOG_PRINT_INFO("COM_DISCUSS_CLOSE");
            function_discuss_close(addr_l, addr_h);
            break;

        case COM_DISCUSS_WAIT:
            LOG_PRINT_INFO("COM_DISCUSS_WAIT");
            function_discuss_wait(addr_l, addr_h);
            break;

        case COM_DISCUSS_WAIT2:
            LOG_PRINT_INFO("COM_DISCUSS_WAIT2");
            function_discuss_wait2(addr_l, addr_h);
            break;

        default:
            break;
        }
    }

    if (MODEL_VOTE == g_model || MODEL_ALL_IN_ONE == g_model) {
        switch (cmd) {
        case COM_VOTE1:
            LOG_PRINT_INFO("COM_VOTE1");
            function_vote(addr_l, addr_h, data1, data2);
            break;

        case COM_VOTE5:
            LOG_PRINT_INFO("COM_VOTE5");
            function_vote5(addr_l, addr_h, data1, data2);
            break;

        case COM_VOTE5_END:
            LOG_PRINT_INFO("COM_VOTE5_END");
            function_vote5_end(addr_l, addr_h);
            break;

        case COM_LOCK_KEY:
            LOG_PRINT_INFO("COM_LOCK_KEY");
            g_lock = TRUE;
            save_status(B_LOCK);
            break;

        case COM_REMARK:
            LOG_PRINT_INFO("COM_REMARK");
            function_remark(addr_l, addr_h, data1, data2);
            break;

        default:
            break;
        }
    }

    g_new_frame = FALSE;

    return TRUE;
}
/*
void dispatchKeyEvent() {
    uint16 last_code_count = 0, last_code_times = 0;

    uint8 i, shift_data = 0xFF;

    KEY_164_DATA = 1;

    while (shift_data) {
        // Pulse out
        KEY_164_CLK = 1;
        NOP();
        NOP();
        NOP();
        KEY_164_CLK = 0;
        NOP();
        NOP();
        NOP();

        shift_data >>= 1;
    }

    shift_data = 0x01;

    while (shift_data) {
        KEY_164_DATA = shift_data;

        // Pulse out
        KEY_164_CLK = 1;
        NOP();
        NOP();
        NOP();
        KEY_164_CLK = 0;

        // Delay
        for (i = 0; i < 16; i++) {
            NOP();
        }

        // Check feedback
        if (key_pressing()) {
            _delay_ms(50);

            if (key_pressing()) {
                enable_led();

                while (key_pressing() && last_code_times < 50) {
                    while (key_pressing() && last_code_count < 32000) {
                        last_code_count ++;
                    }
                    last_code_times ++;
                    last_code_count = 0;

                    wdt_reset();
                }

                if (last_code_times > 5) {
                    g_keyValue = shift_data;
                    last_code_times = 0;
                    break;
                }
            }
        }

        shift_data <<= 1;
    }

    if (0 == shift_data) {
        g_keyValue = 0;
    }
}
*/


void dispatchKeyEvent() {
    static uint8 last_scan_code = 0;
    static uint8 last_code_count = 0;

    uint8 i, shift_data = 0xFF;

    // All output 1
    shift_data = 0xFF;

    KEY_164_DATA = 1;

    while (shift_data) {
        // Pulse out
        KEY_164_CLK = 1;
        KEY_164_CLK = 0;

        shift_data >>= 1;
    }

    shift_data = 0x01;

    while (shift_data) {
        //KEY_164_DATA = (~shift_data) & 0x01;

        KEY_164_DATA = shift_data;

        // Pulse out
        KEY_164_CLK = 1;
        KEY_164_CLK = 0;

        // Delay
        for (i = 0; i < 16; i++)
            NOP();

        // Check feedback
        if (key_pressing()) {
            if (last_scan_code == shift_data) {
                // Same as last scan result, that's the key!
                if (last_code_count > 50) {
                    g_keyValue = shift_data;

                    last_scan_code = 0;
                    last_code_count = 0;
                    break;
                }

                if (last_code_count < 0xFF)
                    last_code_count ++;
            } else {
                last_scan_code = shift_data;
                last_code_count = 0;
                g_keyValue = 0;
            }
            break;
        }

        shift_data <<= 1;
    }

    if (shift_data == 0) {
        g_keyValue = 0;
        last_scan_code = 0;
        last_code_count = 0;
    }
}

void init_variables() {
    // if the address havn't written, make the address to be default.
    if (g_addr_l == 0 && g_addr_h == 0) {
        g_addr_l = 2;
    }

    g_addr_full = ((uint16) g_addr_h << 8) + g_addr_l;

    // g_lcd_contrast = 0x20;

    g_rxd_pointer = 0;
    g_card_inserted = 1;

    g_group_sign = 0;
    g_group_vote = 0;

    g_led_enabled = 1;

    g_online = FALSE;

    g_keyValue = 0;
    g_pressKeyNeeded = FALSE;

    g_laser_on = FALSE;
    g_laser_mode = LASER_OFF;
    g_laser_blink_num = 0;

    g_audio_on = AUDIO_OFF;

    g_discuss_state = DISCUSS_STATE_CLOSE;

    g_retry = 0;

    // FIXME
    // g_mode = MODE_INIT;
    // g_model = MODEL_DISCUSS;
}

int main() {
    init_devices();
    init_variables();

    lcd_clr(0x00);
    display_logo();
    display_not_connected();

    for (;;) {
        if (g_retry < 10) {
            if (g_send_permit) {
                g_send_permit = FALSE;

                if (DISCUSS_STATE_APPLY == g_discuss_state) {
                    send_package(g_addr_l, DATA_APPLY_TALL, g_cameraNo, g_position, g_addr_h);
                } else if (DISCUSS_STATE_OPEN == g_discuss_state) {
                    send_package(g_addr_l, DATA_CLOSE_TALL, g_cameraNo, g_position, g_addr_h);
                }

                g_retry ++;
            }
        } else {
            g_send_permit = FALSE;
            g_send_enable = FALSE;
            g_retry = 0;

            display_signed_fail();
        }

        onCommand();
        dispatchKeyEvent();

        switch (g_mode) {
        case MODE_SIGN_KEY:
            LOG_PRINT_INFO("MODE_SIGN_KEY");
            process_sign_key();
            break;

        case MODE_SIGN_CARD1:
            LOG_PRINT_INFO("MODE_SIGN_CARD1");
            process_sign_card1();
            break;

        case MODE_SIGN_CARD2:
            LOG_PRINT_INFO("MODE_SIGN_CARD2");
            process_sign_card2();
            break;

        case MODE_VOTE:
            LOG_PRINT_INFO("MODE_VOTE");
            process_vote();
            break;

        case MODE_VOTE5:
            LOG_PRINT_INFO("MODE_VOTE5");
            process_vote5();
            break;

        case MODE_REMARK:
            LOG_PRINT_INFO("MODE_REMARK");
            process_remark();
            break;

        case MODE_DISCUSS:
            LOG_PRINT_INFO("MODE_DISCUSS");
            process_discuss();
            process_discuss_clear();
            break;

        case MODE_CHG_ADDR:
            LOG_PRINT_INFO("CHANGE_ADDRESS");
            process_change_address();
            break;

        default:
            break;
        }

        if (g_show_wait) {
            if (g_timer1 > 200) {
                g_timer1 = 0;
                g_show_wait = FALSE;

                display_clear_2N();
                display_line();
                lcd_display_string(STR_VOTED, 2, LCD_START_COLUMN, FONT2432);
            }
        }

        if (g_led_enabled) {
            if (g_timer2 > 400) {
                g_timer2 = 0;

                disable_led();
            }
        }

        // display_number_u8(t_u8_4, g_send_enable, g_send_permit, t_u8_2);

        wdt_reset();
    }

    return 0;
}
