#ifndef _CONST_H__
#define _CONST_H__

/*
 * 机型
 */
#define MODEL_DISCUSS                       (0x00)        /* 单讨论 */
#define MODEL_VOTE                          (0x01)        /* 单表决 */
#define MODEL_ALL_IN_ONE                    (0x02)        /* 一体机 */

#define MODEL_SI_SUPPORT                    (0x10)        /* 支持同传 */
#define MODEL_SI_NONE                       (0x00)        /* 无同传 */

/*
 * 签到类型
 */
#define SIGN_MODE_PRESS                     (1)           /* 按键签到 */
#define SIGN_MODE_ICC                       (2)           /* IC卡对号签到 */
#define SIGN_MODE_ICC_BACK                  (3)           /* IC卡不对号签到 */

/*
 * 模式类型
 */
#define MODE_INIT                           (0)           /* 自检 */
#define MODE_SIGN_KEY                       (1)           /* 按键签到*/
#define MODE_WRITE_CARD                     (2)           /* 写卡 */
#define MODE_SIGN_CARD1                     (3)           /* 卡签到 定位就座*/
#define MODE_SIGN_CARD2                     (9)           /* 卡签到 返回卡号*/
#define MODE_VOTE                           (4)           /* 表决 */
#define MODE_REMARK                         (5)           /* 评议 */
#define MODE_CHG_ADDR                       (6)           /* 修改地址, 低位 */
#define MODE_CHG_ADDR_H                     (16)          /* 修改地址, 高位 */
#define MODE_DISCUSS                        (7)           /* 讨论 */
#define MODE_VOTE5                          (8)           /* 5选举1 */

/*
 * eeprom address
 */
#define EEP_ADDR_MODEL                      ((uint8 *) 0x00)        /* 模式变量: 0x01: 单讨论, 0x02: 单表决, 0x03: 一体机 */
#define EEP_ADDR_SI_MODEL                   ((uint8 *) 0x01)        /* 同传模式: 0x00: 不支持同传, 0x10: 支持同传 */
#define EEP_ADDR_CONTRAST                   ((uint8 *) 0x02)        /* 对比度: DEFAULT: 0x20 */
#define EEP_ADDR_ADDRESS_H                  ((uint8 *) 0x03)        /* 本机地址，高位 */
#define EEP_ADDR_ADDRESS_L                  ((uint8 *) 0x04)        /* 本机地址，低位 */
#define EEP_ADDR_MODE                       ((uint8 *) 0x05)        /* DEFAULT:0x01 */
#define EEP_ADDR_VOTE                       ((uint8 *) 0x06)        /* DEFAULT:0x00 */
#define EEP_ADDR_VOTE_MODE                  ((uint8 *) 0x07)        /* 普通表决 普通选举 */
#define EEP_ADDR_VOTED                      ((uint8 *) 0x08)        /* 是否表决 */
#define EEP_ADDR_SIGN                       ((uint8 *) 0x09)        /* DEFAULT:0x00 */
#define EEP_ADDR_SIGN_MODE                  ((uint8 *) 0x0A)        /* 签到方式按键签到定位IC卡签到随意IC签到 */
#define EEP_ADDR_REMARK                     ((uint8 *) 0x0B)        /* DEFAULT:0x00 */
#define EEP_ADDR_LOCK                       ((uint8 *) 0x0C)        /* DEFAULT:0x00 是否锁定按键 */
#define EEP_ADDR_LOCK_SIGN                  ((uint8 *) 0x0D)        /* DEFAULT:1 */
#define EEP_ADDR_CAMERA_NO                  ((uint8 *) 0x0E)        /* 摄像头编号 */
#define EEP_ADDR_POSITION                   ((uint8 *) 0x0F)        /* 预置位 */
#define EEP_ADDR_CARD_NO_H                  ((uint8 *) 0x10)        /* DEFAULT:0x07 */
#define EEP_ADDR_CARD_NO_L                  ((uint8 *) 0x11)        /* DEFAULT:0x07 */
#define EEP_ADDR_DISCUSS_STATE              ((uint8 *) 0x12)        /* 讨论状态 */
#define EEP_ADDR_PASSWORD1                  ((uint8 *) 0x13)        /* 密码1 */
#define EEP_ADDR_PASSWORD2                  ((uint8 *) 0x14)        /* 密码2 */
#define EEP_ADDR_CANDIDATE                  ((uint8 *) 0x15)        /* 人数 */
#define EEP_ADDR_OPTIONAL                   ((uint8 *) 0x16)        /* 可选人数 */
#define EEP_ADDR_VALID_ON_FIRST             ((uint8 *) 0x17)        /* 是否首次按键有效 */
#define EEP_ADDR_CAMERA_NO_VICE             ((uint8 *) 0x18)        /* 副主席摄像头编号 */
//#define EEP_ADDRESS_UP                    0x00        // 表决器类型
//#define EEP_ADDRL_CHG                     0x02        // 修改目标地址

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
 * 命令类型
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
 * AA AA FB FC FE 00 00 00 00 YZ /联机运行
 * AA AA FB 00 01 00 00 00 00 YZ /总自检
 * AA AA FB FC FD 00 00 00 00 YZ /脱机运行
 * AA AA FB 00 0B 00 00 00 00 YZ /总开始讨论
 *
 * AA AA FB 00 01 00 00 00 00 YZ /总自检
 * AA AA FB BH 01 00 00 00 WH YZ /单机自检
 * AA AA FB 00 31 00 00 00 00 YZ /总搜索
 * AA AA FB BH 31 00 00 00 WH YZ /单机搜索
 *
 * AA AA FB 00 01 00 00 00 00 YZ /总自检
 * AA AA FB 00 02 00 00 00 00 YZ /总签到[按键]
 * AA AA FB BH 02 00 01 00 WH YZ /单机签到[按键]
 * AA AA FB BH 02 00 00 00 WH YZ /签到查询[按键]
 * AA AA FB 00 02 00 01 00 00 YZ /总签到结束[按键]
 *
 * AA AA FB 00 01 00 00 00 00 YZ /总自检
 * AA AA FB 00 03 M1 M2 00 00 YZ /总签到[对号]
 * AA AA FB BH 33 M1 M2 00 WH YZ /单机签到[对号]
 * AA AA FB BH 04 00 00 00 WH YZ /单机签到结束[对号]
 * AA AA FB BH 03 00 00 00 WH YZ /签到查询[对号]
 * AA AA FB 00 04 00 00 00 00 YZ /总签到结束[对号]
 *
 * AA AA FB 00 01 00 00 00 00 YZ /总自检
 * AA AA FB 00 05 M1 M2 00 00 YZ /总签到[不对号]
 * AA AA FB BH 35 M1 M2 00 WH YZ /单机签到[不对号]
 * AA AA FB BH 04 00 00 00 WH YZ /单机签到结束[不对号]
 * AA AA FB BH 05 00 00 00 WH YZ /签到查询[不对号]
 * AA AA FB 00 04 00 00 00 00 YZ /总签到结束[不对号]
 *
 * AA AA FB 00 0B 00 00 00 00 YZ /总开始讨论
 * AA AA FB BH 0B 00 00 00 WH YZ /讨论状态查询
 * AA AA FB BH 0D 00 00 00 WH YZ /单机打开
 * AA AA FB BH 0C 00 00 00 WH YZ /单机关闭
 * AA AA FB 00 0B 00 01 00 00 YZ /讨论结束
 *
 * AA AA FB 00 0C 00 00 00 00 YZ /主席打断发送
 * AA AA FB 01 0B 00 00 00 00 YZ /电脑主席查询
 *
 * AA AA FB 00 0F 00 00 00 00 YZ /总清屏
 * AA AA FB 00 10 01 00 00 00 YZ /总表决[首次有效]
 * AA AA FB 00 10 00 00 00 00 YZ /总表决[尾次有效]
 * AA AA FB 00 11 00 00 00 00 YZ /总锁定
 * AA AA FB BH 10 00 00 00 WH YZ /表决查询
 * AA AA FB 00 10 00 01 00 00 YZ /总结束表决
 *
 * AA AA FB 00 0F 00 00 00 00 YZ /总清屏
 * AA AA FB 00 10 11 02 00 00 YZ /总普选[首次有效]
 * AA AA FB 00 10 10 02 00 00 YZ /总普选[尾次有效]
 * AA AA FB 00 11 00 00 00 00 YZ /总锁定
 * AA AA FB BH 10 00 00 00 WH YZ /普选查询
 * AA AA FB 00 10 00 FF 00 00 YZ /总结束普选
 *
 * AA AA FB 00 0F 00 00 00 00 YZ /总清屏
 * AA AA FB 00 12 01 00 00 00 YZ /总评议[首次有效]
 * AA AA FB 00 12 00 00 00 00 YZ /总评议[尾次有效]
 * AA AA FB 00 11 00 00 00 00 YZ /总锁定
 * AA AA FB BH 12 00 00 00 WH YZ /评议查询
 * AA AA FB 00 12 00 01 00 00 YZ /总结束评议
 *
 * AA AA FB 00 0F 00 00 00 00 YZ /总清屏
 * AA AA FB 00 13 05 01 00 00 YZ /总选举
 * AA AA FB 00 11 00 00 00 00 YZ /总锁定
 * AA AA FB BH 13 00 00 00 WH YZ /选举查询
 * AA AA FB 00 14 00 00 00 00 YZ /总结束选举
 *
 * AA AA FB BH 20 00 00 00 WH YZ /默认对比度
 * AA AA FB BH 21 00 00 00 WH YZ /增加对比度
 * AA AA FB BH 22 00 00 00 WH YZ /减少对比度
 *
 * AA AA FB 00 15 00 BH 00 WH YZ /写地址[单讨论]
 * AA AA FB 00 15 01 BH 00 WH YZ /写地址[单表决]
 * AA AA FB 00 15 02 BH 00 WH YZ /写地址[一体机]
 * AA AA FB 00 15 10 BH 00 WH YZ /写地址[单讨论同传]
 * AA AA FB 00 15 11 BH 00 WH YZ /写地址[单表决同传]
 * AA AA FB 00 15 12 BH 00 WH YZ /写地址[一体机同传]
 */

#define COM_INIT                            0x01        /* 自检 */

#define COM_SEARCH                          0x31        /* 搜索 */
#define COM_ONE_SIGN                        0x33        /* 单机IC卡签到对号 */
// FIXME 0x32
// FIXME 0x34
#define COM_ONE_SIGN_BACK                   0x35        /* 单机IC卡签到不对号 */

#define COM_SIGN_KEY                        0x02        /* 按键签到 */
#define COM_SIGN_CARD                       0x03        /* CHA卡本机直接核对卡号，定位就座 */
#define COM_SIGN_END                        0x04        /* 结束IC卡签到 */
#define COM_SIGN_CARD_BACK                  0x05        /* IC卡签到，报到，返回卡号 */
#define COM_DOWNLOAD_CAMERA                 0x0A        /* 下载摄像头编号和预置位 */
#define COM_DOWNLOAD_CAMERA_VICE_CHAIRMAN   0x1A        /* 下载副主席摄像头编号和预置位 */
#define COM_DISCUSS_START                   0x0B        /* 开始讨论 */
#define COM_DISCUSS_CLOSE                   0x0C        /* 关闭话筒 */
#define COM_DISCUSS_OPEN                    0x0D        /* 打开话筒 */
#define COM_DISCUSS_WAIT                    0x0E        /* 闪烁 */
#define COM_DISCUSS_WAIT2                   0x2E        /* 批准发言闪烁 */
#define COM_CLS_SCREEN                      0x0F        /* 清除屏幕 */
#define COM_VOTE1                           0x10        /* 单一表决 */
#define COM_LOCK_KEY                        0x11        /* 锁定 */
#define COM_REMARK                          0x12        /* 评议 */
#define COM_VOTE5                           0x13        /* 5选1表决 */
#define COM_VOTE5_END                       0x14        /* 结束5选1表决 */
#define COM_CHG_ADDRESS                     0x15        /* 修改地址 */
#define COM_CHG_ADDRESS_H                   0x16        /* 修改地址高地址 */

#define COM_CONTRAST_DEFAULT                0x20        /* 默认对比度 */
#define COM_CONTRAST_INC                    0x21        /* 增加对比度 */
#define COM_CONTRAST_DEC                    0x22        /* 减少对比度 */

#define COM_PASS                            0x2E        /* 主席批准功能 */

#define COM_OFFLINE                         0xFD        /* 脱机 */
#define COM_ONLINE                          0xFE        /* 联机 */

#define COM_ANSWER                          0xFF        /* 应答 */

/*
 * 数据类型
 */
#define DATA_SIGNED                         0x10        /* 已签到 */
#define DATA_NOSIGNED                       0x11        /* 未签到 */
// FIXME 0x12
// FIXME 0x13
#define DATA_APPLY_TALL                     0x32        /* 申请发言 */
#define DATA_OPEN_TALL                      0x33        /* 打开话筒 */
#define DATA_CLOSE_TALL                     0x34        /* 关闭话筒 */
// FIXME 0x35
#define DATA_VOTE1_NOPRESS                  0x40        /* 未按 */
#define DATA_VOTE1_YES                      0x41        /* 赞成 */
#define DATA_VOTE1_ABSTAIN                  0x42        /* 弃权 */
#define DATA_VOTE1_NO                       0x43        /* 反对 */
#define DATA_REMARK_NOPRESS                 0x50        /* 未按 */
#define DATA_REMARK_NO1                     0x51        /* 非常满意 */
#define DATA_REMARK_NO2                     0x52        /* 满意 */
#define DATA_REMARK_NO3                     0x53        /* 基本满意 */
#define DATA_REMARK_NO4                     0x54        /* 不满意 */
#define DATA_VOTE5_NOPRESS                  0x60        /* 未按 */
#define DATA_VOTE5_NO1                      0x61        /* 1 */
#define DATA_VOTE5_NO2                      0x62        /* 2 */
#define DATA_VOTE5_NO3                      0x63        /* 3 */
#define DATA_VOTE5_NO4                      0x64        /* 4 */
#define DATA_VOTE5_NO5                      0x65        /* 5 */

#define KEYCODE_KEY1                        0x02        // 报道，减分数
#define KEYCODE_KEY2                        0x04        // 赞成，满意
#define KEYCODE_KEY3                        0x10        // 反对，不满意
#define KEYCODE_KEY4                        0x08        // 弃权，弃权
#define KEYCODE_KEY5                        0x20        //    ，增分数
#define KEYCODE_KEY6                        0x40        // 开启话筒
#define KEYCODE_KEY7                        0x80        // 打断

#define CH_MIN                              0           /* 最小通道编号 */
#define CH_MAX                              5           /* 最大通道编号 */

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
