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
void Drv_Rgb_Send_Data(uint16_t, uint8_t );
/* Private variables ------------------------------------*/

void Drv_Rgb_Init(void )
{
    uint8_t i;
    uint16_t buf[] = {0xffff, 0xffff, 0xffff};
    
    Hal_Rgb_Init();

    Hal_Rgb_Gclk_Init();

    Drv_Key_Col_Set_Pin_High(15);    
    //Drv_Key_Col_Set_All_Pin_High();

    #if 0
    for(i=0;i<5;i++)
    {
        Drv_Rgb_Send_Data(0xffff, 15);
        Drv_Rgb_Send_Data(0, 15);
        Drv_Rgb_Send_Data(0, 15);
    } 
    Drv_Rgb_Send_Data(0x0000, 13);
    #endif 

    Drv_Rgb_Send_Data(0, 15); 
    
    for(i=0;i<5;i++)
    {
        Drv_Rgb_Send_Data(0, 15);
        Drv_Rgb_Send_Data(0, 15);
        Drv_Rgb_Send_Data(255, 15);
    } 

    Drv_Rgb_Send_Data(0, 13);   
}

void Drv_Rgb_Send_Data(uint16_t dat,uint8_t mode )
{
    uint8_t i;
    
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

        if(i == mode)
        {
            LE_H();
        }
    }

    DCLK_L();

    LE_L();
}



