#ifndef		__TM1637_H
#define		__TM1637_H
#include <STC8.H>

#define u8 unsigned char
#define u16 unsigned int

sbit DIO = P1^5;
sbit CLK = P1^4;

extern void I2CStart();
extern void I2CAsk();
extern void I2CStop();
extern void I2CWriteByte(u8 dat);
extern void Tm1636_write_display(u8 mode);//1:自动;0;固定
extern void Tm1636_set_segbit(u8 addr);//四位0-3,自动模式必须是0	
extern void Tm1636_display(u16 num);
extern void Tm1636_discon(u8 light);//亮度0-7
extern void display_4seg(u8 G1,u8 G2,u8 G3,u8 G4);//自动模式四位数码管显示	

#endif