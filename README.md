讨论单元机源码
===========================================================

## 硬件配置 ##

MCU : Atmega32L  
LCD : ST7567 serial, 96*64  

## 开发环境 ##

Eclipse Version: Kepler Release For C/C++ Development  
Build id: 20130614-0229  
With: AVR Eclipse Plugin 2.4  

## 编译器 ##

avr-gcc (GCC) 4.5.3

## 编译开关 ##
|--------------------------|---------------------------------------------------------------|
| #define LANG_SET 0       | 语言选项，详见注释                                            |
| #define CHAIRMAN_VERSION | 主席/代表编译开关。打开此行后，为主席单元；注释此行为代表单元 |
| #define WITH_SMART_CARD  | 是否支持智能卡                                                |

## 源码说明 ##

|---------------------|--------------------------------------------------------|
| board_func.h        | 芯片相关功能封装及外设功能接口                         |
| build_config.h      | 编译开关选项，可选择语言(英，简)，调试开关             |
| strings.h           | 字符串资源，若添加其它语言版本，实现对应语言字符串即可 |
| config.h            | 配置文件，引用的头文件集合，及基本设置                 |
| const.h             | 常量                                                   |
| font_library.h      | 字库                                                   |
| icc_card.h          | 智能卡相关接口                                         |
| lcd_st7565_driver.h | lcd相关接口，协议与st7567兼容                          |
| utils.h             | 工具及调试功能                                         |
