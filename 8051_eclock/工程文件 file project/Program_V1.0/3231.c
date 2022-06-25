
#include "3231.h"
#include "delay.h"
#include "intrins.h"

uchar hour,min,sec,year,mon,day,week;
bit	ack;		//应答标志位

/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{
	SCL = 1;		
	SDA = 1;
	SDA = 0;
	_nop_();
	SCL = 0;
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
	SCL = 1;
	SDA = 0;
	SDA = 1;
}

/********************************************************************************************************
** 	3231
********************************************************************************************************/
uchar	BCD2HEX(uchar val)
{
	return	((val>>4)*10)+(val&0x0f);
}

uchar	HEX2BCD(uchar val)
{
	return	(((val%100)/10)<<4)|(val%10);
}


void SendByte(uchar c)
{
	uchar BitCnt;
	SCL=0;
	for(BitCnt=0;BitCnt<8;BitCnt++)         //要传送的数据长度为8位
	{
		if((c<<BitCnt)&0x80)
			SDA=1;                          //判断发送位
		else 
			SDA=0; 
		_nop_();
		SCL=1;                            //置时钟线为高，通知被控器开始接收数据位
		Delay5us();                       //保证时钟高电平周期大于4μs   
		SCL=0;
	}
	SDA=1;                                  //8位发送完后释放数据线，准备接收应答位
	_nop_();
	SCL=1;
	Delay5us();
	if(SDA==1)
			ack=0;    
	else
			ack=1;                              //判断是否接收到应答信号
	SCL=0;
	Delay5us();
}	   

uchar RcvByte()
{
	uchar retc;
	uchar BitCnt;

	retc=0;
	SDA=1;                           //置数据线为输入方式
	for(BitCnt=0;BitCnt<8;BitCnt++)
	{
		SCL=0;                      //置时钟线为低，准备接收数据位       
		Delay5us();                 //时钟低电平周期大于4.7μs		       
		SCL=1;                      //置时钟线为高使数据线上数据有效
		Delay5us();
		retc=retc<<1;
		if(SDA==1)
				retc=retc+1;            //读数据位,接收的数据位放入retc中
		Delay5us();
	}
	SCL=0;
	return(retc);
}			    
 
void Ack_I2C(bit a)
{
	SDA	=	a;  
	SCL=1;		      
	Delay5us();             //时钟低电平周期大于4us    
	SCL=0;                  //清时钟线，钳住I2C总线以便继续接收
	Delay5us();   
}					    

uchar write_byte(uchar addr, uchar write_data)
{
	IIC_Start();
	SendByte(DS3231_WriteAddress);
	if (ack == 0)
			return 0;
 
	SendByte(addr);   
	if (ack == 0)
			return 0;
 
	SendByte(write_data);
	if (ack == 0)
			return 0;
 
	IIC_Stop();
	Delay5us();      
	Delay5us();      
	return 1;
}					  

uchar read_current()
{
	uchar read_data;
	IIC_Start();
	SendByte(DS3231_ReadAddress);
	if(ack==0)
		 return(0);	      
	read_data = RcvByte();
	Ack_I2C(1);
	IIC_Stop();
	return read_data;
}						 

uchar read_random(uchar random_addr)
{
	uchar Tmp;
	IIC_Start();
	SendByte(DS3231_WriteAddress);
	if(ack==0)
			return(0);	    
	SendByte(random_addr);
	if(ack==0)
			return(0);
	Tmp=read_current();
	if(random_addr==DS3231_HOUR) 
	Tmp&=0x3f;
						
	return(BCD2HEX(Tmp));//都转10进制输出
}

/***********************/
uchar read_randomTmp(uchar random_addr)  //这个是读温度函数
{
	uchar Tmp;
	write_byte(0x0e,0x20);//0x0e寄存器的CONV位置1开启温度转换，要这句，温度实时刷新，这句不要，温度要64s才刷新1次
	IIC_Start();
	SendByte(DS3231_WriteAddress);
	if(ack==0)
			return(0);	    
	SendByte(random_addr);
	if(ack==0)
			return(0);
	Tmp=read_current();
	return Tmp;
}				  

void ModifyTime(uchar address,uchar num)
{
	uchar temp=0;
	if(address>6 && address <0) return;
	temp=HEX2BCD(num);
	write_byte(address,temp);
}

/*********************/	
//void get_Temperature()	 //温度获取 显示
//{
//  uchar Tem_L; 
//	uchar Tem_H;
//  Tem_H=read_randomTmp(DS3231_TEMPERATUREH);    //温度 高字节 整数部分
//	Tem_L=read_randomTmp(DS3231_TEMPERATUREL);	 //温度 低字节 小数部分
//	
//	Tem_L = (Tem_L>>6)*0.25*100;	 //
//	
//	if(!(Tem_H & 0x80))	//正温度
//	{ 
//		/********显示温度*********/
//		if(Tem_H/10 > 0)
//			//显示温度十位
//		else
//			//否则温度十位为0不显示
//		  //显示温度个位
//		  //显示小数点
//		  //显示温度小数第1位
//		  //显示温度小数第2位
//	}
//	else
//	{ 
//		if(Tem_H & 0x80)	 //负温度
//		{
//			Tem_H =(~Tem_H)+1; //换算成实际温度值
//				/显示“-”负号
//			if(Tem_H/10 > 0)
//				//显示负温度十位
//			else
//				//负温度十位为0不显
//				//显示负温度个位
//		  	//显示小数点
//			  //显示温度小数第1位
//			  //显示温度小数第2位
//		}
//	}
//	//显示℃符号
//}	

