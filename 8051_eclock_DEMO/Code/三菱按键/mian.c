#include <STC8.H>
#include <intrins.h>
#include "TM1637.h"

#define u8 unsigned char
#define u16 unsigned int

u8 data num[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7f,0x6F};

u8 TM0_cp = 0;
sbit k1 = P3^3;
sbit k2 = P3^2;
u8 key_data = 0;
u8 bdata kv = 0x0f;

sbit kv1 = kv^0;
sbit kv2 = kv^1;
sbit kv3 = kv^2;
sbit kv4 = kv^3;

void key_Bitread()
{
		if(k1&&k2)
		{
				kv1=1;
				kv2=1;
				k1=0;
				_nop_();_nop_();//_nop_();_nop_();
				kv3=k2;
				k1=1;
			
				k2=0;
				_nop_();_nop_();//_nop_();_nop_();
				kv4=k1;
				k2=1;
		}
		else
		{
				kv3=1;
				kv4=1;
				kv1=k1;
				kv2=k2;
		}
}
void Key_scan()
{  
		static bit flag=1;
		static u8 count=0;
		key_Bitread();
		if(kv!=15&&flag)
		{
				count++;
				if(count>10)
				{
						count=0;
						switch(kv)
						{
								//0011 0111 1011 1100 1101 1110
								case 0x0e:key_data=1;break;
								case 0x0d:key_data=2;break;
								case 0x0c:key_data=3;break;
								
								case 0x0b:key_data=4;break;
								case 0x07:key_data=5;break;
								case 0x03:key_data=6;break;
						}
						flag=0;
				}
		}
		if(kv==15)//没有按键按下
		{
				count=0;
				flag=1;
				key_data = 9;
		}	
		
}

void Timer0Init(void)		//12T 1毫秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式	//1T AUXR |= 0x80;
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x66;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	ET0 = 1;
	EA = 1;
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void main()
{
	
	//nmd IO复位高阻态
	P1M0 = 0xff;//开漏
	P1M1 = 0xff;
	P3M0 = 0x00;//准双向
	P3M1 = 0x00;
	Timer0Init();
	while(1)
	{
		if(TM0_cp == 10)
		{			
			display_1seg(0x40,0,7);
			display_1seg(0x40,1,7);
			display_1seg(0x40,2,7);
			display_1seg(num[key_data],3,7);
			TM0_cp = 0;
		}
	}
}

void TM0_Isr() interrupt 1
{
	Key_scan(); 
	TM0_cp++;
}


