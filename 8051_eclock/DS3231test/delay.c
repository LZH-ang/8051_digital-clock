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
