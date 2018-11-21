#ifndef _BOARD_FUNC__
#define _BOARD_FUNC__

/*------函数定义------*/
/*************************************************************
 * SPI
 *************************************************************/
void  spi_init(void);
void  spi_write(uint8 sData);
uint8 spi_read(void);

/*************************************************************
 * TWI
 *************************************************************/
#define TW_OK               0
#define TW_ERROR            1
#define TW_NACK             2

extern uint8 Twi_SLA;
/*************************************************************
 * I2C Slave Address Define
 *************************************************************/
#define SI4700_SLA          0x20
#define CS8416_SLA          0x22
#define CS48540_SLA         0x24
#define TFA9812_SLA         0x26
#define DARR80_SLA          0x80

void twi_init(void);
//仲裁成为主机,发送START信号
//返回值:	0表示成功, 1表示失败
uint8 twi_start(void);
//停止通信,发送STOP信号
void twi_stop(void);
//发出从机地址与写命令,即SLA+W,进入MT模式
//返回值:	0表示成功, 1表示失败
uint8 twi_to_write(void);
//发出从机地址与读命令,即SLA+R,进入MR模式
//返回值:	0表示成功, 1表示失败
uint8 twi_to_read(void);
//向从机发数据
//返回值: 0表示接到ACK, 1表示失败, 2表示接到NOT ACK
uint8 twi_send(uint8 data);
//接收从机发来的数据
//返回值: 0表示接到ACK, 1表示失败, 2表示接到NOT ACK
uint8 twi_receive(uint8 *data);
uint8 twi_SendAck(uint8 Ack);
uint8 twi_WriteBuffer(uint8 SubAddr, uint8 *Buff, uint8 cnt, uint8 MemType);
uint8 twi_ReadBuffer(uint8 SubAddr, uint8 *Buff, uint8 cnt);

/*************************************************************
 * UART
 *************************************************************/
#define SYNC_BYTE   0xFF
#define START_BYTE  0x55

// Define Receive Packet State
typedef enum
{
    FSA_INIT,
    FSA_START,
    FSA_LENGTH,
    FSA_LINGO,
    FSA_COMMAND,
    FSA_DATA,
    FSA_CHKSUM
} RxState_t;

// Define Command 
#define CMD_NONE        0
#define CMD_ACK         1
#define CMD_GET_PIO     2
#define CMD_SET_PIO     3

void  usart_init(void);
uint8 usart_recvByte(void);
void  usart_sendSeq(uint8 *string, uint8 len);
uint8 MakeChecksum(uint8 *buff, uint8 len);

/*************************************************************
 * eeprom setting
 *************************************************************/
void restore_status();
void save_status(uint32 items);

/*************************************************************
 * System initialize
 *************************************************************/
// 系统初始化总函数
void init_devices(void);

/*************************************************************
 * Pin operation
 *************************************************************/
//////////////////////////////////////////////////////////////
// PORTA
#define key_pressing()      (0 == (PINA & 0x02))    // 按键检测，低电平被按下

#define KEY_164_CLK         PA(2)
#define KEY_164_DATA        PA(3)

//////////////////////////////////////////////////////////////
// PORTB
#define LED_BACK_ON()       (PORTB |=  (1<<0))      // 背光板驱动，高电平点亮
#define LED_BACK_OFF()      (PORTB &= ~(1<<0))

#define AUDIO_ON()          (PORTB |=  (1<<1))
#define AUDIO_OFF()         (PORTB &= ~(1<<1))

#define LASER_ON()          (PORTB |=  (1<<3))
#define LASER_OFF()         (PORTB &= ~(1<<3))

//////////////////////////////////////////////////////////////
// PORTD
#define MAX487_TXD_EN()     (PORTD |=  (1<<2))
#define MAX487_RXD_EN()     (PORTD &= ~(1<<2))

/*************************************************************
 * Global variable
 *************************************************************/
/*
 * Device Mode
 *
 * e.g. 单讨论: 0x00
 *      单表决: 0x01
 *      一体机: 0x02
 */
extern uint8 g_model;
/*
 * simultaneous interpreting
 * 同传模式:
 * [0x10] 有同传功能
 */
extern uint8 g_si_model;
/* 主机地址，用于命令回传 */
extern uint8 g_addr_back;
/* 本机地址，高字节 */
extern uint8 g_addr_h;
/* 本机地址，低字节 */
extern uint8 g_addr_l;
/*
 * Running State
 * 0: 自检
 * 1: 按键敲到
 * 2: 写卡
 * 3: 卡签到
 * 4: 表决
 * 5: 评议
 * 6: 修改地址
 * 7: 讨论
 * 8: 选举
 */
extern uint8 g_mode;
/*
 * Signing state
 * FALSE: not signed in
 * TRUE: signed in
 */
extern uint8 g_signIn;
/*
 * Sign mode
 * 0: 按键
 * 1: 定位插卡
 * 2: 任意插卡
 */
extern uint8 g_sign_mode;
/*
 * Vote state
 * 0: 未按键
 * 1: 赞成
 * 2: 弃权
 * 3: 反对
 */
extern uint8 g_vote;
/*
 * Vote mode
 * 0: 普通表决
 * 1: 多选表决
 */
extern uint8 g_vote_mode;
/*
 * If voted
 * 0: 未表决
 * 1: 已表决
 */
extern uint8 g_hasVoted;
/*
 * Remark state
 * 0: 未按
 * 1: 非常满意
 * 2: 满意
 * 3: 基本满意
 * 4: 不满意
 */
extern uint8 g_remark;
/*
 * Lock state
 * 0: unlocked
 * 1: locked
 */
extern uint8 g_lock;
/*
 * Sign in lock state
 * 0: unlocked
 * 1: locked
 */
extern uint8 g_lock_sign;
/*
 * Discussion state
 * 0: close
 * 1: open
 * 2: apply
 */
extern uint8 g_discuss_state;
/*  */
extern uint8 g_limit_one_action;
/* Camera number */
extern uint8 g_cameraNo;
/* Camera number for vice chairman */
extern uint8 g_cameraNo_vice;
/* Position */
extern uint8 g_position;
/* 候选人数 */
extern uint8 g_candidate;
/* 可选人数 */
extern uint8 g_available;
/* 液晶屏对比度 */
extern uint8 g_lcd_contrast;
/* ICC卡号 */
extern uint8 g_cardNo_h;
extern uint8 g_cardNo_l;
/* ICC密码 */
extern uint8 g_password1, g_password2;

#endif
