#ifndef _BOARD_FUNC__
#define _BOARD_FUNC__

/*------��������------*/
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
//�ٲó�Ϊ����,����START�ź�
//����ֵ:	0��ʾ�ɹ�, 1��ʾʧ��
uint8 twi_start(void);
//ֹͣͨ��,����STOP�ź�
void twi_stop(void);
//�����ӻ���ַ��д����,��SLA+W,����MTģʽ
//����ֵ:	0��ʾ�ɹ�, 1��ʾʧ��
uint8 twi_to_write(void);
//�����ӻ���ַ�������,��SLA+R,����MRģʽ
//����ֵ:	0��ʾ�ɹ�, 1��ʾʧ��
uint8 twi_to_read(void);
//��ӻ�������
//����ֵ: 0��ʾ�ӵ�ACK, 1��ʾʧ��, 2��ʾ�ӵ�NOT ACK
uint8 twi_send(uint8 data);
//���մӻ�����������
//����ֵ: 0��ʾ�ӵ�ACK, 1��ʾʧ��, 2��ʾ�ӵ�NOT ACK
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
// ϵͳ��ʼ���ܺ���
void init_devices(void);

/*************************************************************
 * Pin operation
 *************************************************************/
//////////////////////////////////////////////////////////////
// PORTA
#define key_pressing()      (0 == (PINA & 0x02))    // ������⣬�͵�ƽ������

#define KEY_164_CLK         PA(2)
#define KEY_164_DATA        PA(3)

//////////////////////////////////////////////////////////////
// PORTB
#define LED_BACK_ON()       (PORTB |=  (1<<0))      // ������������ߵ�ƽ����
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
 * e.g. ������: 0x00
 *      �����: 0x01
 *      һ���: 0x02
 */
extern uint8 g_model;
/*
 * simultaneous interpreting
 * ͬ��ģʽ:
 * [0x10] ��ͬ������
 */
extern uint8 g_si_model;
/* ������ַ����������ش� */
extern uint8 g_addr_back;
/* ������ַ�����ֽ� */
extern uint8 g_addr_h;
/* ������ַ�����ֽ� */
extern uint8 g_addr_l;
/*
 * Running State
 * 0: �Լ�
 * 1: �����õ�
 * 2: д��
 * 3: ��ǩ��
 * 4: ���
 * 5: ����
 * 6: �޸ĵ�ַ
 * 7: ����
 * 8: ѡ��
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
 * 0: ����
 * 1: ��λ�忨
 * 2: ����忨
 */
extern uint8 g_sign_mode;
/*
 * Vote state
 * 0: δ����
 * 1: �޳�
 * 2: ��Ȩ
 * 3: ����
 */
extern uint8 g_vote;
/*
 * Vote mode
 * 0: ��ͨ���
 * 1: ��ѡ���
 */
extern uint8 g_vote_mode;
/*
 * If voted
 * 0: δ���
 * 1: �ѱ��
 */
extern uint8 g_hasVoted;
/*
 * Remark state
 * 0: δ��
 * 1: �ǳ�����
 * 2: ����
 * 3: ��������
 * 4: ������
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
/* ��ѡ���� */
extern uint8 g_candidate;
/* ��ѡ���� */
extern uint8 g_available;
/* Һ�����Աȶ� */
extern uint8 g_lcd_contrast;
/* ICC���� */
extern uint8 g_cardNo_h;
extern uint8 g_cardNo_l;
/* ICC���� */
extern uint8 g_password1, g_password2;

#endif
