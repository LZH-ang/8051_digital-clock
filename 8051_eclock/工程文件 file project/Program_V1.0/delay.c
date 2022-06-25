#include "delay.h"
#include "intrins.h"

void Delay2us()                //@11.0592MHz
{
	unsigned char i;
	_nop_();
	i = 5;
	while (--i);
}
void Delay3us()                //@11.0592MHz
{
	unsigned char i;
	i = 9;
	while (--i);
}
void Delay5us()                //@11.0592MHz
{
	unsigned char i;
	_nop_();
	i = 16;
	while (--i);
	}
void Delay20us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 52;
	while (--i);
}
void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}
void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}



