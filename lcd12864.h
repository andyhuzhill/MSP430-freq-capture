/*
 *    Filename: LCD.h
 *
 * Description: 12864 LCD driver for msp430
 *     Version: 1.0
 *    Compiler: msp430-gcc
 *     Created: 2012-7-24 2:53:33
 *      Author: Andy Scout
 *      E-mail: andyhuzhill@gmail.com
 *    HomePage: andylinux.sinaapp.com
 *              www.andylinux.co.cc
 *   CopyRight: GPL v3
 *    Revision:
 *
 */

#ifndef LCD12864_H_
#define LCD12864_H_

#include <msp430.h>
#include <stdint.h>
#include "delay.h"

#if 0

/*
 * 4缂��锟介��ゆ�����凤拷杈炬�����烽��ゆ�LCD12864
 *
 * MSP430 濞�拷��CD 锟解��烽��ヤ������ * LCD 4濞达��烽��ゆ���拷�烽��ゆ�婵�拷�烽�锟�D7���锟介��ゆ���拷��0锟斤拷��濞�拷�烽��ゆ���拷U
 *
 * PIN1 --> GND
 * PIN2 --> VCC5V
 * PIN3 --> ���锟介�锟�> GND
 * PIN4 --> RS --> P1.0
 * PIN5 --> R/W --> P1.1
 * PIN6 --> EN --> P1.2
 * PIN7 --> D0 濞�拷�烽�锟�
 * * PIN8 --> D1 濞�拷�烽�锟�
 * * PIN9 --> D2 濞�拷�烽�锟�
 * * PIN10 --> D3 濞�拷�烽�锟�
 * * PIN11 --> D4 --> P2.0
 * PIN12 --> D5 --> P2.1
 * PIN13 --> D6 --> P2.2
 * PIN14 --> D7 --> P2.3
 * PIN15 --> PSB --> 濞�拷�烽�锟�
 * * PIN16 --> NC --> 濞�拷�烽�锟�
 * * PIN17 --> /RESET --> 濞�拷�烽�锟�
 * * PIN18 --> VOUT --> 濞�拷�烽�锟�
 * * PIN19 --> A -->  VCC5V
 * PIN30 --> K --> GND
 *
 */

#define LCD_EN_PORT P1OUT
#define LCD_EN_DDR P1DIR
#define LCD_RS_PORT P1OUT
#define LCD_RS_DDR P1DIR
#define LCD_RW_PORT P1OUT
#define LCD_RW_DDR P1DIR
#define LCD_DATA_PORT P2OUT
#define LCD_DATA_DDR P2DIR
#define LCD_EN BIT2
#define LCD_RS BIT0
#define LCD_RW BIT1
#define LCD_DATA BIT3|BIT2|BIT1|BIT0

#endif
/*
 * 濞�拷锟介��ゆ�锟斤拷�风��э拷����烽��ゆ�LCD12864
 *
 * MSP430 濞�拷��CD 锟解��烽��ヤ������ *
 *
 * PIN1 --> GND
 * PIN2 --> VCC5V
 * PIN3 -->
 * PIN4 --> CS --> P2.0
 * PIN5 --> SID --> P2.1
 * PIN6 --> CLK --> P2.2
 * PIN7 --> D0 濞�拷�烽�锟�
 * * PIN8 --> D1 濞�拷�烽�锟�
 * * PIN9 --> D2 濞�拷�烽�锟�
 * * PIN10 --> D3 濞�拷�烽�锟�
 * * PIN11 --> D4
 * PIN12 --> D5
 * PIN13 --> D6
 * PIN14 --> D7
 * PIN15 --> PSB  -->GND
 * PIN16 --> NC
 * PIN17 --> /RESET --> 濞�拷�烽�锟�
 * * PIN18 --> VOUT --> 濞�拷�烽�锟�
 * * PIN19 --> A -->  VCC5V
 * PIN30 --> K --> GND
 *
 *
 */
#define LCD_SID_PORT P2OUT
#define LCD_SID_DDR P2DIR
#define LCD_CLK_PORT P2OUT
#define LCD_CLK_DDR P2DIR


#define LCD_SID BIT5
#define LCD_CLK BIT4

void LCD12864_init(void);
void LCD12864_clr(void);

#if 0
void LCD12864_en_up(void);
void LCD12864_en_down(void);
#endif

void LCD12864_write_command(uint8_t cmd);
void LCD12864_write_data(uint8_t dat);
void LCD12864_write_string(uint8_t Xpos,uint8_t Ypos,const char *str);
void LCD12864_write_char(uint8_t Xpos,uint8_t Ypos, uint8_t chr);
void LCD12864_goToXY(uint8_t Xpos,uint8_t Ypos);

#endif /* LCD12864_H_ */
