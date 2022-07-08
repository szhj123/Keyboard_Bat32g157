/********************************************************
* @file       app_lcd.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_timer.h"
#include "drv_spi_flash.h"
//#include "pic.h"
#include "app_lcd.h"
/* Private typedef --------------------------------------*/

/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Lcd_Clr_Callback(void );

/* Private variables ------------------------------------*/
lcd_ctrl_blokc_t lcdInfo;
func_state_t     funcState;


void App_Lcd_Init(void )
{
    Drv_Lcd_Init();    

    //App_Lcd_Gif_Set();
    App_Lcd_Clr_Set(BLUE);
}

void App_Lcd_Handler(void )
{
    if(lcdInfo.handler != NULL)
    {
        lcdInfo.handler();
    }
}

void App_Lcd_Clr_Set(uint16_t color )
{
    lcdInfo.bgColor = color;
    lcdInfo.funcState = FUNC_ENTRY;
    lcdInfo.handler = App_Lcd_Clr_Handler;
    lcdInfo.lcdWrEndFlag = 0;
}

void App_Lcd_Clr_Handler(void )
{
    switch(lcdInfo.funcState)
    {
        case FUNC_ENTRY:
        {
            Drv_Lcd_Clr(lcdInfo.bgColor, App_Lcd_Clr_Callback);
            lcdInfo.funcState = FUNC_EXIT;
            break;
        }
        case FUNC_EXIT:
        {
            if(lcdInfo.lcdWrEndFlag)
            {
                lcdInfo.lcdWrEndFlag = 0;

                App_Lcd_Normal_Set();
            }
            break;
        }
        default: break;
    }
}

void App_Lcd_Gif_Set(void )
{
    lcdInfo.funcState = FUNC_ENTRY;
    lcdInfo.lcdPicIndex = 0;
    lcdInfo.lcdPicNum = 37;
    lcdInfo.handler = App_Lcd_Gif_Handler;
}

void App_Lcd_Gif_Handler(void )
{
    switch(lcdInfo.funcState)
    {
        case FUNC_ENTRY:
        {
            Drv_Lcd_Gif(lcdInfo.lcdPicIndex, App_Lcd_Clr_Callback);
            lcdInfo.funcState = FUNC_PROCESS;
            break;
        }
        case FUNC_PROCESS:
        {
            if(lcdInfo.lcdWrEndFlag)
            {
                lcdInfo.lcdWrEndFlag = 0;
                
                lcdInfo.lcdPicIndex++;

                if(lcdInfo.lcdPicIndex < lcdInfo.lcdPicNum)
                {
                    Drv_Lcd_Gif(lcdInfo.lcdPicIndex, App_Lcd_Clr_Callback);
                }
                else
                {
                    lcdInfo.lcdPicIndex = 0;
                    lcdInfo.funcState = FUNC_ENTRY;
                }
                
            }
            break;
        }
        case FUNC_EXIT:
        {
            break;
        }
        default: break;
    }
}

void App_Lcd_Normal_Set(void )
{
    lcdInfo.funcState = FUNC_ENTRY;
    lcdInfo.handler = App_Lcd_Normal_Handler;
    lcdInfo.lcdWrEndFlag = 0;
}

void App_Lcd_Normal_Handler(void )
{
    switch(lcdInfo.funcState)
    {
        case FUNC_ENTRY:
        {
            break;
        }
        case FUNC_PROCESS:
        {
            break;
        }
        case FUNC_EXIT:
        {
            break;
        }
        default: break;
    }
}

void App_Lcd_Save_Picture(uint16_t picIndex )
{
    uint32_t flashAddr = picIndex * PIC_MAX_SIZE;

    App_Lcd_Erase_Picture(picIndex);
        
    //Drv_Spi_Write(flashAddr, (uint8_t *)gImage_pic1, sizeof(gImage_pic1));
}

void App_Lcd_Erase_Picture(uint16_t picIndex )
{
    uint8_t i;
    uint32_t flashAddr = picIndex * PIC_MAX_SIZE;
    
    Drv_Spi_64K_Block_Erase(flashAddr);
    
    flashAddr += ERASE_64K_BLOCK_SIZE;
    
    Drv_Spi_64K_Block_Erase(flashAddr);
    
    flashAddr += ERASE_64K_BLOCK_SIZE;

    Drv_Spi_32K_Block_Erase(flashAddr);
}

static void App_Lcd_Clr_Callback(void )
{
    lcdInfo.lcdWrEndFlag = 1;
}


