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
#include "drv_key.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void Drv_Rgb_Send_Data(uint16_t );
/* Private variables ------------------------------------*/

void Drv_Rgb_Init(void )
{
    uint16_t buf[] = {0xffff, 0xffff, 0xffff};
    
    Hal_Rgb_Init();

    Hal_Rgb_Gclk_Init();

    Drv_Key_Col_Set_All_Pin_High();    

    while(1)
    Drv_Rgb_Send_Data(0x5555);
    
}

void Drv_Rgb_Delay(void )
{
    uint8_t cnt = 1;
    while(cnt--);
}

void Drv_Rgb_Send_Data(uint16_t dat )
{
    uint8_t i;
    
    LE_L();

    for(i=0;i<15;i++)
    {
        DCLK_L();

        if(dat & 0x8000)
            SIN_H();
        else
            SIN_L();
        
        DCLK_H();

        dat <<= 1;
    }

    DCLK_L();

    LE_H();

    if(dat & 0x8000)
        SIN_H();
    else
        SIN_L();

    DCLK_H();
    
    LE_L();

    DCLK_L();
    
}



