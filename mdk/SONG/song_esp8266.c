#include"song_esp8266.h"
u16 x = 0;
u16 y = 0;
//返回值是null或str字符串所在的地址
u8* atk_8266_check_cmd(u8 *str)
{

	char *strx = 0;
	if (USART3_RX_STA & 0X8000)		
	{
		USART3_RX_BUF[USART3_RX_STA & 0X7FFF] = 0;
	//	printf(USART3_RX_BUF);
		strx = strstr((const char*)USART3_RX_BUF, (const char*)str);
	}
	return (u8*)strx;
}

u8 atk_8266_send_cmd(u8 *cmd, u8 *ack, u16 waittime)
{
	u8 res = 0;
	USART3_RX_STA = 0;
	u3_printf("%s\r\n", cmd);	
	if (ack&&waittime)		
	{
		while (--waittime)	
		{
			SDelayMs(10);
			if (USART3_RX_STA & 0X8000) //这时候已经接受到所有的反馈信息.
			{
				if (atk_8266_check_cmd(ack))    //如果是正确的反馈
				{

					printf("ack:%s\r\n", (u8*)ack);
					break;
				}
				USART3_RX_STA = 0;
			}
		}
		if (waittime == 0)res = 1;
	}
	return res;
}

u8 atk_8266_send_data(u8 *data, u8 *ack, u16 waittime)
{
	u8 res = 0;
	USART3_RX_STA = 0;
	u3_printf("%s", data);
	if (ack&&waittime)		
	{
		while (--waittime)	
		{
			SDelayMs(10);
			if (USART3_RX_STA & 0X8000)
			{
				if (atk_8266_check_cmd(ack))break;
				USART3_RX_STA = 0;
			}
		}
		if (waittime == 0)res = 1;
	}
	return res;
}

//退出穿透模式
u8 atk_8266_quit_trans(void)
{
	while ((USART3->SR & 0X40) == 0);	
	USART3->DR = '+';
	SDelayMs(15);
	while ((USART3->SR & 0X40) == 0);	
	USART3->DR = '+';
	SDelayMs(15);
	while ((USART3->SR & 0X40) == 0);	
	USART3->DR = '+';
	SDelayMs(500);
	return atk_8266_send_cmd("AT", "OK", 20);
}


u8 atk_8266_consta_check(void)
{
	u8 *p;
	u8 res;
	if (atk_8266_quit_trans())return 0;			
	atk_8266_send_cmd("AT+CIPSTATUS", ":", 50);	
	p = atk_8266_check_cmd("+CIPSTATUS:");
	res = *p;									
	return res;
}























































































































































