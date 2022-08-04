/********************************************************
* @file       drv_rgb.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_rgb.h"
#include "drv_timer.h"
#include "drv_key.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
#define CMD_DATA_LOCK                 1
#define CMD_TOTAL_LOCK                3
#define CMD_READ_STATE_REG            5
#define CMD_WRITE_STATE_REG           11
#define CMD_RESET_PWM_COUNTER         13
#define CMD_ENABLE_WRITE_REG          15

/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void Drv_Rgb_Write_State_Reg(void );
void Drv_Rgb_Send_Data(uint16_t, uint8_t );
static void Drv_Rgb_Show_Horse_Single_Color_Callback(void *arg );
/* Private variables ------------------------------------*/
static rgb_color_t rowColorBuf[6];
static uint8_t rgbTimerId = TIMER_NUL;
static rgb_horse_t rgbHorse;

void Drv_Rgb_Init(void )
{
    Hal_Rgb_Init();

    Hal_Rgb_Gclk_Init();

    Drv_Rgb_Write_State_Reg();
    
    Drv_Rgb_All_Turn_Off();

    Drv_Key_Col_Set_Pin_High(15);    

    rgb_color_t rgbColor;

    rgbColor.red = 255;

    Drv_Rgb_Show_Horse_Single_Color(3, 50, rgbColor);
}

void Drv_Rgb_Write_State_Reg(void )
{
    uint16_t config = 0x0000;
    
    Drv_Rgb_Send_Data(config, CMD_ENABLE_WRITE_REG);

    
    Drv_Rgb_Send_Data(config, CMD_WRITE_STATE_REG);

}

void Drv_Rgb_Send_Data(uint16_t dat,uint8_t mode )
{
    uint8_t i;

    dat = dat * 255;
    
    LE_L();

    for(i=0;i<16;i++)
    {
        DCLK_L();

        if(dat & 0x8000)
            SIN_H();
        else
            SIN_L();
        
        DCLK_H();

        dat <<= 1;

        if(i > (15 - mode))
        {
            LE_H();
        }
    }

    DCLK_L();

    LE_L();
}

void Drv_Rgb_All_Turn_Off(void )
{
    uint8_t i;
    for(i=0;i<32;i++)
    {
        Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    }

    
    Drv_Rgb_Send_Data(0, CMD_TOTAL_LOCK);
}


void Drv_Rgb_Set_Row_Data(uint8_t *buf, uint8_t length )
{
    uint8_t i;

    for(i=0;i<16;i++)
    {
        Drv_Rgb_Send_Data(buf[15-i], CMD_DATA_LOCK);
    }

    Drv_Rgb_Send_Data(0, CMD_TOTAL_LOCK);
}

void Drv_Rgb_Show_Horse_Single_Color(uint8_t rgbNum, uint16_t speed, rgb_color_t color )
{
    if(rgbNum <= 0)
    {
        return ;
    }
    
    rgbHorse.rgbCol = 0;
    rgbHorse.rgbRow = 0;
    rgbHorse.rgbNum = rgbNum;
    rgbHorse.rgbColor = color;
    rgbHorse.rowSwitchFlag = 0;
    
    Drv_Timer_Delete(rgbTimerId);

    rgbTimerId = Drv_Timer_Regist_Period(Drv_Rgb_Show_Horse_Single_Color_Callback, 0, speed, NULL);
}

static void Drv_Rgb_Show_Horse_Single_Color_Callback(void *arg )
{
    uint8_t i;

    rgb_color_t rgbOffColor;
    
    rgbOffColor.red = 0;
    rgbOffColor.green = 0;
    rgbOffColor.blue = 0;

    Drv_Key_Col_Set_All_Pin_Low();

    rowColorBuf[rgbHorse.rgbRow] = rgbHorse.rgbColor;

    if(!rgbHorse.rowSwitchFlag)
    {
        if(rgbHorse.rgbCol < rgbHorse.rgbNum)
        {
            Drv_Key_Col_Set_Pin_High(rgbHorse.rgbCol);
        }
        else
        {
            for(i=0;i<rgbHorse.rgbNum;i++)
            {
                Drv_Key_Col_Set_Pin_High(rgbHorse.rgbCol-i);
            }
        }

        Drv_Rgb_Set_Row_Data((uint8_t *)rowColorBuf, 16);

        rgbHorse.rgbCol++;

        if(rgbHorse.rgbCol >= KEY_COL_MAX_NUM)
        {
            rowColorBuf[rgbHorse.rgbRow] = rgbOffColor;
                
            rgbHorse.rgbCol = 0;
            
            rgbHorse.rgbRow++;

            if(rgbHorse.rgbRow >= KEY_ROW_MAX_NUM)
            {
                rgbHorse.rgbRow = 0;
            }

            rgbHorse.rowSwitchFlag = 1;
        }
    }
    else
    {
        if(rgbHorse.rgbCol < rgbHorse.rgbNum)
        {
            Drv_Key_Col_Set_Pin_High(KEY_COL_MAX_NUM -rgbHorse.rgbCol - 1);
        }
        else
        {
            for(i=0;i<rgbHorse.rgbNum;i++)
            {
                Drv_Key_Col_Set_Pin_High(KEY_COL_MAX_NUM -rgbHorse.rgbCol- i);
            }
        }

        Drv_Rgb_Set_Row_Data((uint8_t *)rowColorBuf, 16);

        rgbHorse.rgbCol++;

        if(rgbHorse.rgbCol >= KEY_COL_MAX_NUM)
        {
            rowColorBuf[rgbHorse.rgbRow] = rgbOffColor;
            
            rgbHorse.rgbCol = 0;
            
            rgbHorse.rgbRow++;
            
            if(rgbHorse.rgbRow >= KEY_ROW_MAX_NUM)
            {
                rgbHorse.rgbRow = 0;
            }

            rgbHorse.rowSwitchFlag = 0;
        }
    }
    
    #if 0
    switch(rgbHorse.rgbRow)
    {
        case 0:
        {
            if(rgbHorse.rgbCol < rgbHorse.rgbNum)
            {
                Drv_Key_Col_Set_Pin_High(rgbHorse.rgbCol);
            }
            else
            {
                for(i=0;i<rgbHorse.rgbNum;i++)
                {
                    Drv_Key_Col_Set_Pin_High(rgbHorse.rgbCol-i);
                }
            }

            Drv_Rgb_Set_Row_Data((uint8_t *)rowColorBuf, 16);

            rgbHorse.rgbCol++;

            if(rgbHorse.rgbCol >= KEY_COL_MAX_NUM)
            {
                rowColorBuf[rgbHorse.rgbRow] = rgbOffColor;
                    
                rgbHorse.rgbCol = 0;
                rgbHorse.rgbRow  = 1;
            }
            break;
        }
        case 1:
        {
            if(rgbHorse.rgbCol < rgbHorse.rgbNum)
            {
                Drv_Key_Col_Set_Pin_High(KEY_COL_MAX_NUM -rgbHorse.rgbCol - 1);
            }
            else
            {
                for(i=0;i<rgbHorse.rgbNum;i++)
                {
                    Drv_Key_Col_Set_Pin_High(KEY_COL_MAX_NUM -rgbHorse.rgbCol- i);
                }
            }

            Drv_Rgb_Set_Row_Data((uint8_t *)rowColorBuf, 16);

            rgbHorse.rgbCol++;

            if(rgbHorse.rgbCol >= KEY_COL_MAX_NUM)
            {
                rowColorBuf[rgbHorse.rgbRow] = rgbOffColor;
                
                rgbHorse.rgbCol = 0;
                rgbHorse.rgbRow  = 2;
            }
            break;
        }
        case 2:
        {
            
        }
        default: break;
    }
    #endif 
}

