#ifndef _CONST_H__
#define _CONST_H__

/*
 * ����
 */
#define MODEL_DISCUSS                       (0x00)        /* ������ */
#define MODEL_VOTE                          (0x01)        /* ����� */
#define MODEL_ALL_IN_ONE                    (0x02)        /* һ��� */

#define MODEL_SI_SUPPORT                    (0x10)        /* ֧��ͬ�� */
#define MODEL_SI_NONE                       (0x00)        /* ��ͬ�� */

/*
 * ǩ������
 */
#define SIGN_MODE_PRESS                     (1)           /* ����ǩ�� */
#define SIGN_MODE_ICC                       (2)           /* IC���Ժ�ǩ�� */
#define SIGN_MODE_ICC_BACK                  (3)           /* IC�����Ժ�ǩ�� */

/*
 * ģʽ����
 */
#define MODE_INIT                           (0)           /* �Լ� */
#define MODE_SIGN_KEY                       (1)           /* ����ǩ��*/
#define MODE_WRITE_CARD                     (2)           /* д�� */
#define MODE_SIGN_CARD1                     (3)           /* ��ǩ�� ��λ����*/
#define MODE_SIGN_CARD2                     (9)           /* ��ǩ�� ���ؿ���*/
#define MODE_VOTE                           (4)           /* ��� */
#define MODE_REMARK                         (5)           /* ���� */
#define MODE_CHG_ADDR                       (6)           /* �޸ĵ�ַ, ��λ */
#define MODE_CHG_ADDR_H                     (16)          /* �޸ĵ�ַ, ��λ */
#define MODE_DISCUSS                        (7)           /* ���� */
#define MODE_VOTE5                          (8)           /* 5ѡ��1 */

/*
 * eeprom address
 */
#define EEP_ADDR_MODEL                      ((uint8 *) 0x00)        /* ģʽ����: 0x01: ������, 0x02: �����, 0x03: һ��� */
#define EEP_ADDR_SI_MODEL                   ((uint8 *) 0x01)        /* ͬ��ģʽ: 0x00: ��֧��ͬ��, 0x10: ֧��ͬ�� */
#define EEP_ADDR_CONTRAST                   ((uint8 *) 0x02)        /* �Աȶ�: DEFAULT: 0x20 */
#define EEP_ADDR_ADDRESS_H                  ((uint8 *) 0x03)        /* ������ַ����λ */
#define EEP_ADDR_ADDRESS_L                  ((uint8 *) 0x04)        /* ������ַ����λ */
#define EEP_ADDR_MODE                       ((uint8 *) 0x05)        /* DEFAULT:0x01 */
#define EEP_ADDR_VOTE                       ((uint8 *) 0x06)        /* DEFAULT:0x00 */
#define EEP_ADDR_VOTE_MODE                  ((uint8 *) 0x07)        /* ��ͨ��� ��ͨѡ�� */
#define EEP_ADDR_VOTED                      ((uint8 *) 0x08)        /* �Ƿ��� */
#define EEP_ADDR_SIGN                       ((uint8 *) 0x09)        /* DEFAULT:0x00 */
#define EEP_ADDR_SIGN_MODE                  ((uint8 *) 0x0A)        /* ǩ����ʽ����ǩ����λIC��ǩ������ICǩ�� */
#define EEP_ADDR_REMARK                     ((uint8 *) 0x0B)        /* DEFAULT:0x00 */
#define EEP_ADDR_LOCK                       ((uint8 *) 0x0C)        /* DEFAULT:0x00 �Ƿ��������� */
#define EEP_ADDR_LOCK_SIGN                  ((uint8 *) 0x0D)        /* DEFAULT:1 */
#define EEP_ADDR_CAMERA_NO                  ((uint8 *) 0x0E)        /* ����ͷ��� */
#define EEP_ADDR_POSITION                   ((uint8 *) 0x0F)        /* Ԥ��λ */
#define EEP_ADDR_CARD_NO_H                  ((uint8 *) 0x10)        /* DEFAULT:0x07 */
#define EEP_ADDR_CARD_NO_L                  ((uint8 *) 0x11)        /* DEFAULT:0x07 */
#define EEP_ADDR_DISCUSS_STATE              ((uint8 *) 0x12)        /* ����״̬ */
#define EEP_ADDR_PASSWORD1                  ((uint8 *) 0x13)        /* ����1 */
#define EEP_ADDR_PASSWORD2                  ((uint8 *) 0x14)        /* ����2 */
#define EEP_ADDR_CANDIDATE                  ((uint8 *) 0x15)        /* ���� */
#define EEP_ADDR_OPTIONAL                   ((uint8 *) 0x16)        /* ��ѡ���� */
#define EEP_ADDR_VALID_ON_FIRST             ((uint8 *) 0x17)        /* �Ƿ��״ΰ�����Ч */
#define EEP_ADDR_CAMERA_NO_VICE             ((uint8 *) 0x18)        /* ����ϯ����ͷ��� */
//#define EEP_ADDRESS_UP                    0x00        // ���������
//#define EEP_ADDRL_CHG                     0x02        // �޸�Ŀ���ַ

#define B_MODEL                             (1L)
#define B_SI_MODEL                          (1L << 1)
#define B_CONTRAST                          (1L << 2)
#define B_ADDR_H                            (1L << 3)
#define B_ADDR_L                            (1L << 4)
#define B_MODE                              (1L << 5)
#define B_VOTE                              (1L << 6)
#define B_VOTE_MODE                         (1L << 7)
#define B_VOTED                             (1L << 8)
#define B_SIGN                              (1L << 9)
#define B_SIGN_MODE                         (1L << 10)
#define B_REMARK                            (1L << 11)
#define B_LOCK                              (1L << 12)
#define B_LOCK_SIGN                         (1L << 13)
#define B_CAMERA_NO                         (1L << 14)
#define B_POSITION                          (1L << 15)
#define B_CARD_NO_H                         (1L << 16)
#define B_CARD_NO_L                         (1L << 17)
#define B_DISCUSS_STATE                     (1L << 18)
#define B_PASSWORD1                         (1L << 19)
#define B_PASSWORD2                         (1L << 20)
#define B_CANDIDATE                         (1L << 21)
#define B_AVAILABLE                         (1L << 22)
#define B_VALID_ON_FIRST                    (1L << 23)
#define B_CAMERA_NO_VICE                    (1L << 24)

/*
 * ��������
 * BYTE0: SYNC
 * BYTE1: SYNC
 * BYTE2: ADDR HOST
 * BYTE3: ADDR LOW
 * BYTE4: CMD
 * BYTE5: data1
 * BYTE6: data2
 * BYTE7: data3
 * BYTE8: ADDR HIGH
 * BYTE9: CHECK SUM
 *
 * AA AA FB FC FE 00 00 00 00 YZ /��������
 * AA AA FB 00 01 00 00 00 00 YZ /���Լ�
 * AA AA FB FC FD 00 00 00 00 YZ /�ѻ�����
 * AA AA FB 00 0B 00 00 00 00 YZ /�ܿ�ʼ����
 *
 * AA AA FB 00 01 00 00 00 00 YZ /���Լ�
 * AA AA FB BH 01 00 00 00 WH YZ /�����Լ�
 * AA AA FB 00 31 00 00 00 00 YZ /������
 * AA AA FB BH 31 00 00 00 WH YZ /��������
 *
 * AA AA FB 00 01 00 00 00 00 YZ /���Լ�
 * AA AA FB 00 02 00 00 00 00 YZ /��ǩ��[����]
 * AA AA FB BH 02 00 01 00 WH YZ /����ǩ��[����]
 * AA AA FB BH 02 00 00 00 WH YZ /ǩ����ѯ[����]
 * AA AA FB 00 02 00 01 00 00 YZ /��ǩ������[����]
 *
 * AA AA FB 00 01 00 00 00 00 YZ /���Լ�
 * AA AA FB 00 03 M1 M2 00 00 YZ /��ǩ��[�Ժ�]
 * AA AA FB BH 33 M1 M2 00 WH YZ /����ǩ��[�Ժ�]
 * AA AA FB BH 04 00 00 00 WH YZ /����ǩ������[�Ժ�]
 * AA AA FB BH 03 00 00 00 WH YZ /ǩ����ѯ[�Ժ�]
 * AA AA FB 00 04 00 00 00 00 YZ /��ǩ������[�Ժ�]
 *
 * AA AA FB 00 01 00 00 00 00 YZ /���Լ�
 * AA AA FB 00 05 M1 M2 00 00 YZ /��ǩ��[���Ժ�]
 * AA AA FB BH 35 M1 M2 00 WH YZ /����ǩ��[���Ժ�]
 * AA AA FB BH 04 00 00 00 WH YZ /����ǩ������[���Ժ�]
 * AA AA FB BH 05 00 00 00 WH YZ /ǩ����ѯ[���Ժ�]
 * AA AA FB 00 04 00 00 00 00 YZ /��ǩ������[���Ժ�]
 *
 * AA AA FB 00 0B 00 00 00 00 YZ /�ܿ�ʼ����
 * AA AA FB BH 0B 00 00 00 WH YZ /����״̬��ѯ
 * AA AA FB BH 0D 00 00 00 WH YZ /������
 * AA AA FB BH 0C 00 00 00 WH YZ /�����ر�
 * AA AA FB 00 0B 00 01 00 00 YZ /���۽���
 *
 * AA AA FB 00 0C 00 00 00 00 YZ /��ϯ��Ϸ���
 * AA AA FB 01 0B 00 00 00 00 YZ /������ϯ��ѯ
 *
 * AA AA FB 00 0F 00 00 00 00 YZ /������
 * AA AA FB 00 10 01 00 00 00 YZ /�ܱ��[�״���Ч]
 * AA AA FB 00 10 00 00 00 00 YZ /�ܱ��[β����Ч]
 * AA AA FB 00 11 00 00 00 00 YZ /������
 * AA AA FB BH 10 00 00 00 WH YZ /�����ѯ
 * AA AA FB 00 10 00 01 00 00 YZ /�ܽ������
 *
 * AA AA FB 00 0F 00 00 00 00 YZ /������
 * AA AA FB 00 10 11 02 00 00 YZ /����ѡ[�״���Ч]
 * AA AA FB 00 10 10 02 00 00 YZ /����ѡ[β����Ч]
 * AA AA FB 00 11 00 00 00 00 YZ /������
 * AA AA FB BH 10 00 00 00 WH YZ /��ѡ��ѯ
 * AA AA FB 00 10 00 FF 00 00 YZ /�ܽ�����ѡ
 *
 * AA AA FB 00 0F 00 00 00 00 YZ /������
 * AA AA FB 00 12 01 00 00 00 YZ /������[�״���Ч]
 * AA AA FB 00 12 00 00 00 00 YZ /������[β����Ч]
 * AA AA FB 00 11 00 00 00 00 YZ /������
 * AA AA FB BH 12 00 00 00 WH YZ /�����ѯ
 * AA AA FB 00 12 00 01 00 00 YZ /�ܽ�������
 *
 * AA AA FB 00 0F 00 00 00 00 YZ /������
 * AA AA FB 00 13 05 01 00 00 YZ /��ѡ��
 * AA AA FB 00 11 00 00 00 00 YZ /������
 * AA AA FB BH 13 00 00 00 WH YZ /ѡ�ٲ�ѯ
 * AA AA FB 00 14 00 00 00 00 YZ /�ܽ���ѡ��
 *
 * AA AA FB BH 20 00 00 00 WH YZ /Ĭ�϶Աȶ�
 * AA AA FB BH 21 00 00 00 WH YZ /���ӶԱȶ�
 * AA AA FB BH 22 00 00 00 WH YZ /���ٶԱȶ�
 *
 * AA AA FB 00 15 00 BH 00 WH YZ /д��ַ[������]
 * AA AA FB 00 15 01 BH 00 WH YZ /д��ַ[�����]
 * AA AA FB 00 15 02 BH 00 WH YZ /д��ַ[һ���]
 * AA AA FB 00 15 10 BH 00 WH YZ /д��ַ[������ͬ��]
 * AA AA FB 00 15 11 BH 00 WH YZ /д��ַ[�����ͬ��]
 * AA AA FB 00 15 12 BH 00 WH YZ /д��ַ[һ���ͬ��]
 */

#define COM_INIT                            0x01        /* �Լ� */

#define COM_SEARCH                          0x31        /* ���� */
#define COM_ONE_SIGN                        0x33        /* ����IC��ǩ���Ժ� */
// FIXME 0x32
// FIXME 0x34
#define COM_ONE_SIGN_BACK                   0x35        /* ����IC��ǩ�����Ժ� */

#define COM_SIGN_KEY                        0x02        /* ����ǩ�� */
#define COM_SIGN_CARD                       0x03        /* CHA������ֱ�Ӻ˶Կ��ţ���λ���� */
#define COM_SIGN_END                        0x04        /* ����IC��ǩ�� */
#define COM_SIGN_CARD_BACK                  0x05        /* IC��ǩ�������������ؿ��� */
#define COM_DOWNLOAD_CAMERA                 0x0A        /* ��������ͷ��ź�Ԥ��λ */
#define COM_DOWNLOAD_CAMERA_VICE_CHAIRMAN   0x1A        /* ���ظ���ϯ����ͷ��ź�Ԥ��λ */
#define COM_DISCUSS_START                   0x0B        /* ��ʼ���� */
#define COM_DISCUSS_CLOSE                   0x0C        /* �رջ�Ͳ */
#define COM_DISCUSS_OPEN                    0x0D        /* �򿪻�Ͳ */
#define COM_DISCUSS_WAIT                    0x0E        /* ��˸ */
#define COM_DISCUSS_WAIT2                   0x2E        /* ��׼������˸ */
#define COM_CLS_SCREEN                      0x0F        /* �����Ļ */
#define COM_VOTE1                           0x10        /* ��һ��� */
#define COM_LOCK_KEY                        0x11        /* ���� */
#define COM_REMARK                          0x12        /* ���� */
#define COM_VOTE5                           0x13        /* 5ѡ1��� */
#define COM_VOTE5_END                       0x14        /* ����5ѡ1��� */
#define COM_CHG_ADDRESS                     0x15        /* �޸ĵ�ַ */
#define COM_CHG_ADDRESS_H                   0x16        /* �޸ĵ�ַ�ߵ�ַ */

#define COM_CONTRAST_DEFAULT                0x20        /* Ĭ�϶Աȶ� */
#define COM_CONTRAST_INC                    0x21        /* ���ӶԱȶ� */
#define COM_CONTRAST_DEC                    0x22        /* ���ٶԱȶ� */

#define COM_PASS                            0x2E        /* ��ϯ��׼���� */

#define COM_OFFLINE                         0xFD        /* �ѻ� */
#define COM_ONLINE                          0xFE        /* ���� */

#define COM_ANSWER                          0xFF        /* Ӧ�� */

/*
 * ��������
 */
#define DATA_SIGNED                         0x10        /* ��ǩ�� */
#define DATA_NOSIGNED                       0x11        /* δǩ�� */
// FIXME 0x12
// FIXME 0x13
#define DATA_APPLY_TALL                     0x32        /* ���뷢�� */
#define DATA_OPEN_TALL                      0x33        /* �򿪻�Ͳ */
#define DATA_CLOSE_TALL                     0x34        /* �رջ�Ͳ */
// FIXME 0x35
#define DATA_VOTE1_NOPRESS                  0x40        /* δ�� */
#define DATA_VOTE1_YES                      0x41        /* �޳� */
#define DATA_VOTE1_ABSTAIN                  0x42        /* ��Ȩ */
#define DATA_VOTE1_NO                       0x43        /* ���� */
#define DATA_REMARK_NOPRESS                 0x50        /* δ�� */
#define DATA_REMARK_NO1                     0x51        /* �ǳ����� */
#define DATA_REMARK_NO2                     0x52        /* ���� */
#define DATA_REMARK_NO3                     0x53        /* �������� */
#define DATA_REMARK_NO4                     0x54        /* ������ */
#define DATA_VOTE5_NOPRESS                  0x60        /* δ�� */
#define DATA_VOTE5_NO1                      0x61        /* 1 */
#define DATA_VOTE5_NO2                      0x62        /* 2 */
#define DATA_VOTE5_NO3                      0x63        /* 3 */
#define DATA_VOTE5_NO4                      0x64        /* 4 */
#define DATA_VOTE5_NO5                      0x65        /* 5 */

#define KEYCODE_KEY1                        0x02        // ������������
#define KEYCODE_KEY2                        0x04        // �޳ɣ�����
#define KEYCODE_KEY3                        0x10        // ���ԣ�������
#define KEYCODE_KEY4                        0x08        // ��Ȩ����Ȩ
#define KEYCODE_KEY5                        0x20        //    ��������
#define KEYCODE_KEY6                        0x40        // ������Ͳ
#define KEYCODE_KEY7                        0x80        // ���

#define CH_MIN                              0           /* ��Сͨ����� */
#define CH_MAX                              5           /* ���ͨ����� */

enum {
    VOTE_MODE_SINGLE,
    VOTE_MODE_MULTIPLE
};

enum {
    VOTE_NOT_PRESS,
    VOTE_APPROVE,
    VOTE_REJECT,
    VOTE_ABSTAIN
};

enum {
    VOTE5_NOT_PRESS,
    VOTE5_1,
    VOTE5_2,
    VOTE5_3,
    VOTE5_4,
    VOTE5_5
};

enum {
    REMARK_NOT_PRESS,
    REMARK_SATISFIED,
    REMARK_ADEQUATE,
    REMARK_DISAPPOINTED
};

enum {
    DISCUSS_STATE_CLOSE,
    DISCUSS_STATE_OPEN,
    DISCUSS_STATE_APPLY
};

typedef enum tag_Laser_mode {
    LASER_OFF,
    LASER_STATIC,
    LASER_BLINK,
    LASER_BLINK_SPEC_TIMES
} Laser_mode_t;

typedef enum tag_Audio_mode {
    AUDIO_OFF,
    AUDIO_ON
} Audio_mode_t;

#endif /* CONSTS_H_ */
