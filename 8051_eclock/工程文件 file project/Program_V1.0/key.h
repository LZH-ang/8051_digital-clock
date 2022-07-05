#ifndef  __key_H
#define  __key_H
#include <STC8.H>

#define u8 unsigned char
#define u16 unsigned int
	
extern u8 mode,dis_format,temp;	//显示界面控制
extern u8 hour_t,min_t,sec_t,mon_t,day_t,year_t,week_t;	//临时存数据
extern bit dis_time,dis_temp;	//月日温度显示控制


sbit SW1 = P3^4;//SET
sbit SW2 = P3^5;//CHANGE
sbit SW3 = P3^6;//ENTER

extern void Key_Set();//SET：短按依次设置时分(秒自动设置为30)月日，按ENTER键确定
extern void Key_Enter();//ENTER：set时，短按写入时间，若无改动或设置完成短按返回正常界面，正常界面短按显示温度，几秒钟后自动显示时分
extern void Key_Change();//CHANGE：set时，设置时间，正常界面短按显示月日

#endif