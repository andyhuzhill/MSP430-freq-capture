/*
 *    Filename: lcd12864.c
 *
 * Description:
 *     Version: 1.0
 *    Compiler: msp430-gcc
 *     Created: 2012-7-24 1:12:21
 *      Author: Andy Scout
 *      E-mail: andyhuzhill@gmail.com
 *    HomePage: andylinux.sinaapp.com
 *              www.andylinux.co.cc
 *   CopyRight: GPL v3
 *    Revision:
 *
 */

#include "lcd12864.h"

void LCD12864_write_byte(uint8_t byte)
{
    uint8_t nCount;
    for (nCount = 0; nCount < 8; ++nCount)
    {
        LCD_CLK_PORT &= ~LCD_CLK;
        if (byte & 0x80)
        {
            LCD_SID_PORT |= LCD_SID;
        }
        else
        {
            LCD_SID_PORT &= ~LCD_SID;
        }
        byte = byte << 1;
        LCD_CLK_PORT |= LCD_CLK;
        delay_us(50);
        LCD_CLK_PORT &= ~LCD_CLK;
        delay_us(50);
    }
}


/*
 *
 *     初始化ＬＣＤ
 *
 */
void LCD12864_init(void)
{
    delay_ms(5);
    LCD_SID_DDR |= LCD_SID;
    LCD_CLK_DDR |= LCD_CLK;

    delay_ms(5);
    LCD12864_write_command(0x30);
    delay_ms(5);
    LCD12864_write_command(0x28);
    delay_ms(30);
    LCD12864_write_command(0x01);
    LCD12864_write_command(0x0c);
    LCD12864_write_command(0x06);
    delay_ms(5);
}


/*
 *
 * 　　　　写指令
 *
 */

void LCD12864_write_command(uint8_t cmd)
{
    LCD12864_write_byte(0xf8);
    LCD12864_write_byte(cmd & 0xf0);
    LCD12864_write_byte((cmd<<4)&0xf0);
}

/*
 *
 * 　　写数据
 *
 */

void LCD12864_write_data(uint8_t dat)
{
    LCD12864_write_byte(0xfa);
    LCD12864_write_byte(dat & 0xf0);
    LCD12864_write_byte((dat<<4)&0xf0);
}

/*
 *
 *  光标移至指定位置
 *
 */

void LCD12864_goToXY(uint8_t Xpos, uint8_t Ypos)
{
    uint8_t address;
    switch(Ypos)
    {
        case 1:
            address = 0x80 | Xpos;
            break;
        case 2:
            address = 0x90 | Xpos;
            break;
        case 3:
            address = ((0x80|Xpos)+8);
            break;
        case 4:
            address = ((0x90|Xpos)+8);
            break;
        default:
            address = 0x80;
            break;
    }
    LCD12864_write_command(address);
}

/*
 *
 *	写入一个字符串
 *
 */

void LCD12864_write_string(uint8_t Xpos, uint8_t Ypos,const char *str)
{
    LCD12864_goToXY(Xpos, Ypos);
    while(*str)
    {
        LCD12864_write_data(*str++);
    }
}

/*
 *
 *  写入一个字符
 *
 */

void LCD12864_write_char(uint8_t Xpos, uint8_t Ypos, uint8_t dat)
{
    LCD12864_goToXY(Xpos, Ypos);
    LCD12864_write_data(dat);
}

/*
 *
 * LCD 清屏
 *
 */

void LCD12864_clr(void)
{
    LCD12864_write_command(0x30);
    LCD12864_write_command(0x01);
}
