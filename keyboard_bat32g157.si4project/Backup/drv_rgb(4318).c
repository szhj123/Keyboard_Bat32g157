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
#define CMD_DATA_LOCK                 1
#define CMD_TOTAL_LOCK                3
#define CMD_READ_STATE_REG            5
#define CMD_WRITE_STATE_REG           11
#define CMD_RESET_PWM_COUNTER         13
#define CMD_ENABLE_WRITE_REG          14

/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void Drv_Rgb_Write_State_Reg(void );
void Drv_Rgb_Send_Data(uint16_t, uint8_t );
/* Private variables ------------------------------------*/

void Drv_Rgb_Init(void )
{
    uint8_t i;
    uint16_t buf[] = {0xffff, 0xffff, 0xffff};
    
    Hal_Rgb_Init();

    Hal_Rgb_Gclk_Init();

    Drv_Rgb_Write_State_Reg();
    
    Drv_Rgb_All_Turn_Off();

    Drv_Key_Col_Set_Pin_High(15);    

    Drv_Rgb_All_Turn_Off();

    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    
    //Drv_Rgb_Send_Data(0, CMD_TOTAL_LOCK);
    
    Drv_Rgb_Send_Data(255, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    
    #if 0
    Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
       
    for(i=0;i<5;i++)
    {
        Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
        Drv_Rgb_Send_Data(255, CMD_DATA_LOCK);
        Drv_Rgb_Send_Data(0, CMD_DATA_LOCK);
    } 
    #endif 

    Drv_Rgb_Send_Data(0, CMD_TOTAL_LOCK);
    
}

void Drv_Rgb_Write_State_Reg(void )
{
    uint16_t config = 0x82b0;
    
    Drv_Rgb_Send_Data(config, CMD_ENABLE_WRITE_REG);

    
    Drv_Rgb_Send_Data(config, CMD_WRITE_STATE_REG);

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



