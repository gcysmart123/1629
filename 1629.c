																							  /*****************************************************************************
 *版权信息：深圳天微电子有限公司
 *文 件 名：TM1629A-V1.0
 *当前版本：V1.0
 *MCU 型号：STC12C5608AD
 *开发环境：Keil uVision4
 *晶震频率：11.0592MHZ       
 *完成日期：2013-07-30
 *程序功能：1.数码管驱动：驱动2组8段8位LED共阴数码管显示0~F，电路图请参考TM1629A规格书共阴接法；
 *免责声明：1.此程序为TM1629A驱动LED数码管演示程序，仅作参考之用。
            2.如有直接使用本例程程序造成经济损失的，本公司不承担任何责任             
********************************************************************************/

#include <reg52.h>				//MCU头文件
#include "intrins.h"				//包含nop指令头文件

#define nop _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();//宏定义


/********************定义控制端口**********************/
sbit DIO=P0^1;						//定义DIO
sbit CLK=P0^0;						//定义CLK
sbit STB=P0^2;						//定义STB

/********************定义数据*************************/
//unsigned char const CODE[]={0x3F,0x06,0x5B,0x4F,0xFF,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,};	   //共阴数码管0~F字型码，与实际电路接法为准
unsigned char const CODE[]={0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,};	   //共阴数码管0~F字型码，与实际电路接法为准
/***************发送8bit数据，从低位开始**************/
void send_8bit(unsigned char dat)	
{
  unsigned char i;
  for(i=0;i<8;i++)
  {	 
    CLK=0;
    if(dat&0x01) 
	   DIO=1;
	 else 
	   DIO=0;
	 _nop_();
	 _nop_();
	 _nop_();
	 CLK=1;
	 dat>>=1;
  }
   CLK=0;
   DIO=0;
}

/******************发送控制命令***********************/
void send_command(unsigned char word)
{
 STB=1;
 nop;
 STB=0;
 send_8bit(word);
}

/************显示函数，数码管1~16位显示0~F************/
void display()		
{
 unsigned char i;
 send_command(0x40);	//设置数据命令:普通模式、地址自增1，写数据到显存
 send_command(0xc0);	//设置显示地址命令：从00H开始
 for(i=0;i<16;i++)	//发送16字节的显存数据
 {
  send_8bit(CODE[i]);
 }
 send_command(0x8C);	//设置显示控制命令：打开显示，并设置为11/16.
 STB=1;
}


void main()
{

while(1)
{
 display();		  //上电显示0~F
 }
}


