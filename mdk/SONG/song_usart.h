#ifndef SONG_USART_H
#define SONG_USART_H
#include "song_IO.h"
#include "stdio.h"	
#define USART_REC_LEN  			200 

extern u8  USART_RX_BUF[USART_REC_LEN];
extern u16 USART_RX_STA;



void SUsartInit(u32 bound);
#endif
