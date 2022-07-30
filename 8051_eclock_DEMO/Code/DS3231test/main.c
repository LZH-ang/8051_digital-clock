#include <STC8.H>
#include "intrins.h"
#include "delay.h"
#include "3231.h"
#include "TM1637.h"

#define u8 unsigned char
#define u16 unsigned int

u8 num[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7f,0x6F};
u8 sec_dot=0,cp=0;
sbit led6 = P1^0;

void Timer0Init(void)		//5毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x00;		//设置定时初始值
	TH0 = 0x28;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EA = 1;
}

void main()
{
	P1M0 = 0x30;
	P1M1 = 0x30;
	P3M1 = 0x00;
	P3M0 = 0x00;
	Timer0Init();
	led6 = 1;
	while(cp<=20);cp = 0;//等待供电稳定
//	ModifyTime(DS3231_SECOND,00);_nop_();
//	ModifyTime(DS3231_MINUTE,14);_nop_();
//	ModifyTime(DS3231_HOUR,17);_nop_();
//	ModifyTime(DS3231_YEAR,22);_nop_();
//	ModifyTime(DS3231_MONTH,1);_nop_();
//	ModifyTime(DS3231_DAY,15);_nop_();
//	ModifyTime(DS3231_WEEK,7);_nop_();
	while(1)
	{
		if(cp ==60)
		{
			cp = 0;
			year = read_random(DS3231_YEAR);_nop_();
			mon = read_random(DS3231_MONTH);_nop_();
			day = read_random(DS3231_DAY);_nop_();
			hour = read_random(DS3231_HOUR);_nop_();
			min = read_random(DS3231_MINUTE);_nop_();
			sec = read_random(DS3231_SECOND);_nop_();
		}
		if(sec%2)sec_dot=0x80;else sec_dot=0;
	}
}

void TM0_Isr() interrupt 1
{
	
	cp++;
	display_4seg(num[hour/10],num[hour%10]|sec_dot,num[min/10],num[min%10]);
//	display_4seg(0xff,0xff,0xff,0xff);
}