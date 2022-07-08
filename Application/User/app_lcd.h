#ifndef _APP_LCD_H
#define _APP_LCD_H

#include "drv_lcd.h"

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x1F00  
#define BRED             0X1FF8
#define GRED 			 0XE0FF
#define GBLUE			 0XFF07
#define RED           	 0x00F8
#define MAGENTA       	 0x1FF8
#define GREEN         	 0xE007
#define CYAN          	 0xFF7F
#define YELLOW        	 0xE0FF
#define BROWN 			 0X40BC
#define BRRED 			 0X07FC 
#define GRAY  			 0X3084



typedef enum
{
    FUNC_ENTRY = 0,
    FUNC_PROCESS,
    FUNC_EXIT
}func_state_t;

typedef struct _lcd_ctrl_blokc_t
{
    void          (*handler)(void );
    func_state_t  funcState;
    uint16_t      bgColor;
    uint8_t       lcdPicNum;
    uint8_t       lcdPicIndex;
    uint8_t       lcdWrEndFlag;
}lcd_ctrl_blokc_t;

void App_Lcd_Init(void );
void App_Lcd_Handler(void );
void App_Lcd_Clr_Set(uint16_t color );
void App_Lcd_Clr_Handler(void );
void App_Lcd_Gif_Set(void );
void App_Lcd_Gif_Handler(void );
void App_Lcd_Normal_Set(void );
void App_Lcd_Normal_Handler(void );
void App_Lcd_Erase_Picture(uint16_t picIndex );
void App_Lcd_Save_Picture(uint16_t picIndex );

#endif 

