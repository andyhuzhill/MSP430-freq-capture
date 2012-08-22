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


/*
 *
 *
 *  *
 *
 * PIN1 --> GND
 * PIN2 --> VCC5V
 * PIN3 -->
 * PIN4 --> CS --> VCC
 * PIN5 --> SID --> P2.5
 * PIN6 --> CLK --> P2.4
 * PIN7 --> D0
 * PIN8 --> D1
 * PIN9 --> D2
 * PIN10 --> D3
 * PIN11 --> D4
 * PIN12 --> D5
 * PIN13 --> D6
 * PIN14 --> D7
 * PIN15 --> PSB  -->GND
 * PIN16 --> NC
 * PIN17 --> /RESET -->
 * PIN18 --> VOUT -->
 * PIN19 --> A -->  VCC5V
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
