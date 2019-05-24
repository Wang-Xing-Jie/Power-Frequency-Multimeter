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
char  DisBuf[64];	  		  	 //sprintf�������ݻ���

/*******************************************************
˵��: USART2_Send_Char(0xFF);
	  USART2_Send_Char(0XFF);
	  USART2_Send_Char(0XFF);   ��ʾ���ݷ��ͽ���	
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
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	uart_init(9600);	 //���ڳ�ʼ��
	Init0832();						//Ӳ����ʼ��
//	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
// 	bsp_InitSPIBus();	/* ����SPI���� */
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


