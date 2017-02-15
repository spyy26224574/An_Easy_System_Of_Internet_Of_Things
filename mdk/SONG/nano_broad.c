#include "nano_broad.h"
void BLed_Init()
{

	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);
	gpio.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
	GPIO_Init(GPIOC, &gpio);
	PBout(0) = 1;
	PCout(3) = 1;
	PCout(4) = 1;

}

void BKey_Init()
{

	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	gpio.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &gpio);
	gpio.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &gpio);

}

void BExit_Init()
{

	EXTI_InitTypeDef exit;
	NVIC_InitTypeDef nvic;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);
	exit.EXTI_Line = EXTI_Line0;
	exit.EXTI_LineCmd = ENABLE;
	exit.EXTI_Mode = EXTI_Mode_Interrupt;
	exit.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&exit);

	exit.EXTI_Line = EXTI_Line13;
	EXTI_Init(&exit);

	nvic.NVIC_IRQChannel = EXTI0_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x02;
	nvic.NVIC_IRQChannelSubPriority = 0x02;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_Init(&nvic);

}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) != RESET)
	{

		if (LED0 == 1)
		{
			printf("LED0 On");
			PBout(0) = 0;
		}
		else
			PBout(0) = 1;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line13) != RESET)
	{
		if (LED1 == 1)
		{
			printf("LED1 On");
			PCout(3) = 0;
		}
		else
			PCout(3) = 1;
	}
	EXTI_ClearITPendingBit(EXTI_Line13);
}
