#include <STC8.H>
#include "TM1637.h"


u8 num[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7f,0x6F};
u8 second=30;
u16 ms;
bit dot=0;

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
		if(dot)
		{
			display_1seg(num[second/10]|0x80,1,2);
		  display_1seg(num[second%10]|0x80,2,2);
		}
		else 
		{
			display_1seg(num[second/10],1,2);
		  display_1seg(num[second%10],2,2);
		}	
	}
}

void TM0_Isr() interrupt 1
{
	ms++;
	if(ms == 500)dot = ~dot;
	if(ms==1000)
	{
		dot = ~dot;
		ms=0;
		second++;
		if(second==60)
		{
			second=0;
		}
	}
}