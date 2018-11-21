#include "config.h"

void delay_us(uint8 i) {
    while (i--) NOP();
}

void delay_ms(uint8 i) {
    uint8 j, k;
    while(i--) {
        for(k=0;k<4;k++) {
            for(j=250;j!=0;j--)
                NOP();
        }
    }
}

static inline void clock() {
    ICC_SCLK = 1;
    delay_us(5);
    ICC_SCLK = 0;
    delay_us(5);
}

uint8 read_byte() {
    set_io_input();

    uint8 i, byte = 0;

    ICC_SCLK = 0;

    for (i = 0; i < 8; i++) {
        byte = byte >> 1;

        ICC_SCLK = 1;
        delay_us(5);

        if (io_port_is_set()) {
           byte |= 0x80;
        }

        ICC_SCLK = 0;
        delay_us(5);
    }

    return byte;
}

void write_byte(uint8 byte) {
    set_io_output();

    uint8 i;

    for (i = 0; i < 8; i++) {
        ICC_SCLK = 0;

        ICC_IO = 0x01 & (byte >> i);
        clock();
    }
}

void start_comm() {
    set_io_output();

    ICC_SCLK = 0;
    ICC_IO = 0;
    delay_us(2);
    ICC_SCLK = 1;
    ICC_IO = 1;
    delay_us(2);
    ICC_SCLK = 0;
    ICC_IO = 0;
}

void stop_comm() {
    set_io_output();

    ICC_SCLK = 0;
    ICC_IO = 0;
    delay_us(5);
    ICC_SCLK = 1;
    ICC_IO = 0;
    delay_us(2);
    ICC_IO = 1;
    delay_us(2);
    ICC_IO = 0;
}

void send_comm(uint8 cmd, uint8 addr, uint8 data) {
    start_comm();
    write_byte(cmd);
    write_byte(addr);
    write_byte(data);
    stop_comm();
}

void BreakOperate() {
    set_io_output();

    ICC_SCLK = 0;
    ICC_RST = 0;
    ICC_IO = 0;

    delay_us(2);

    ICC_RST = 1;
    ICC_IO = 1;

    delay_us(2);

    ICC_RST = 0;

    delay_us(2);
}

void ResetCard(void) {
    set_io_output();

    ICC_RST = 0;
    ICC_SCLK = 0;
    ICC_IO = 1;
    delay_us(5);
    ICC_RST = 1;
    delay_us(5);

    clock();

    ICC_RST = 0;

    delay_us(10);

    // �ն� 32Bit (4Byte)
    read_byte();
    read_byte();
    read_byte();
    read_byte();
}

void ReadMode(uint8 *pt, uint8 count) {
    set_io_input();

    ICC_SCLK = 0;
    delay_us(5);

    do
    {
        *(pt++) = read_byte();
        //pt ++;
    } while (--count);
}

void ProcessMode(void) {
    set_io_output();

    uint8 i;

    ICC_SCLK = 0;
    delay_us(5);

    ICC_IO = 0;
    delay_us(5);

    for (i = 255; i > 0; i--) {
        ICC_SCLK = 1;
        delay_us(2);
        ICC_SCLK = 0;
        delay_us(2);
    }

    ICC_IO = 1;
    delay_us(2);
}

void ReadMainMem(uint8 addr, uint8 *pt, uint8 count) {
    ResetCard();
    send_comm(ICC_CMD_RMM, addr, 0xFF);
    ReadMode(pt, count);
    BreakOperate();
}

void WriteMainMem(uint8 addr, uint8 pt) {
    ResetCard();
    send_comm(ICC_CMD_RMM, addr, pt);
    ProcessMode();
    BreakOperate();
}

void ReadProtectMem(uint8 *pt) {
    ResetCard();
    send_comm(ICC_CMD_RPM, 0xFF, 0xFF);
    ReadMode(pt, 4);
    BreakOperate();
}

void ProtectByte(uint8 addr, uint8 *pt) {
    ResetCard();
    send_comm(ICC_CMD_WPM, addr, *pt);
    ProcessMode();
    BreakOperate();
}

uint8 Verify(uint8 *pt) {
     uint8 temp[4];                                 //�ݴ�4�ֽڵı���������
     uint8 i = 0;

     send_comm(ICC_CMD_RSM, 0xFF, 0xFF);            //������洢����������,��2,3�������ڴ������б�����

     ReadMode(temp, 4);                             //����

    if ((temp[0] & 0x07) != 0) {                    //��һ�ֽ��Ǵ��������,������������Ϊ0,ֱ���˳�
        if ((temp[0] & 0x07) == 0x07) {
            i = 0x06;
        } else if ((temp[0] & 0x07) == 0x06) {
            i = 0x04;
        } else if ((temp[0] & 0x07) == 0x04) {
            i = 0x00;
        }               //������һλΪ1�ĸ�Ϊ0

        send_comm(ICC_CMD_WSM, 0, i);               //�޸Ĵ��������

        ProcessMode();                              //����

        for (i = 1; i < 4; i++, pt++) {             //У��3�ֽڵ�����
            send_comm(ICC_CMD_VER, i, *pt);         //����У������,
            ProcessMode();                          //����
        }

        send_comm(ICC_CMD_WSM, 0, 0xff);            //�����������ָ����������
        ProcessMode();                              //����
        send_comm(ICC_CMD_RSM, 0xff, 0xff);         //������洢����������,��2,3�������ڴ������б�����

        ReadMode(temp, 4);                          //�����������������
        if ((temp[0] & 0x07) == 0x07)               //���û�б��ɹ�����,����У��ʧ��
            return 1;
    }

    return 0;
}
