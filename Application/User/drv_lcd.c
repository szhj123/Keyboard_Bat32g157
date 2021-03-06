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
void Drv_Lcd_Read_Id(void );
/* Private variables ------------------------------------*/

void Drv_Lcd_Init(void )
{
    Hal_Lcd_Init();

    LCD_RST_HIGH();
    Drv_Lcd_Delay_US(1000*35);
	LCD_RST_LOW();
	Drv_Lcd_Delay_US(10000*35);
	LCD_RST_HIGH();
	Drv_Lcd_Delay_US(120000*35);

    Drv_Lcd_Wr_Cmd(0x11);  
    Drv_Lcd_Delay_US(120000*35);
    
    Drv_Lcd_Wr_Cmd(0x36);//	
	//Drv_Lcd_Wr_Data(0x20);
	Drv_Lcd_Wr_Data(0x00);

	Drv_Lcd_Wr_Cmd(0x3A);			
	Drv_Lcd_Wr_Data(0x05);

	Drv_Lcd_Wr_Cmd(0xB2);			
	Drv_Lcd_Wr_Data(0x0C);
	Drv_Lcd_Wr_Data(0x0C); 
	Drv_Lcd_Wr_Data(0x00); 
	Drv_Lcd_Wr_Data(0x33); 
	Drv_Lcd_Wr_Data(0x33); 			

	Drv_Lcd_Wr_Cmd(0xB7);			
	Drv_Lcd_Wr_Data(0x35);

	Drv_Lcd_Wr_Cmd(0xBB);			
	Drv_Lcd_Wr_Data(0x29); //32 Vcom=1.35V
															
	Drv_Lcd_Wr_Cmd(0xC2);			
	Drv_Lcd_Wr_Data(0x01);

	Drv_Lcd_Wr_Cmd(0xC3);			
	Drv_Lcd_Wr_Data(0x19); //GVDD=4.8V 
															
	Drv_Lcd_Wr_Cmd(0xC4);  
	Drv_Lcd_Wr_Data(0x18); //VDV, 0x20:0v

	Drv_Lcd_Wr_Cmd(0xC5);
	Drv_Lcd_Wr_Data(0x1f);

	Drv_Lcd_Wr_Cmd(0xC6);			
	Drv_Lcd_Wr_Data(0x01); //0x0F:60Hz   0x03:99Hz       	

	Drv_Lcd_Wr_Cmd(0xD0);			
	Drv_Lcd_Wr_Data(0xA4);
	Drv_Lcd_Wr_Data(0xA1);	
		
	Drv_Lcd_Wr_Cmd(0xE0);     
	Drv_Lcd_Wr_Data(0xD0);   
	Drv_Lcd_Wr_Data(0x08);   
	Drv_Lcd_Wr_Data(0x0E);   
	Drv_Lcd_Wr_Data(0x09);   
	Drv_Lcd_Wr_Data(0x09);   
	Drv_Lcd_Wr_Data(0x05);   
	Drv_Lcd_Wr_Data(0x31);   
	Drv_Lcd_Wr_Data(0x33);   
	Drv_Lcd_Wr_Data(0x48);    
	Drv_Lcd_Wr_Data(0x17);   
	Drv_Lcd_Wr_Data(0x14);   
	Drv_Lcd_Wr_Data(0x15);   
	Drv_Lcd_Wr_Data(0x31);   
	Drv_Lcd_Wr_Data(0x34);   

	Drv_Lcd_Wr_Cmd(0xE1);     
	Drv_Lcd_Wr_Data(0xD0);   
	Drv_Lcd_Wr_Data(0x08);   
	Drv_Lcd_Wr_Data(0x0E);   
	Drv_Lcd_Wr_Data(0x09);   
	Drv_Lcd_Wr_Data(0x09);   
	Drv_Lcd_Wr_Data(0x15);   
	Drv_Lcd_Wr_Data(0x31);   
	Drv_Lcd_Wr_Data(0x33);   

	Drv_Lcd_Wr_Data(0x48);   
	Drv_Lcd_Wr_Data(0x17);   
	Drv_Lcd_Wr_Data(0x14);   
	Drv_Lcd_Wr_Data(0x15);   
	Drv_Lcd_Wr_Data(0x31);   
	Drv_Lcd_Wr_Data(0x34);

	Drv_Lcd_Wr_Cmd(0x21);
	Drv_Lcd_Wr_Cmd(0x29);

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

void Drv_Lcd_Read_Id(void )
{
    uint8_t buf[4] = {0};
    
    Drv_Lcd_Wr_Cmd(0x04);

    Drv_Lcd_Rd_Data(buf, 4);
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

void Drv_Lcd_Rd_Data(uint8_t *buf, uint8_t length )
{
    uint8_t i;
    
    LCD_CS_LOW();
	LCD_DC_HIGH();
    
    for(i=0;i<length;i++)
    {
        while(Read_LBCTL_BYF());
        buf[i] = LCDB->LBDATAL;
        while(Read_LBCTL_TPF());/* write LBDATAL */
    }
}

void Drv_Lcd_Delay_US(uint32_t us )
{
    while(--us);
}
