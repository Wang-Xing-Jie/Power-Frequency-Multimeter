#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "bsp_spi_ad7606.h"
#include "bsp_spi_bus.h"
#include "ad0832.h"

#include <stdio.h> 
#include <math.h> 
#include <string.h> 
char  DisBuf[64];	  		  	 //sprintf函数数据缓存

/*******************************************************
说明: USART2_Send_Char(0xFF);
	  USART2_Send_Char(0XFF);
	  USART2_Send_Char(0XFF);   表示数据发送结束	
********************************************************/
void DisplayLCD(char *s) 
{
 	while(*s!=0x00)
 	{
 		sendchar(*s);
 		s++;
 	}
  sendchar(0xFF);	 
	sendchar(0XFF);	
	sendchar(0XFF);
}


 int main(void)
 {	
	int i=1,j=3;
	unsigned char ADCRawValue=0; 
	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	uart_init(9600);	 //串口初始化
	Init0832();						//硬件初始化
//	LED_Init();		  	 //初始化与LED连接的硬件接口 
// 	bsp_InitSPIBus();	/* 配置SPI总线 */
	DisplayLCD("");	 
	 
	 
	while(1)
	{
		ADCRawValue=ReadADC0832();
		
		sprintf(DisBuf,"t10.txt=\"val: %d\"",ADCRawValue);
		DisplayLCD(DisBuf); 	

		sprintf(DisBuf,"t11.txt=\"ffff\"");
		DisplayLCD(DisBuf); 
		
		sprintf(DisBuf,"t12.txt=\"%4d.%3d\"",i,j);
		DisplayLCD(DisBuf); 		
		
	}	 
}


