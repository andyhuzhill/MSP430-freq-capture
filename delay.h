/*
 *    Filename: delay.h
 *
 * Description:
 *     Version: 1.0
 *    Compiler: 
 *     Created: 2012-7-24 4:05:49
 *      Author: Andy Scout
 *      E-mail: andyhuzhill@gmail.com
 *    HomePage: andylinux.sinaapp.com
 *              www.andylinux.co.cc
 *   CopyRight: GPL v3
 *    Revision:
 *
 */

#ifndef DELAY_H_
#define DELAY_H_

#define CPU_F 8000000UL
#define delay_us(x) __delay_cycles(CPU_F*(double)x/1000000.0)
#define delay_ms(x) __delay_cycles(CPU_F*(double)x/1000.0)

#endif /* DELAY_H_ */
