#ifndef		__3231_H
#define		__3231_H

#include <STC8.H>
#define uint  unsigned int
#define uchar unsigned char
// ------------------------------------------------------------
// IO口模拟I2C通信
// ------------------------------------------------------------
sbit SCL=P1^0; //串行时钟
sbit SDA=P1^1; //串行数据

extern char hour,min,sec,year,mon,day,week;
extern bit	ack;		//应答标志位
/********************************************************************************************************
** 	DS3231常数定义
********************************************************************************************************/
#define DS3231_WriteAddress 0xD0    //器件写地址 
#define DS3231_ReadAddress  0xD1    //器件读地址
#define DS3231_SECOND       0x00    //秒
#define DS3231_MINUTE       0x01    //分
#define DS3231_HOUR         0x02    //时
#define DS3231_WEEK         0x03    //星期
#define DS3231_DAY          0x04    //日
#define DS3231_MONTH        0x05    //月
#define DS3231_YEAR         0x06    //年

#define DS3231_TEMPERATUREH 0x11    //温度寄存器高字节(8位)	整数部分
#define DS3231_TEMPERATUREL 0x12    //温度寄存器低字节(低2位) 小数部分 

#define NACK    1
#define ACK     0

extern void IIC_Start();
extern void IIC_Stop();
extern uchar	BCD2HEX(uchar val);
extern uchar	HEX2BCD(uchar val);
extern void SendByte(uchar c);	
extern uchar RcvByte();	
extern void Ack_I2C(bit a);	
extern uchar write_byte(uchar addr, uchar write_data);	
extern uchar read_current();
extern uchar read_random(uchar random_addr);//读取时间
extern uchar read_randomTmp(uchar random_addr);
extern void ModifyTime(uchar address,uchar num);//修改时间

#endif