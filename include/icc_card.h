#ifndef _ICC_FUNC_H__
#define _ICC_FUNC_H__

#define CARD_INSERTED()     (0 == (PINA & 0x01))

#define PORT_IO             (4)
#define PORT_PWR            (5)
#define PORT_RES            (6)
#define PORT_CLK            (7)

#define ICC_IO              PB(4)
#define ICC_PWR             PB(5)
#define ICC_RST             PB(6)
#define ICC_SCLK            PB(7)

#define ICC_CMD_RMM         0x30       // 读主存命令字
#define ICC_CMD_WMM         0x38       // 写主存命令字
#define ICC_CMD_RSM         0x31       // 读密码存储区
#define ICC_CMD_WSM         0x39       // 写密码存储区
#define ICC_CMD_RPM         0x34       // 读保护存储区
#define ICC_CMD_WPM         0x3C       // 写保护存储区
#define ICC_CMD_VER         0x33       // 校验密码

#define io_port_is_set() bit_is_set(PORTB, PORT_IO)

static inline void set_io_input() {
    DDRB &= ~(1 << PORT_IO);
}

static inline void set_io_output() {
    DDRB |= (1 << PORT_IO);
}

extern void ReadMainMem(uint8 addr, uint8 *pData, uint8 count);
extern void WriteMainMem(uint8 addr, uint8 data);

extern void ReadProtectMem(uint8 *pData);
extern void ProtectByte(uint8 addr, uint8 *pData);

extern void ResetCard();
extern void BreakOperate();

extern void ReadMode(uint8 *pData, uint8 count);
extern void ProcessMode();

extern uint8 Verify(uint8 *pData);

#endif /* ICC_FUNC_H_ */
