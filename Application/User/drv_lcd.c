/********************************************************
* @file       drv_lcd.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_lcd.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Drv_Lcd_Init(void )
{
    Hal_Lcd_Init();

    LCD_RST_HIGH();
    Drv_Lcd_Delay_US(1000*48);
	LCD_RST_LOW();
	Drv_Lcd_Delay_US(10000*48);
	LCD_RST_HIGH();
	Drv_Lcd_Delay_US(120000*48);

    Drv_Lcd_Wr_Cmd(0x11);  
    Drv_Lcd_Delay_US(120000*48);
    
    Drv_Lcd_Wr_Cmd(0x36);  
	Drv_Lcd_Wr_Data(0x00); 
    Drv_Lcd_Wr_Cmd(0x3a);  
	Drv_Lcd_Wr_Data(0x06); 
    
    Drv_Lcd_Wr_Cmd(0xb2);  
	Drv_Lcd_Wr_Data(0x0c); 
	Drv_Lcd_Wr_Data(0x0c); 
	Drv_Lcd_Wr_Data(0x00); 
	Drv_Lcd_Wr_Data(0x33); 
	Drv_Lcd_Wr_Data(0x33); 
    Drv_Lcd_Wr_Cmd(0xb7);  
	Drv_Lcd_Wr_Data(0x35); 

    Drv_Lcd_Wr_Cmd(0xbb);  
	Drv_Lcd_Wr_Data(0x35); 
    Drv_Lcd_Wr_Cmd(0xc0);  
	Drv_Lcd_Wr_Data(0x2c); 
    Drv_Lcd_Wr_Cmd(0xc2);  
	Drv_Lcd_Wr_Data(0x01); 
    Drv_Lcd_Wr_Cmd(0xc3);  
	Drv_Lcd_Wr_Data(0x0b); 
    Drv_Lcd_Wr_Cmd(0xc4);  
	Drv_Lcd_Wr_Data(0x20); 
    Drv_Lcd_Wr_Cmd(0xc6);  
	Drv_Lcd_Wr_Data(0x0f); 
    Drv_Lcd_Wr_Cmd(0xd0);  
	Drv_Lcd_Wr_Data(0xa4); 
	Drv_Lcd_Wr_Data(0xa1); 
    
    Drv_Lcd_Wr_Cmd(0xe0); 
    Drv_Lcd_Wr_Data(0xd0); 
    Drv_Lcd_Wr_Data(0x00); 
    Drv_Lcd_Wr_Data(0x02); 
    Drv_Lcd_Wr_Data(0x07); 
    Drv_Lcd_Wr_Data(0x0b); 
    Drv_Lcd_Wr_Data(0x1a); 
    Drv_Lcd_Wr_Data(0x31); 
    Drv_Lcd_Wr_Data(0x54); 
    Drv_Lcd_Wr_Data(0x40); 
    Drv_Lcd_Wr_Data(0x29); 
    Drv_Lcd_Wr_Data(0x12); 
    Drv_Lcd_Wr_Data(0x12); 
    Drv_Lcd_Wr_Data(0x12); 
    Drv_Lcd_Wr_Data(0x17); 
    Drv_Lcd_Wr_Cmd(0xe1); 
    Drv_Lcd_Wr_Data(0xd0); 
    Drv_Lcd_Wr_Data(0x00); 
    Drv_Lcd_Wr_Data(0x02); 
    Drv_Lcd_Wr_Data(0x07); 
    Drv_Lcd_Wr_Data(0x05); 
    Drv_Lcd_Wr_Data(0x25); 
    Drv_Lcd_Wr_Data(0x2d); 
    Drv_Lcd_Wr_Data(0x44); 
    Drv_Lcd_Wr_Data(0x45); 
    Drv_Lcd_Wr_Data(0x1c); 
    Drv_Lcd_Wr_Data(0x18); 
    Drv_Lcd_Wr_Data(0x16); 
    Drv_Lcd_Wr_Data(0x1c); 
    Drv_Lcd_Wr_Data(0x1d); 
    Drv_Lcd_Wr_Cmd(0x29); 

    BACKLIGHT_ON();
}

void Drv_Lcd_Clr(uint16_t color, lcd_isr_callback_t callback )
{
    Drv_Lcd_Set_Position(0, 0, LCD_W-1,LCD_H-1);

    Hal_Lcd_Set_BgColor(color, callback);
}

void Drv_Lcd_Gif(uint8_t picIndex, lcd_isr_callback_t callback )
{
    Drv_Lcd_Set_Position(0, 0, LCD_W-1,LCD_H-1);
    
    Hal_Lcd_Show_Picture(picIndex, callback );
}

void Drv_Lcd_Set_Position(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY )
{
	Drv_Lcd_Wr_Cmd(0x2A);
	Drv_Lcd_Wr_Data(startX>>8);
	Drv_Lcd_Wr_Data(startX&0xff);
	Drv_Lcd_Wr_Data(endX>>8);
	Drv_Lcd_Wr_Data(endX&0xff);
    
	Drv_Lcd_Wr_Cmd(0x2B);
	Drv_Lcd_Wr_Data(startY>>8);
	Drv_Lcd_Wr_Data(startY&0xff);
	Drv_Lcd_Wr_Data(endY>>8);
	Drv_Lcd_Wr_Data(endY&0xff);
}

void Drv_Lcd_Wr_Cmd(uint8_t reg )
{
    LCD_CS_LOW();
	LCD_DC_LOW();
	
	Write_LBDATAL(reg);

	LCD_CS_HIGH();
}

void Drv_Lcd_Wr_Data(uint8_t dat )
{
    LCD_CS_LOW();
	LCD_DC_HIGH();
	
	Write_LBDATAL(dat);

	LCD_CS_HIGH();
}

void Drv_Lcd_Delay_US(uint32_t us )
{
    while(--us);
}
