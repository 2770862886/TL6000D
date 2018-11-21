#ifndef _FUNC_WRAPPER_H__
#define _FUNC_WRAPPER_H__

void enable_led();
void disable_led();

void send_package(uint8 data1, uint8 data2, uint8 data3, uint8 data4, uint8 data5);

void function_init(uint8 addr_l, uint8 addr_h);
void function_sign_key(uint8 addr_l, uint8 addr_h, uint8 signType);
void function_sign_card(uint8 addr_l, uint8 addr_h, uint8 password1, uint8 password2);
void function_sign_card_back(uint8 addr_l, uint8 addr_h, uint8 password1, uint8 password2);
void function_sign_end(uint8 addr_l, uint8 addr_h);
void function_download_camera(uint8 addr_l, uint8 addr_h, uint8 cameraNo, uint8 position);
void function_download_camera_vice_chairman(uint8 addr_l, uint8 addr_h, uint8 cameraNo);
void function_clear_screen();
void function_contrast_default(uint8 addr_l, uint8 addr_h);
void function_contrast_up(uint8 addr_l, uint8 addr_h);
void function_contrast_down(uint8 addr_l, uint8 addr_h);
void function_search(uint8 addr_l, uint8 addr_h);
void function_one_sign(uint8 addr_l, uint8 addr_h, uint8 password1, uint8 password2);
void function_one_sign_back(uint8 addr_l, uint8 addr_h, uint8 password1, uint8 password2);
void function_change_address(uint8 addr_l, uint8 addr_h, uint8 mode);
void function_pass(uint8 addr_l, uint8 addr_h);
void function_discuss_start(uint8 addr_l, uint8 addr_h, uint8 type);
void function_discuss_open(uint8 addr_l, uint8 addr_h);
void function_discuss_close(uint8 addr_l, uint8 addr_h);
void function_discuss_wait(uint8 addr_l, uint8 addr_h);
void function_discuss_wait2(uint8 addr_l, uint8 addr_h);
void function_vote(uint8 addr_l, uint8 addr_h, uint8 data1, uint8 data2);
void function_vote5(uint8 addr_l, uint8 addr_h, uint8 data1, uint8 data2);
void function_vote5_end(uint8 addr_l, uint8 addr_h);
void function_remark(uint8 addr_l, uint8 addr_h, uint8 data1, uint8 data2);

void test_card();

void process_sign_key();
void process_sign_card1();
void process_sign_card2();
void process_vote();
void process_vote5();
void process_remark();
void process_discuss();
void process_discuss_clear();
void process_change_address();
void process_channel();

void chairman_discuss();
void vice_chairman_discuss();

void display_logo();
void display_not_connected();
void display_connected();
void display_signed();
void display_not_signed();
void display_signed_fail();

void display_clear_1N();
void display_clear_2N();
void display_line();

extern uint8 ICC_BUF[16];
extern uint8 g_online;
extern uint8 g_timer1;
extern uint16 g_timer2;
extern uint16 g_timer3;
extern uint8 g_timer4;
extern uint8 g_timer5;
extern uint8 g_timer6;
extern uint8 g_laser_mode;
extern uint8 g_laser_on;
extern uint8 g_laser_blink_num;
extern uint8 g_audio_on;
extern uint8 g_group_sign;
extern uint8 g_group_vote;
extern uint8 g_pressKeyNeeded;
extern uint8 g_keyValue;
extern uint8 g_led_enabled;
extern uint8 g_show_wait;
extern uint8 g_model_buf;
extern uint8 g_si_model_buf;
extern uint8 g_obj_addr_l;
extern uint8 g_obj_addr_h;
extern uint8 g_clear_phone;
extern uint8 g_send_permit;
extern uint8 g_send_enable;
extern uint8 g_addr_l_buf;
extern uint8 g_addr_h_buf;
extern uint16 g_addr_full;
extern uint16 g_addr_full_buf;
extern uint8 g_retry;
extern uint8 g_show_status;
extern uint8 g_card_inserted;
extern uint8 g_card_valid;
extern uint8 g_chairman_press;
/* 通道号 */
// extern uint8 g_channel;
/* 通道设置阶段: 0:通道加减 1:通道重置 */
// extern uint8 g_chl_phrase;
/* 标志是否显示通道状态 */
// extern uint8 g_chl_show;

#endif /* _FUNC_WRAPPER_H__ */
