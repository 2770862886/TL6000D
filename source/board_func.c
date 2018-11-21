#include "config.h"

/*
 * Device Mode
 *
 * 0x00 单讨论
 * 0x01 单表决
 * 0X02 一体机
 */
uint8 g_model;
/*
 * simultaneous interpreting type
 *
 * 同传模式:
 * 0x00 无同传功能
 * 0x10 有同传功能
 */
uint8 g_si_model;
/* 主机地址，用于命令回传 */
uint8 g_addr_back;
/* 本机地址，高字节 */
uint8 g_addr_h;
/* 本机地址，低字节 */
uint8 g_addr_l;
/*
 * Running State
 *
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
uint8 g_mode;
/*
 * Signing state
 *
 * 0: unsigned in
 * 1: signed in
 */
uint8 g_signIn;
/*
 * Signing mode
 *
 * 0: 按键
 * 1: 定位插卡
 * 2: 任意插卡
 */
uint8 g_sign_mode;
/*
 * Vote state
 *
 * 0: 未按键
 * 1: 赞成
 * 2: 反对
 * 3: 弃权
 */
uint8 g_vote;
/*
 * Vote mode
 *
 * VOTE_MODE_SINGLE
 * VOTE_MODE_MULTIPLE
 */
uint8 g_vote_mode;
/*
 * If has voted
 *
 * 0: 未表决
 * 1: 已表决
 */
uint8 g_hasVoted;
/*
 * Remark result
 *
 * REMARK_NOT_PRESS
 * REMARK_SATISFIED
 * REMARK_ADEQUATE
 * REMARK_DISAPPOINTED
 */
uint8 g_remark;
/*
 * Lock state
 *
 * FALSE:   unlocked
 * TRUE:    locked
 */
uint8 g_lock;
/*
 * Sign in lock state
 *
 * 0: unlocked
 * 1: locked
 */
uint8 g_lock_sign;
/*
 * Discussion state
 * 0: close
 * 1: open
 * 2: apply
 */
uint8 g_discuss_state;
/* 是否首次按键有效 */
uint8 g_limit_one_action;
/* Camera number */
uint8 g_cameraNo;
/* Camera number for vice chairman */
uint8 g_cameraNo_vice;
/* Position */
uint8 g_position;
/* 候选人数 */
uint8 g_candidate;
/* 可选人数 */
uint8 g_available;
/* 液晶屏对比度 */
uint8 g_lcd_contrast;
/* icc卡号 */
uint8 g_cardNo_l;
uint8 g_cardNo_h;
/* icc卡密码 */
uint8 g_password1, g_password2;

/********************************************************************
 ** 系统初始化
 ********************************************************************/
/*
 * 端口初始化
 */
void port_init(void) {
    DDRA = 0xFC;        // 0b11111100;
    PORTA = 0xFF;

    DDRB = 0xFF;
    PORTB = 0x00;

    DDRC = 0xFF;
    PORTC = 0x00;

    DDRD = 0xFF;
    PORTD = 0x00;
}

/*
 * 定时器T0初始化
 */
void timer0_init(void) {
    TCCR0 = 0x00;
    TCNT0 = 0x00;
    TCCR0 = (1 << CS02) | (1 << CS00);  // start timer0 with /1024 prescaler
    TIMSK = 1 << TOIE0;
}

/*
 * 定时器T1初始化
 */
void timer1_init(void) {
    TCCR1B = 0x00;          // 停止定时器
    TIMSK |= 0x20;          // 中断允许
    TCNT1H = 0xFF;
    TCNT1L = 0xFF;          // 初始值
    OCR1AH = 0xFE;
    OCR1AL = 0xFF;          // 匹配A值
    OCR1BH = 0xFE;
    OCR1BL = 0xFF;          // 匹配B值
    ICR1H = 0xFF;
    ICR1L = 0xFF;           // 输入捕捉匹配值
    TCCR1A = 0x00;
    TCCR1B = 0x83;          // 启动定时器
}

/********************************************************************
 ** SPI 底层功能函数
 ********************************************************************/
// SPI baud rate = 921.6KHz
void spi_init(void) {
    //DDRB |= BIT(PORT1) | BIT(PORT2);
    //PORTB |= ~BIT(PORT1) | BIT(PORT2);
    SPCR = BIT(SPE) | BIT(MSTR) | BIT(SPR0) | BIT(CPHA);
    SPSR = 0x00;
}

void spi_write(uint8 sData) {
    SPDR = sData;
    while (!(SPSR & BIT(SPIF)))
        ;
    //sData=SPDR;//读从机发送回来的数据
}

uint8 spi_read(void) {
    SPDR = 0xFF;
    while (!(SPSR & BIT(SPIF)))
        ;
    return SPDR;
}

/********************************************************************
 ** TWI 底层功能函数
 ********************************************************************/
uint8 Twi_SLA;

void twi_SetBitrate(uint16 bitrateKHz) {
    uint8 bitrate_div;

    /* set i2c bitrate*/
    /* SCL freq = F_CPU / (16 + 2 * TWBR)) */
    /* for processors with additional bitrate division (mega64) */
    /* SCL freq = F_CPU/(16+2*TWBR*4^TWPS) */
    /* set TWPS to zero */TWSR = 0x00;
    /* calculate bitrate division */
    bitrate_div = ((F_CPU / 1000) / bitrateKHz);
    if (bitrate_div >= 16)
        bitrate_div = (bitrate_div - 16) / 2;
    TWBR = bitrate_div;
}

// TWI初始化函数
// SCL freq = 100KHz
void twi_init(void) {
    TWCR = 0x00;        // 禁止TWI
    twi_SetBitrate(100);
    TWCR = BIT(TWEN);   // 启动TWI  | BIT(TWSTA)
}

// 仲裁成为主机,发送START信号
// 返回值:  0表示成功, 1表示失败
uint8 twi_start(void) {
    TWCR = BIT(TWINT) | BIT(TWEN) | BIT(TWSTA);
    while (!(TWCR & BIT(TWINT)))
        ;
    if ((TW_STATUS != TW_START) && (TW_STATUS != TW_REP_START))
        return TW_ERROR;
    return TW_OK;
}

// 停止通信,发送STOP信号
void twi_stop(void) {
    TWCR = BIT(TWINT) | BIT(TWEN) | BIT(TWSTO);
    while (!(TWCR & BIT(TWSTO)))
        ;
}

// 发出从机地址与写命令,即SLA+W,进入MT模式
// 返回值:	0表示成功, 1表示失败
uint8 twi_to_write(void) {
    TWDR = Twi_SLA & 0xFE;
    TWCR = BIT(TWINT) | BIT(TWEN);
    while (!(TWCR & BIT(TWINT)))
        ;
    if (TW_STATUS != TW_MT_SLA_ACK)
        return TW_ERROR;
    return TW_OK;
}

// 发出从机地址与读命令,即SLA+R,进入MR模式
// 返回值:	0表示成功, 1表示失败
uint8 twi_to_read(void) {
    TWDR = Twi_SLA | 0x01;
    TWCR = BIT(TWINT) | BIT(TWEN);
    while (!(TWCR & BIT(TWINT)))
        ;
    if (TW_STATUS != TW_MR_SLA_ACK)
        return TW_ERROR;
    return TW_OK;
}

// 向从机发数据
// 返回值: 0表示接到ACK, 1表示失败, 2表示接到NOT ACK
uint8 twi_send(uint8 data) {
    TWDR = data;
    TWCR = BIT(TWINT) | BIT(TWEN);
    while (!(TWCR & BIT(TWINT)))
        ;
    if (TW_STATUS == TW_MT_DATA_ACK)
        return TW_OK;
    else if (TW_STATUS == TW_MT_DATA_NACK)
        return TW_NACK;
    return TW_ERROR;
}

// 接收从机发来的数据
// 返回值: 0表示接到ACK, 1表示失败, 2表示接到NOT ACK
uint8 twi_receive(uint8 *data) {
    TWCR = BIT(TWINT) | BIT(TWEN);
    while (!(TWCR & BIT(TWINT)))
        ;
    *data = TWDR;
    if (TW_STATUS == TW_MR_DATA_ACK)
        return TW_OK;
    else if (TW_STATUS == TW_MR_DATA_NACK)
        return TW_NACK;
    return TW_ERROR;
}

// 接收从机发来的数据
// 返回值: 0表示接到ACK, 1表示失败, 2表示接到NOT ACK
uint8 twi_SendAck(uint8 Ack) {
    if (Ack) {
        TWCR = BIT(TWINT) | BIT(TWEN) | BIT(TWEA);
    } else {
        TWCR = BIT(TWINT) | BIT(TWEN);
    }
    while (!(TWCR & BIT(TWINT)))
        ;
    if (TW_STATUS == TW_MR_DATA_ACK)
        return TW_OK;
    else if (TW_STATUS == TW_MR_DATA_NACK)
        return TW_NACK;
    return TW_ERROR;
}

uint8 twi_WriteBuffer(uint8 SubAddr, uint8 *Buff, uint8 cnt, uint8 MemType) {
    uint8 error;

    twi_start();
    error = twi_to_write();
    if (error)
        goto twi_Wr_exit;

    error = twi_send(SubAddr);
    if (error)
        goto twi_Wr_exit;

    while (cnt--) {
        if (MemType)
            error = twi_send(pgm_read_byte(*Buff ++));
        else
            error = twi_send(*Buff++);

        if (error)
            goto twi_Wr_exit;
    }

    twi_Wr_exit: twi_stop();

    return error;
}

uint8 twi_ReadBuffer(uint8 SubAddr, uint8 *Buff, uint8 cnt) {
    uint8 error;

    twi_start();
    error = twi_to_write();
    if (error)
        goto twi_Rd_exit;

    error = twi_send(SubAddr);
    if (error)
        goto twi_Rd_exit;

    twi_stop();

    twi_start();
    error = twi_to_read();
    if (error)
        goto twi_Rd_exit;

    while (--cnt) {
        twi_receive(Buff++);
        twi_SendAck(1);
    }

    twi_receive(Buff++);
    twi_SendAck(0);

    twi_Rd_exit: twi_stop();

    return error;
}

/********************************************************************
 * UART 底层功能函数
 ********************************************************************/
//static int usart_putchar_printf(char data, FILE *stream);
//static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_RW);

void usart_init(void) {
    //stdout = &mystdout;
    UBRRL = UBRR_VALUE;
    UBRRH = UBRR_VALUE >> 8;

    UCSRA = 0x00;
    UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);    // 允许发送和接收，接收完成中断
    UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);  // 8位数据，1位STOP位
}

void usart_sendByte(uint8 data) {
    // Wait for empty transmit buffer
    while ( !(UCSRA & _BV(UDRE)) );
    UDR = data;
}

uint8 usart_recvByte(void) {
    // Wait for incoming data
    while ( !(UCSRA & _BV(RXC)) );
    return UDR;
}

void usart_sendSeq(uint8 *buff, uint8 len) {
    uint8 i;
    for (i = 0; i < len; i++) {
        usart_sendByte(*buff++);
    }
}

/*static*/ int usart_putchar_printf(char data, FILE *stream) {
    if ('\n' == data)
        usart_sendByte('\r');

    usart_sendByte(data);

    return 0;
}

uint8 MakeChecksum(uint8 *buff, uint8 len) {
    uint8 i, result = 0;

    for (i = 0; i < len; i++) {
        result += buff[i];
    }

    result = (~result) + 1;

    return (result);
}

void peripheral_init() {
    AUDIO_OFF();
    LASER_OFF();

    MAX487_RXD_EN();
}

void restore_status() {
    g_model                 = eeprom_read_byte(EEP_ADDR_MODEL);
    g_si_model              = eeprom_read_byte(EEP_ADDR_SI_MODEL);
    g_lcd_contrast          = eeprom_read_byte(EEP_ADDR_CONTRAST);
    g_addr_h                = eeprom_read_byte(EEP_ADDR_ADDRESS_H);
    g_addr_l                = eeprom_read_byte(EEP_ADDR_ADDRESS_L);
    g_mode                  = eeprom_read_byte(EEP_ADDR_MODE);
    g_vote                  = eeprom_read_byte(EEP_ADDR_VOTE);
    g_vote_mode             = eeprom_read_byte(EEP_ADDR_VOTE_MODE);
    g_hasVoted              = eeprom_read_byte(EEP_ADDR_VOTED);
    g_signIn                = eeprom_read_byte(EEP_ADDR_SIGN);
    g_sign_mode             = eeprom_read_byte(EEP_ADDR_SIGN_MODE);
    g_remark                = eeprom_read_byte(EEP_ADDR_REMARK);
    g_lock                  = eeprom_read_byte(EEP_ADDR_LOCK);
    g_lock_sign             = eeprom_read_byte(EEP_ADDR_LOCK_SIGN);
    g_cameraNo              = eeprom_read_byte(EEP_ADDR_CAMERA_NO);
    g_position              = eeprom_read_byte(EEP_ADDR_POSITION);
    g_cardNo_h              = eeprom_read_byte(EEP_ADDR_CARD_NO_H);
    g_cardNo_l              = eeprom_read_byte(EEP_ADDR_CARD_NO_L);
    g_discuss_state         = eeprom_read_byte(EEP_ADDR_DISCUSS_STATE);
    g_password1             = eeprom_read_byte(EEP_ADDR_PASSWORD1);
    g_password2             = eeprom_read_byte(EEP_ADDR_PASSWORD2);
    g_candidate             = eeprom_read_byte(EEP_ADDR_CANDIDATE);
    g_available             = eeprom_read_byte(EEP_ADDR_OPTIONAL);
    g_limit_one_action      = eeprom_read_byte(EEP_ADDR_VALID_ON_FIRST);
    g_cameraNo_vice         = eeprom_read_byte(EEP_ADDR_CAMERA_NO_VICE);
    g_cameraNo              = g_cameraNo | g_cameraNo_vice;
}

void save_status(uint32 items) {
    cli();

    if (B_MODEL & items)            eeprom_write_byte(EEP_ADDR_MODEL, g_model);
    if (B_SI_MODEL & items)         eeprom_write_byte(EEP_ADDR_SI_MODEL, g_si_model);
    if (B_CONTRAST & items)         eeprom_write_byte(EEP_ADDR_CONTRAST, g_lcd_contrast);
    if (B_ADDR_H & items)           eeprom_write_byte(EEP_ADDR_ADDRESS_H, g_addr_h);
    if (B_ADDR_L & items)           eeprom_write_byte(EEP_ADDR_ADDRESS_L, g_addr_l);
    if (B_MODE & items)             eeprom_write_byte(EEP_ADDR_MODE, g_mode);
    if (B_VOTE & items)             eeprom_write_byte(EEP_ADDR_VOTE, g_vote);
    if (B_VOTE_MODE & items)        eeprom_write_byte(EEP_ADDR_VOTE_MODE, g_vote_mode);
    if (B_VOTED & items)            eeprom_write_byte(EEP_ADDR_VOTED, g_hasVoted);
    if (B_SIGN & items)             eeprom_write_byte(EEP_ADDR_SIGN, g_signIn);
    if (B_SIGN_MODE & items)        eeprom_write_byte(EEP_ADDR_SIGN_MODE, g_sign_mode);
    if (B_REMARK & items)           eeprom_write_byte(EEP_ADDR_REMARK, g_remark);
    if (B_LOCK & items)             eeprom_write_byte(EEP_ADDR_LOCK, g_lock);
    if (B_LOCK_SIGN & items)        eeprom_write_byte(EEP_ADDR_LOCK_SIGN, g_lock_sign);
    if (B_CAMERA_NO & items)        eeprom_write_byte(EEP_ADDR_CAMERA_NO, g_cameraNo);
    if (B_POSITION & items)         eeprom_write_byte(EEP_ADDR_POSITION, g_position);
    if (B_CARD_NO_H & items)        eeprom_write_byte(EEP_ADDR_CARD_NO_H, g_cardNo_h);
    if (B_CARD_NO_L & items)        eeprom_write_byte(EEP_ADDR_CARD_NO_L, g_cardNo_l);
    if (B_DISCUSS_STATE & items)    eeprom_write_byte(EEP_ADDR_DISCUSS_STATE, g_discuss_state);
    if (B_PASSWORD1 & items)        eeprom_write_byte(EEP_ADDR_PASSWORD1, g_password1);
    if (B_PASSWORD2 & items)        eeprom_write_byte(EEP_ADDR_PASSWORD2, g_password2);
    if (B_CANDIDATE & items)        eeprom_write_byte(EEP_ADDR_CANDIDATE, g_candidate);
    if (B_AVAILABLE & items)        eeprom_write_byte(EEP_ADDR_OPTIONAL, g_available);
    if (B_VALID_ON_FIRST & items)   eeprom_write_byte(EEP_ADDR_VALID_ON_FIRST, g_limit_one_action);
    if (B_CAMERA_NO_VICE & items)   eeprom_write_byte(EEP_ADDR_CAMERA_NO_VICE, g_cameraNo_vice);

    sei();
}

/*
 * 系统初始化总函数
 */
void init_devices(void) {
    cli();

    wdt_disable();
    //MCUCR = 0x00;
    //MCUCSR = 0x80;
    //GICR = 0x00;

    port_init();
    timer0_init();
    // timer1_init();

    // spi_init();
    // twi_init();

    usart_init();

    restore_status();

    lcd_init();

    peripheral_init();

    wdt_enable(WDTO_2S);

    sei();
}
