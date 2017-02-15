#ifndef BROAD
#define BROAD
#include "song_IO.h"
#define LED0 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) 
#define LED1 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) 
#define LED2 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) 
//init the led on the broad
void BLed_Init();
void BKey_Init();
void BExit_Init();
#endif
