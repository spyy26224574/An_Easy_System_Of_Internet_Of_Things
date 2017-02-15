#include "song_usart.h"
#if 1
#pragma import(__use_no_semihosting)             

u8 USART_RX_BUF[USART_REC_LEN];
u16 USART_RX_STA=0 ;
struct __FILE
{
	int handle;
};

FILE __stdout;

_sys_exit(int x)
{
	x = x;
}

int fputc(int ch, FILE *f)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	USART_SendData(USART1, (uint8_t)ch);
	return ch;
}
#endif 

void SUsartInit(u32 bound)
{
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef usart;
	NVIC_InitTypeDef nvic;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	USART_DeInit(USART1);
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_9;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_10;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);

	usart.USART_BaudRate = bound;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usart);

	nvic.NVIC_IRQChannel = USART1_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 3;
	nvic.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&nvic);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void)
{
	u8 Res;

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Res = USART_ReceiveData(USART1);
		if ((USART_RX_STA & 0x8000) == 0)
		{
			if (USART_RX_STA & 0x4000)
			{
				if (Res != 0x0a)USART_RX_STA = 0;
				else USART_RX_STA |= 0x8000;
			}
			else
			{
				if (Res == 0x0d)USART_RX_STA |= 0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA & 0X3FFF] = Res;
					USART_RX_STA++;
					if (USART_RX_STA > (USART_REC_LEN - 1))USART_RX_STA = 0;
				}
			}
		}
	}
}


