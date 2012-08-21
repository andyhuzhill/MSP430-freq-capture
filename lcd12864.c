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
 *     LCD 初始化
 */
void LCD12864_init(void)
{
    delay_ms(5);
    //    LCD_CS_DDR |= LCD_CS;
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

#if 0

/*
 *
 * 娑叉�浣胯�涓��娌� *
 */

void LCD12864_en_up(void)
{
    LCD_EN_PORT &= ~LCD_EN;
    delay_us(10);
    LCD_EN_PORT |= LCD_EN;
}

/*
 *
 * 娑叉�浣胯�涓��娌� *
 */
void LCD12864_en_down(void)
{
    LCD_EN_PORT |= LCD_EN;
    delay_us(10);
    LCD_EN_PORT &= ~LCD_EN;
}
#endif



/*
 *
 *  ���浠ゅ��� *
 */

void LCD12864_write_command(uint8_t cmd)
{
#if 0
    delay_us(16);
    LCD_RS_PORT &= ~LCD_RS;  // RS=0
    LCD_RW_PORT &= ~LCD_RW;  // RW=0
    LCD12864_en_up();
    LCD_DATA_PORT &= 0xf0;   //娓�����
    LCD_DATA_PORT |= (cmd >> 4) & 0x0f;  //������

    delay_us(16);
    LCD12864_en_down();
    LCD12864_en_up();
    LCD_DATA_PORT &= 0xf0;    //娓�����
    LCD_DATA_PORT |= cmd & 0x0f; //������
    LCD12864_en_down();
#endif
    //    LCD_CS_PORT |= LCD_CS;
    LCD12864_write_byte(0xf8);
    LCD12864_write_byte(cmd & 0xf0);
    LCD12864_write_byte((cmd<<4)&0xf0);
    //    LCD_CS_PORT &= ~LCD_CS;
}

/*
 *
 * �������� *
 */

void LCD12864_write_data(uint8_t dat)
{
#if 0
    delay_us(16);
    LCD_RS_PORT |= LCD_RS;  // RS=1
    LCD_RW_PORT &= ~LCD_RW;
    LCD12864_en_up();       // E涓��娌�    LCD_DATA_PORT &= 0xf0;
    LCD_DATA_PORT |= (dat >> 4) & 0x0f;
    delay_us(16);
    LCD12864_en_down();
    LCD12864_en_up();
    LCD_DATA_PORT &= 0xf0;
    LCD_DATA_PORT |= dat & 0x0f;
    LCD12864_en_down();
#endif
    //    LCD_CS_PORT |= LCD_CS;
    LCD12864_write_byte(0xfa);
    LCD12864_write_byte(dat & 0xf0);
    LCD12864_write_byte((dat<<4)&0xf0);
    //    LCD_CS_PORT &= ~LCD_CS;
}

/*

 * �������� *
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
 *  在指定位置开始写一个字符串
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
 *  在指定位置写入一个字符
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
