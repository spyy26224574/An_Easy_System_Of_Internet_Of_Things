/*OLD MAIN FUN

#include  "stm32f10x_conf.h"
#include "song_IO.h"
#include "song_usart.h"
#include "song_lcd.h"
#include "nano_broad.h"
#include "includes.h"
#define TASK_STK_SIZE 512
OS_STK T1[TASK_STK_SIZE];
OS_STK T2[TASK_STK_SIZE];
OS_STK ST[TASK_STK_SIZE];
INT16U x = 0, y = 0;
u8 off[3] = { 'o', 'f', 'f' };
u8 on[2] = { 'o', 'n' };
void t1(void * pdata);
void t2(void * pdata);
void start(void * pdata);
int main()
{
	u16 len = 0;
	u16 i = 0;
	delay_init();
	NVIC_Configuration();
	LCD_Config();
	Lcd_GramScan(2);
	LCD_Clear(0, 0, 320, 240, 0x0000);
	BLed_Init();
	BKey_Init();
	SUsartInit(9600);
	BExit_Init();
//	LCD_DispChar(10,10,'M',0xffff);
//	while (1);
//	OSInit();
//	OSTaskCreate(start,(void *)0,&ST[TASK_STK_SIZE-1],10);
//	OSStart();
	while (1)
	{
		if (USART_RX_STA & 0x8000)
		{
			len = USART_RX_STA & 0x3fff;
			if (len > 0)
			{
				if (len == 2)
				{
					for (i = 0; i < 2; i++)
					{
						if (USART_RX_BUF[i] != on[i])
							break;
					}
					PCout(4) = 0;
					printf("led on\r\n");
					
				}
				else if (len == 3)
				{
					for (i = 0; i < 3; i++)
					{
						if (USART_RX_BUF[i] != off[i])
							break;
					}
					PCout(4) = 1;
					printf("led off\r\n");
				}
				else
					printf("ilegal command!\r\n");
			}
			USART_RX_STA = 0;
		}
	}
}
/*
void t1(void * pdata)
{
	OS_CPU_SR cpu_sr = 0;
	for (;;)
	{
		if (x > 319)
		{
			y += 14;
			x = 0;
		}
	
		OS_ENTER_CRITICAL();
		LCD_DispChar(x, y, 'Y', 0xffff);
		x += 8;
		OS_EXIT_CRITICAL();
		OSTimeDlyHMSM(0, 0, 3, 0);

	}
}

void t2(void * pdata)
{
	OS_CPU_SR cpu_sr = 0;
	for (;;)
	{
		if (x > 319)
		{
			y += 14;
			x = 0;
		}
	
		OS_ENTER_CRITICAL();
		LCD_DispChar(x, y, 'M', 0xffff);
		x += 8;
		OS_EXIT_CRITICAL();
		OSTimeDlyHMSM(0, 0, 1, 0);

	}
}

/*
void t1(void*pdate)
{
	while (1)
	{
		PBout(0) = 1;
		OSTimeDlyHMSM(0, 0, 1, 0);
		PBout(0) = 0;
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}
void t2(void * pdate)
{
	while (1)
	{
		PCout(3) = 1;
		OSTimeDlyHMSM(0, 0, 3, 0);
		PCout(3) = 0;
		OSTimeDlyHMSM(0, 0, 3, 0);
	}
}

void start(void * pdata)
{
	OS_CPU_SR cpu_sr = 0;
	OS_ENTER_CRITICAL();
	OSTaskCreate(t1, 0, &T1[TASK_STK_SIZE - 1], 7);
	OSTaskCreate(t2, 0, &T2[TASK_STK_SIZE - 1], 6);
	OSTaskSuspend(10);
	OS_EXIT_CRITICAL();
}

*/



#include"song_IO.h"
#include"song_time3.h"
#include"song_lcd.h"
#include"song_usart.h"
#include"song_usart3.h"
#include"nano_broad.h"
#include"song_molloc.h"
#include"song_esp8266.h"
int main()
{
	u8 len,t,a;
	u16 x = 0;
	u8 flag = 0;
	u8 y = 12;
	u8 *p;
	delay_init();
	NVIC_Configuration();
	LCD_Config();
	SUsartInit(115200);
	Lcd_GramScan(2);
	LCD_Clear(0, 0, 320, 240, 0x0000);
	BLed_Init();
	BKey_Init();
	usart3_init(115200);
	my_mem_init(SRAMIN);
	p = mymalloc(SRAMIN, 32);
	printf("init finish\r\n");
	LCD_DispStr(0, 0, "init finish",0xffff);
	atk_8266_quit_trans();
	atk_8266_send_cmd("AT+CIPMODE=0", "OK", 200);
	atk_8266_send_cmd("AT+CWMODE=1", "OK", 200);
	a=atk_8266_send_cmd("AT+RST", "OK", 2000);
	SDelayMs(1000);
	SDelayMs(1000);
	SDelayMs(1000);
	SDelayMs(1000);
	sprintf((char*)p, "AT+CIPSTART=\"TCP\",\"115.159.34.201\",12345");
	atk_8266_send_cmd(p, "OK", 2000);
	atk_8266_send_cmd("AT+CIPMODE=1", "OK", 200);
	atk_8266_send_cmd("AT+CIPSEND", "OK", 20);
	SDelayMs(1000);
	SDelayMs(1000);
	SDelayMs(1000);
	SDelayMs(1000);
	printf("finish\r\n");
	while (1)
	{
		if (USART3_RX_STA & 0x8000)
		{
			len = USART3_RX_STA & 0x7fff;
			for (t = 0; t<len; t++)
			{
				USART_SendData(USART1, USART3_RX_BUF[t]);
				while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
				if (x>319)
				{
					x = 0;
					y += 14;
				}
				
				if ((USART3_RX_BUF[t] <127) && (USART3_RX_BUF[t] >32))
				{
					
					LCD_DispChar(x, y, USART3_RX_BUF[t], 0xffff);
				}
				x += 6;
			}
			
			if(USART3_RX_BUF[0]=='o')
				if(USART3_RX_BUF[1]=='k')
				{
					if(flag==0)
					{
						PBout(0)=1;
						flag=1;
					}
					else
					{
						PBout(0)=0;
						flag=0;
					}
					
				}
	//		LCD_DispStr(0, 12, USART3_RX_BUF, 0xffff);
			USART3_RX_STA = 0;
		}
	}
}














