#include "song_font.h"
#include "song_lcd.h"
void Lcd_Delay(__IO uint32_t nCount)
{
	for (; nCount != 0; nCount--);
}

void LCD_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

	     
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD
		| RCC_APB2Periph_GPIOE
		| RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 |
		GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
		GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
		GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#if 1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
#elif 0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD, GPIO_Pin_13);
#endif
}

void LCD_FSMC_Config(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  p;


	p.FSMC_AddressSetupTime = 0x02;
	p.FSMC_AddressHoldTime = 0x00;
	p.FSMC_DataSetupTime = 0x05;
	p.FSMC_BusTurnAroundDuration = 0x00;
	p.FSMC_CLKDivision = 0x00;
	p.FSMC_DataLatency = 0x00;
	p.FSMC_AccessMode = FSMC_AccessMode_B;

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;

	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

void LCD_Rst(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);
	Lcd_Delay(0xAFFf << 2);
	GPIO_SetBits(GPIOE, GPIO_Pin_1);
	Lcd_Delay(0xAFFf << 2);
}

void LCD_REG_Config(void)
{

	//	DEBUG_DELAY();
	LCD_ILI9341_CMD(0xCF);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x81);
	LCD_ILI9341_Parameter(0x30);


	//DEBUG_DELAY();
	LCD_ILI9341_CMD(0xED);
	LCD_ILI9341_Parameter(0x64);
	LCD_ILI9341_Parameter(0x03);
	LCD_ILI9341_Parameter(0x12);
	LCD_ILI9341_Parameter(0x81);


	//DEBUG_DELAY();
	LCD_ILI9341_CMD(0xE8);
	LCD_ILI9341_Parameter(0x85);
	LCD_ILI9341_Parameter(0x10);
	LCD_ILI9341_Parameter(0x78);


	//DEBUG_DELAY();
	LCD_ILI9341_CMD(0xCB);
	LCD_ILI9341_Parameter(0x39);
	LCD_ILI9341_Parameter(0x2C);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x34);
	LCD_ILI9341_Parameter(0x02);


	//DEBUG_DELAY();
	LCD_ILI9341_CMD(0xF7);
	LCD_ILI9341_Parameter(0x20);


	//	DEBUG_DELAY();
	LCD_ILI9341_CMD(0xEA);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x00);


	//DEBUG_DELAY();
	LCD_ILI9341_CMD(0xB1);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x1B);


	//DEBUG_DELAY();
	LCD_ILI9341_CMD(0xB6);
	LCD_ILI9341_Parameter(0x0A);
	LCD_ILI9341_Parameter(0xA2);


	//DEBUG_DELAY();
	LCD_ILI9341_CMD(0xC0);
	LCD_ILI9341_Parameter(0x35);


	//DEBUG_DELAY();
	LCD_ILI9341_CMD(0xC1);
	LCD_ILI9341_Parameter(0x11);


	LCD_ILI9341_CMD(0xC5);
	LCD_ILI9341_Parameter(0x45);
	LCD_ILI9341_Parameter(0x45);


	LCD_ILI9341_CMD(0xC7);
	LCD_ILI9341_Parameter(0xA2);


	LCD_ILI9341_CMD(0xF2);
	LCD_ILI9341_Parameter(0x00);


	LCD_ILI9341_CMD(0x26);
	LCD_ILI9341_Parameter(0x01);
	//	DEBUG_DELAY();
	LCD_ILI9341_CMD(0xE0);
	LCD_ILI9341_Parameter(0x0F);
	LCD_ILI9341_Parameter(0x26);
	LCD_ILI9341_Parameter(0x24);
	LCD_ILI9341_Parameter(0x0B);
	LCD_ILI9341_Parameter(0x0E);
	LCD_ILI9341_Parameter(0x09);
	LCD_ILI9341_Parameter(0x54);
	LCD_ILI9341_Parameter(0xA8);
	LCD_ILI9341_Parameter(0x46);
	LCD_ILI9341_Parameter(0x0C);
	LCD_ILI9341_Parameter(0x17);
	LCD_ILI9341_Parameter(0x09);
	LCD_ILI9341_Parameter(0x0F);
	LCD_ILI9341_Parameter(0x07);
	LCD_ILI9341_Parameter(0x00);


	LCD_ILI9341_CMD(0XE1);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x19);
	LCD_ILI9341_Parameter(0x1B);
	LCD_ILI9341_Parameter(0x04);
	LCD_ILI9341_Parameter(0x10);
	LCD_ILI9341_Parameter(0x07);
	LCD_ILI9341_Parameter(0x2A);
	LCD_ILI9341_Parameter(0x47);
	LCD_ILI9341_Parameter(0x39);
	LCD_ILI9341_Parameter(0x03);
	LCD_ILI9341_Parameter(0x06);
	LCD_ILI9341_Parameter(0x06);
	LCD_ILI9341_Parameter(0x30);
	LCD_ILI9341_Parameter(0x38);
	LCD_ILI9341_Parameter(0x0F);


	//DEBUG_DELAY();
	LCD_ILI9341_CMD(0x36);
	LCD_ILI9341_Parameter(0xC8);
	//	DEBUG_DELAY();


	LCD_ILI9341_CMD(0X2A);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0xEF);


	//DEBUG_DELAY();
	LCD_ILI9341_CMD(0X2B);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x00);
	LCD_ILI9341_Parameter(0x01);
	LCD_ILI9341_Parameter(0x3F);


	//	DEBUG_DELAY();
	LCD_ILI9341_CMD(0x3a);
	LCD_ILI9341_Parameter(0x55);


	LCD_ILI9341_CMD(0x11);
	Lcd_Delay(0xAFFf << 2);
	//	DEBUG_DELAY();


	LCD_ILI9341_CMD(0x29);
}

void Lcd_GramScan(uint16_t option)
{
	switch (option)
	{
	case 1:                                                   //从左上角到右下角
	{
																  LCD_ILI9341_CMD(0x36);
																  LCD_ILI9341_Parameter(0xC8);
																  LCD_ILI9341_CMD(0X2A);
																  LCD_ILI9341_Parameter(0x00);
																  LCD_ILI9341_Parameter(0x00);
																  LCD_ILI9341_Parameter(0x00);
																  LCD_ILI9341_Parameter(0xEF);

																  LCD_ILI9341_CMD(0X2B);
																  LCD_ILI9341_Parameter(0x00);
																  LCD_ILI9341_Parameter(0x00);
																  LCD_ILI9341_Parameter(0x01);
																  LCD_ILI9341_Parameter(0x3F);

	}break;
	case 2:												//左下->右上
	{
															LCD_ILI9341_CMD(0x36);
															LCD_ILI9341_Parameter(0x68);
															LCD_ILI9341_CMD(0X2A);
															LCD_ILI9341_Parameter(0x00);
															LCD_ILI9341_Parameter(0x00);
															LCD_ILI9341_Parameter(0x01);
															LCD_ILI9341_Parameter(0x3F);

															LCD_ILI9341_CMD(0X2B);
															LCD_ILI9341_Parameter(0x00);
															LCD_ILI9341_Parameter(0x00);
															LCD_ILI9341_Parameter(0x00);
															LCD_ILI9341_Parameter(0xEF);
	}break;
	case 3:													//右下->左上
	{
																LCD_ILI9341_CMD(0x36);
																LCD_ILI9341_Parameter(0x28);
																LCD_ILI9341_CMD(0X2A);
																LCD_ILI9341_Parameter(0x00);
																LCD_ILI9341_Parameter(0x00);
																LCD_ILI9341_Parameter(0x01);
																LCD_ILI9341_Parameter(0x3F);

																LCD_ILI9341_CMD(0X2B);
																LCD_ILI9341_Parameter(0x00);
																LCD_ILI9341_Parameter(0x00);
																LCD_ILI9341_Parameter(0x00);
																LCD_ILI9341_Parameter(0xEF);
	}break;
	case 4:
	{
			  LCD_ILI9341_CMD(0x36);
			  LCD_ILI9341_Parameter(0x48);
			  LCD_ILI9341_CMD(0X2A);
			  LCD_ILI9341_Parameter(0x00);
			  LCD_ILI9341_Parameter(0x00);
			  LCD_ILI9341_Parameter(0x00);
			  LCD_ILI9341_Parameter(0xEF);

			  LCD_ILI9341_CMD(0X2B);
			  LCD_ILI9341_Parameter(0x00);
			  LCD_ILI9341_Parameter(0x00);
			  LCD_ILI9341_Parameter(0x01);
			  LCD_ILI9341_Parameter(0x3F);
	}break;
	}

	LCD_ILI9341_CMD(0x2C);
}

uint16_t LCD_RD_data(void)
{
	uint16_t R = 0, G = 0, B = 0;
	R = *(__IO uint16_t *)Bank1_LCD_D; 	  /*FIRST READ OUT DUMMY DATA*/
	R = *(__IO uint16_t *)Bank1_LCD_D;  	/*READ OUT RED DATA  */
	B = *(__IO uint16_t *)Bank1_LCD_D;  	/*READ OUT BLACK DATA*/
	G = *(__IO uint16_t *)Bank1_LCD_D;  	/*READ OUT GREEN DATA*/

	return (((R >> 11) << 11) | ((G >> 10) << 5) | (B >> 11));
}

void LCD_Clear(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)//从x到y开始写数据，也可用于画矩形。
{
	uint32_t i = 0;
	LCD_ILI9341_CMD(0X2A);
	LCD_ILI9341_Parameter(x >> 8);	 //高八位
	LCD_ILI9341_Parameter(x & 0xff);	         /* column start   *///第八位
	LCD_ILI9341_Parameter((x + width - 1) >> 8);   /* column end   */
	LCD_ILI9341_Parameter((x + width - 1) & 0xff);

	/* page address control set */
	LCD_ILI9341_CMD(0X2B);
	LCD_ILI9341_Parameter(y >> 8);			/* page start   */
	LCD_ILI9341_Parameter(y & 0xff);
	LCD_ILI9341_Parameter((y + height - 1) >> 8);  /* page end     */
	LCD_ILI9341_Parameter((y + height - 1) & 0xff);

	/* memory write */
	LCD_ILI9341_CMD(0x2c);//写颜色数据

	for (i = 0; i < width*height; i++)
	{
		LCD_WR_Data(color);
		//Delay(0x0FFf);
	}
}

void LCD_SetBack(uint16_t back)
{
	backcolor = back;
}
void LCD_SetCursor(uint16_t x, uint16_t y)//设置光标
{
	*(__IO uint16_t *)(Bank1_LCD_C) = (0X2A);
	*(__IO uint16_t *)(Bank1_LCD_D) = (x >> 8);
	*(__IO uint16_t *)(Bank1_LCD_D) = (x & 0xff);
	*(__IO uint16_t *)(Bank1_LCD_D) = (x >> 8);
	*(__IO uint16_t *)(Bank1_LCD_D) = (x & 0xff);

	*(__IO uint16_t *)(Bank1_LCD_C) = 0x2B;
	*(__IO uint16_t *)(Bank1_LCD_D) = (x >> 8);
	*(__IO uint16_t *)(Bank1_LCD_D) = (y & 0xff);
	*(__IO uint16_t *)(Bank1_LCD_D) = (y >> 8);
	*(__IO uint16_t *)(Bank1_LCD_D) = (y & 0xff);
}

void LCD_OpenWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	LCD_ILI9341_CMD(0X2A);
	LCD_ILI9341_Parameter(x >> 8);
	LCD_ILI9341_Parameter(x & 0xff);
	LCD_ILI9341_Parameter((x + width - 1) >> 8);
	LCD_ILI9341_Parameter((x + width - 1) & 0xff);

	LCD_ILI9341_CMD(0X2B);
	LCD_ILI9341_Parameter(y >> 8);
	LCD_ILI9341_Parameter(y & 0xff);
	LCD_ILI9341_Parameter((y + height - 1) >> 8);
	LCD_ILI9341_Parameter((y + height - 1) & 0xff);
}

void LCD_SetPoint(uint16_t x, uint16_t y, uint16_t color)//画点
{
	*(__IO uint16_t *)(Bank1_LCD_C) = (0X2A);
	*(__IO uint16_t *)(Bank1_LCD_D) = (x >> 8);
	*(__IO uint16_t *)(Bank1_LCD_D) = (x & 0xff);
	*(__IO uint16_t *)(Bank1_LCD_D) = (x >> 8);
	*(__IO uint16_t *)(Bank1_LCD_D) = (x & 0xff);

	*(__IO uint16_t *)(Bank1_LCD_C) = 0x2B;
	*(__IO uint16_t *)(Bank1_LCD_D) = (x >> 8);
	*(__IO uint16_t *)(Bank1_LCD_D) = (y & 0xff);
	*(__IO uint16_t *)(Bank1_LCD_D) = (y >> 8);
	*(__IO uint16_t *)(Bank1_LCD_D) = (y & 0xff);

	*(__IO uint16_t *)(Bank1_LCD_C) = 0x2C;
	*(__IO uint16_t *)(Bank1_LCD_D) = color;
}

void LCD_Config(void)
{
	LCD_GPIO_Config();
	LCD_FSMC_Config();
	LCD_Rst();
	LCD_REG_Config();
}

void LCD_DispChar(uint16_t x, uint16_t y, uint8_t ascii, uint16_t color)
{
	uint16_t page, column, temp, i;
	i = ascii - ' ';

	LCD_OpenWindow(x, y, STR_WIDTH, STR_HEIGHT);
	LCD_ILI9341_CMD(0X2C);

	for (page = 0; page < STR_HEIGHT; page++)
	{
		temp = asc2_1206[i][page];
		for (column = 0; column < STR_WIDTH; column++)
		{
			if (temp & 0x01)
			{
				LCD_WR_Data(color);
			}
			else
			{
				LCD_WR_Data(backcolor);
			}
			temp >>= 1;
		}
	}
}

void LCD_DispAnyChar(u16 x, u16 y, u16 width, u16 height, u8 *a, u16 color)
{
	u16 i, j;
	u8 m;
	u16 bitwidth = 0;
	u8 tmp;
	LCD_OpenWindow(x, y, width, height);
	LCD_ILI9341_CMD(0X2C);

	if (width % 8 == 0)
	{
		bitwidth = width / 8;
	}
	else
		bitwidth = width / 8 + 1;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < bitwidth; j++)
		{
			tmp = a[i*bitwidth + j];
			if (j != bitwidth - 1)
			{
				for (m = 0; m < 8; m++)
				{
					if (tmp & 0x80)
						LCD_WR_Data(color);
					else
						LCD_WR_Data(backcolor);
					tmp <<= 1;
				}
			}
			else if (width % 8)
			{
				for (m = 0; m < width % 8; m++)
				{
					if (tmp & 0x80)
						LCD_WR_Data(color);
					else
						LCD_WR_Data(backcolor);
					tmp <<= 1;
				}
			}
			else
			{
				for (m = 0; m < 8; m++)
				{
					if (tmp & 0x80)
						LCD_WR_Data(color);
					else
						LCD_WR_Data(backcolor);
					tmp <<= 1;
				}
			}
		}
	}
}



void LCD_DispStr(uint16_t x, uint16_t y, uint8_t *pstr, uint16_t color)
{
	while (*pstr != '\0')
	{
		if (x > (COLUMN - STR_WIDTH))
		{
			x = 0;
			y += STR_HEIGHT;
		}
		if (y > (PAGE - STR_HEIGHT))
		{
			x = 0;
			y = 0;
		}
		LCD_DispChar(x, y, *pstr, color);
		x += STR_WIDTH;
		pstr++;
	}
}


void LCD_DisNum(uint16_t x, uint16_t y, int32_t num, uint16_t color)
{
	uint32_t length = 0, temp = 0;

	if (num >= 0)
	{
		temp = num;
		if (temp == 0)
		{
			LCD_DispChar(x, y, '0', color);
			return;
		}

		while (temp)
		{
			temp /= 10;
			length++;
		}

		while (num)
		{
			LCD_DispChar((x + STR_WIDTH*(length--) - STR_WIDTH), y, (num % 10) + '0', color);
			num /= 10;
		}
	}
	else
	{
		num = num*-1;
		temp = num;
		LCD_DispChar(x, y, '-', color);
		if (temp == 0)
		{
			LCD_DispChar(x, y, '0', color);
			return;
		}

		while (temp)
		{
			temp /= 10;
			length++;
		}
		length++;
		while (num)
		{
			LCD_DispChar((x + STR_WIDTH*(length--) - STR_WIDTH), y, (num % 10) + '0', color);
			num /= 10;
		}
	}
}


uint16_t LCD_ReadPoint(int x, int y)
{
	uint16_t temp;
	LCD_SetCursor(x, y);
	LCD_ILI9341_CMD(0x2e);
	temp = LCD_RD_data();
	return (temp);
}


void LCD_Invert(u16 x, u16 y, u16 width, u16 heigth)
{
	u16 i, j;
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < heigth; j++)
		{
			if (LCD_ReadPoint(x + i, y + j) == 0x0000)
			{
				LCD_SetCursor(x + i, y + j);
				LCD_ILI9341_CMD(0X2C);
				*(__IO uint16_t *)(Bank1_LCD_D) = 0xffff;
			}
			else if (LCD_ReadPoint(x + i, y + j) == 0xffff)
			{
				LCD_SetCursor(x + i, y + j);
				LCD_ILI9341_CMD(0X2C);
				*(__IO uint16_t *)(Bank1_LCD_D) = 0x0000;
			}
		}
	}
}


void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, uint16_t color)
{
	u16 t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	uRow = x1;
	uCol = y1;
	if (delta_x>0)incx = 1;
	else if (delta_x == 0)incx = 0;
	else { incx = -1; delta_x = -delta_x; }
	if (delta_y>0)incy = 1;
	else if (delta_y == 0)incy = 0;
	else{ incy = -1; delta_y = -delta_y; }
	if (delta_x>delta_y)distance = delta_x;
	else distance = delta_y;
	for (t = 0; t <= distance + 1; t++)
	{
		LCD_SetPoint(uRow, uCol, color);
		xerr += delta_x;
		yerr += delta_y;
		if (xerr>distance)
		{
			xerr -= distance;
			uRow += incx;
		}
		if (yerr>distance)
		{
			yerr -= distance;
			uCol += incy;
		}
	}
}

void LCD_DrawCoords()
{
	u16 a;
	u16 b = 0;
	for (a = 0; a < 48; a++)
	{
		LCD_SetPoint(160, a * 5, 0xffff);
	}
	for (b = 0; b < 64; b++)
	{
		LCD_SetPoint(b * 5, 120, 0xffff);
	}
	for (a = 0; a < 9; a++)
	{
		if (a != 4)
		{
			LCD_SetPoint(161, (4 + 5 * a) * 5, 0xffff);
		}
	}

	for (a = 0; a < 9; a++)
	{
		if (a != 4)
		{
			LCD_SetPoint(162, (4 + 5 * a) * 5, 0xffff);
		}
	}

	for (b = 0; b < 13; b++)
	{
		if (b != 6)
		{
			LCD_SetPoint((2 + 5 * b) * 5, 119, 0xffff);
		}
	}
	for (b = 0; b < 13; b++)
	{
		if (b != 6)
		{
			LCD_SetPoint((2 + 5 * b) * 5, 118, 0xffff);
		}
	}	for (a = 0; a < 48; a++)
	{
		LCD_SetPoint(160, a * 5, 0xffff);
	}
	for (b = 0; b < 64; b++)
	{
		LCD_SetPoint(b * 5, 120, 0xffff);
	}
	for (a = 0; a < 9; a++)
	{
		if (a != 4)
		{
			LCD_SetPoint(161, (4 + 5 * a) * 5, 0xffff);
		}
	}

	for (a = 0; a < 9; a++)
	{
		if (a != 4)
		{
			LCD_SetPoint(162, (4 + 5 * a) * 5, 0xffff);
		}
	}

	for (b = 0; b < 13; b++)
	{
		if (b != 6)
		{
			LCD_SetPoint((2 + 5 * b) * 5, 119, 0xffff);
		}
	}
	for (b = 0; b < 13; b++)
	{
		if (b != 6)
		{
			LCD_SetPoint((2 + 5 * b) * 5, 118, 0xffff);
		}
	}

	for (b = 0; b < 6; b++)
	{

		LCD_DisNum(25 * b + 8, 121, (6 - b), 0xffff);

	}

	for (b = 0; b < 6; b++)
	{

		LCD_DisNum(25 * (b + 7) + 8, 121, b + 1, 0xffff);

	}

	for (a = 0; a < 4; a++)
	{
		LCD_DisNum(160 - 12, (4 + 5 * a) * 5 - 5, 4 - a, 0xffff);
	}


	for (a = 0; a < 4; a++)
	{
		LCD_DisNum(160 - 17, (4 + 5 * (a + 5)) * 5 - 5, -(a + 1), 0xffff);
	}
}

void DDSUI(u8 a)
{
	LCD_Clear(0 - a, 200, 40, 40, RED);
	LCD_Clear(50 - a, 200, 40, 40, YELLOW);
	LCD_Clear(100 - a, 200, 40, 40, BLUE);

	LCD_Clear(180 - a, 200, 40, 40, BLUE);
	LCD_Clear(230 - a, 200, 40, 40, YELLOW);
	LCD_Clear(280 - a, 200, 40, 40, RED);

	LCD_Clear(50 - a, 130, 60, 60, GREEN);
	LCD_Clear(210 - a, 130, 60, 60, GREEN);

	LCD_Clear(250 - a, 10, 50, 50, MAGENTA);

	LCD_Clear(10 - a, 10, 30, 30, MAGENTA);
}

void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
{
	LCD_WR_REG(LCD_Reg);
	LCD_WR_Data(LCD_RegValue);
}


void LCD_DisSqure(uint16_t x, uint16_t y, uint16_t width, uint16_t heigth, uint16_t color)
{
	LCD_DrawLine(x, y, x + width, y, color);
	LCD_DrawLine(x + width, y, x + width, y + heigth, color);
	LCD_DrawLine(x + width, y + heigth, x, y + heigth, color);
	LCD_DrawLine(x, y + heigth, x, y, color);
}





void DDSUI3()
{

}