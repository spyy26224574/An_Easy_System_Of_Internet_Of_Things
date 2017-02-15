#ifndef SONG_USER_LCD
#define SONG_USER_LCD
#include "song_IO.h"

#define LcdDataAddr  ((uint32_t)0x60020000)
#define LcdRegAddr   ((uint32_t)0x60000000)

#define Bank1_LCD_C    ((u32)0x60000000)	   
#define Bank1_LCD_D    ((u32)0x60020000)

#define COLUMN		320
#define PAGE		240	

#define STR_WIDTH		6		
#define STR_HEIGHT		12		

#define BACKGROUND		BLACK

#define WHITE		   0xFFFF
#define BLACK        0x0000	
#define GREY          0xF7DE	
#define BLUE          0x001F	
#define BLUE2        0x051F	
#define RED            0xF800	
#define MAGENTA      0xF81F	
#define GREEN        0x07E0	
#define CYAN         0x7FFF
#define YELLOW       0xFFE0	
#define BRED         0XF81F
#define GRED         0XFFE0
#define GBLUE        0X07FF

#define LCD_WR_REG(index)    ((*(__IO u16 *) (LcdRegAddr)) = ((u16)index))
#define LCD_WR_Data(val)       ((*(__IO u16 *) (LcdDataAddr)) = ((u16)(val)))
#define LCD_WR_DATA(val)	    ((*(__IO u16 *) (LcdDataAddr)) = ((u16)(val)))

#define LCD_ILI9341_CMD(index)       LCD_WR_REG(index)
#define LCD_ILI9341_Parameter(val)	 LCD_WR_Data(val)

static uint16_t backcolor = 0x0000;

void Lcd_Delay(__IO uint32_t nCount);
void LCD_GPIO_Config(void);
void LCD_FSMC_Config(void);
void LCD_Rst(void);
void LCD_REG_Config(void);
void Lcd_GramScan(uint16_t option);
void LCD_Clear(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void LCD_SetCursor(uint16_t x, uint16_t y);
void LCD_OpenWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void LCD_SetPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_Config(void);
void LCD_DispChar(uint16_t x, uint16_t y, uint8_t ascii, uint16_t color);
void LCD_SetBack(uint16_t back);
void LCD_DispStr(uint16_t x, uint16_t y, uint8_t *pstr, uint16_t color);

void LCD_DisNum(uint16_t x, uint16_t y, int32_t num, uint16_t color);
void LCD_DisSqure(uint16_t x, uint16_t y, uint16_t width, uint16_t heigth, uint16_t color);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, uint16_t color);
uint16_t LCD_ReadPoint(int x, int y);
uint16_t LCD_RD_data(void);
void LCD_DrawCoords();
void DDSUI(u8 a);
void DDSUI2();
void DDSUI3();
void LCD_DispAnyChar(u16 x, u16 y, u16 width, u16 height, u8 *a, u16 color);
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
void LCD_Invert(u16 x, u16 y, u16 width, u16 heigth);
#endif
