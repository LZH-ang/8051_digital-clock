#include <STC8.H>
#include "TM1637.h"

#define u8 unsigned char
#define u16 unsigned int

u8 num[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7f,0x6F};
u8 second=30,min=98;
u16 ms;

void Timer0Init(void)                //1∫¡√Î@11.0592MHz
{
	AUXR |= 0x80;
	TMOD &= 0xF0;
	TL0 = 0xCD;
	TH0 = 0xD4;
	ET0 = 1;
	EA = 1;
	TF0 = 0;
	TR0 = 1;
}

void main()
{
	P1M0 = 0xff;
	P1M1 = 0xff;
	Timer0Init();
	while(1)
	{
		display_4seg(num[min/10],num[min%10]|0x80,num[second/10],num[second%10]);
	}
}

void TM0_Isr() interrupt 1
{
	ms++;
	if(ms==1000)
	{
		ms=0;
		second++;
		if(second==60)
		{
			second=0;
			min++;
			if(min==100)
			{
				min=0;
			}
		}
	}
}