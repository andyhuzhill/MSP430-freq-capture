/*
 *    Filename: main.c
 *
 * Description:
 *     Version: 1.0
 *    Compiler: 
 *     Created: 2012-8-16 上午11:27:13
 *      Author: Andy Scout
 *      E-mail: andyhuzhill@gmail.com
 *    HomePage: andylinux.sinaapp.com
 *              www.andylinux.co.cc
 *   CopyRight: GPL v3
 *    Revision:
 *
 */

#include <msp430g2553.h>
#include "lcd12864.h"

typedef unsigned int uint;

uint Capture = 0;
uint CapCnt=0;
uint TA_OverflowCnt=0;
unsigned long Period=0;

void ConfigClocks(void)
{
	uint i;
	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;
	BCSCTL3 |= LFXT1S_0;                  //ACLK = LFXT1 = 32768Hz
	do {
		IFG1 &= ~OFIFG; 				  //清除振荡器失效标志
		for (i = 0xff;i>0;i--);
	} while ((IFG1 & OFIFG)!=0);			//如果振荡器失效标志存在

	BCSCTL2 |= SELM_0 + DIVM_0 + DIVS_0;  //MCLK =DCO SMCLK = DCO
}

void ConfigTimer(void)
{
	CCTL1 = CCIE + CM_3 + SCS + CAP;     //上升沿捕获、选择CCI1A (P1.2) 同步捕获
	TA0CTL = TASSEL_2 + MC_2 + TAIE + TACLR + ID_3;
	//基准频率8MHz 连续计数 八 分频、定时中断允许
	//	TACTL = TASSEL_1 + MC_2 + TAIE + TACLR + ID_0;
	//	//基准频率32768Hz 连续计数  无分频  定时中断允许
}

void ConfigADC(void)
{
	ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON + ADC10IE ;
	//转换时钟选择 ADC10ON 参考电压1.5V
	ADC10CTL1 |= INCH_4;
	ADC10AE0  |= BIT4;
}

void ConfigPort(void)
{
	P1DIR &= ~BIT2;
	P1SEL |= BIT2;     //捕获引脚 CCI1A P1.2

	P1DIR &= ~BIT4;
	P1SEL |= BIT4;     //ADC引脚 P1.4
}

char* ftoa(float f)  //浮点数转换为字符串
{
	static char str[8]={0};
	long iDat;

	iDat = (long)f;
	str[0]=iDat / 100000 + 0x30;
	str[1]=iDat / 10000 % 10 + 0x30;
	str[2]=iDat / 1000 % 10 + 0x30;
	str[3]=iDat / 100 % 10 + 0x30;
	str[4]=iDat /10 % 10 + 0x30;
	str[5]= '.';
	str[6]=iDat % 10 +0x30;
	str[7]= '\0';
	return str;
}

void
main(void)
{
	char *str;
	uint i,j,k;
	float t,freq;

	uint ADC_value[100];
	uint ADC_max[10];
	float volt,average;
	unsigned long temp;

	WDTCTL = WDTPW + WDTHOLD;
	ConfigClocks();
	ConfigPort();
	ConfigTimer();
	ConfigADC();

	i=j=k=0;

	LCD12864_init();
	LCD12864_clr();
	LCD12864_write_string(0,1,"    频  率  计");
	LCD12864_write_string(0,2,"频率:");
	LCD12864_write_string(0,3,"幅值:");
	while(1)
	{
		ADC10CTL0 |= ADC10SC + ENC;
		_BIS_SR(CPUOFF+GIE);

		if (Period != 0) {
			t = Period / 200.0;
			freq = 1000000.0 / t / 2;              //将周期转换为频率
			freq = freq / 1.01;
			str = ftoa(freq*10);
			LCD12864_write_string(3,2,str);
			LCD12864_write_data('H');
			LCD12864_write_data('z');
			Period = 0;
		}

		ADC_value[i++] = ADC10MEM;           //记录100次ADC转换值，求幅值
		if(i == 100){
			i = 0;
			ADC_max[k] = ADC_value[0];

			for(j = 0;j < 100;j ++){
				if(ADC_max[k] < ADC_value[j])
					ADC_max[k] = ADC_value[j];
			}								//找出100个值中的最大值

			k ++;
			if(k == 10){
				temp = 0;
				for(j = 0; j < 10 ;j ++)
					temp += ADC_max[j];
				average = (temp / 10);
				k = 0;
				volt =  average / 1023.0 * 1.5;
				str = ftoa(volt*10);
				LCD12864_write_string(4,3,str); // 计算十个最大值的平均值作为幅值，并显示
				LCD12864_write_data('V');
			}
		}
	}
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void
TimerA0_ISR(void)
{
	_DINT();
	switch (TAIV)
	{
	case 2:
		if ((CapCnt ==0)&&(CCTL1&CM0))  //当上升沿时 开始计时
			Capture = CCR1;
		CapCnt ++;
		if (CapCnt >= 200){
			if (TA_OverflowCnt > 0){
				Period = CCR1 + TA_OverflowCnt * 65536  - Capture ;  // 计算100个周期所用时间
			}else{
				Period = CCR1 - Capture ;
			}
			CapCnt = 0;
			Capture = 0;
			TA_OverflowCnt = 0;
		}
		TACCTL0 &= ~CCIFG;
		_BIC_SR_IRQ(CPUOFF);
		break;
	case 10:
		if (Capture != 0) {
			TA_OverflowCnt ++;
		}     //如果没有开始捕获，则不计时
		TACTL &= ~TAIFG;
		break;
	default:
		break;
	}
	_EINT();
}

//#pragma vector= TIMER1_A1_VECTOR
//__interrupt void
//TimerA1_ISR(void)
//{
//	ADC10CTL0 = ADC10SC | ENC;
//}

#pragma vector= ADC10_VECTOR
__interrupt
void Adc10_ISR(void)
{
	_BIC_SR_IRQ(CPUOFF);
}
