#include <STC8.H>
//#include "intrins.h"
#define u8 unsigned char 
#define u16 unsigned int 	
#define PWMA_Period 60000
#define PWMA_CCER1  (*(unsigned char volatile xdata *)0xfecc) 
#define PWMA_CCMR1  (*(unsigned char volatile xdata *)0xfec8) 
#define PWMA_ENO  (*(unsigned char volatile xdata *)0xfeb1) 
#define PWMA_BKR  (*(unsigned char volatile xdata *)0xfedd) 
#define PWMA_CCR1  (*(unsigned int volatile xdata *)0xfed5) 
#define PWMA_ARR  (*(unsigned int volatile xdata *)0xfed2) 
#define PWMA_CR1  (*(unsigned char volatile xdata *)0xfec0) 
u16 duty_led = 100;  
u16 Duty(u16 duty);//dury%
void led();	//呼吸灯函数
void main() 
{ 
	P0M0 = 0x00; 
	P0M1 = 0x00; 
	P1M0 = 0x00; 
	P1M1 = 0x00; 
	P2M0 = 0x00; 
	P2M1 = 0x00; 
	P3M0 = 0x00; 
	P3M1 = 0x00; 
	P4M0 = 0x00; 
	P4M1 = 0x00; 
	P5M0 = 0x00; 
	P5M1 = 0x00; 

	P_SW2 = 0x80; //sfr P_SW2 = 0xba; 
	PWMA_CCER1 = 0x00; //写 CCMRx 前必须先清零 CCERx 关闭通道 
	PWMA_CCMR1 = 0x60; //设置 CC1 为 PWMA 输出模式 
	PWMA_CCER1 = 0x05; //使能 CC1 通道 反相输出的
	PWMA_CCR1 = 10000; //设置占空比时间 
	PWMA_ARR = PWMA_Period; //设置周期时间 
	PWMA_ENO = 0x03; //使能 PWM1P 端口输出 
	PWMA_BKR = 0x80; //使能主输出 
	PWMA_CR1 = 0x01; //开始计时 
	//PWMA_CCR1 = Duty(75);
	while (1)
	{
		led();
		PWMA_CCR1 = Duty(duty_led);
	}
}
unsigned int Duty(u16 duty)//dury% 0-1000
{
		return PWMA_Period*0.001*duty;
}
void led()//呼吸灯函数
{
	static u8 flag_led = 0;
	static u16 led_t = 200;
	static u16 i = 0;
	if(duty_led>=700)led_t = 400;
	else led_t = 200;
	if((!flag_led)&&i>=led_t){
		i = 0;
		duty_led++;if(duty_led>=960)flag_led = 1;
	}
	if(flag_led&&i>=led_t){
		i = 0;
		duty_led--;if(duty_led<=400)flag_led = 0;
	}i++;
}