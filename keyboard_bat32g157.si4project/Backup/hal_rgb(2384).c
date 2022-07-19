/********************************************************
* @file       hal_rgb.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_rgb.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Hal_Rgb_Init(void )
{
    Hal_Key_Init();
}

void Hal_Rgb_Spi_Init(void )
{        
    CGC->PER1 |= 0x40;

    SPIHS0->SPIC0 = _0006_SPI_SCK_fCLK_6 | (SPI_MODE_0 & 0x03) << 3;    

    SPIHS0->SPIM0 = _0040_SPI_RECEPTION_TRANSMISSION | _0000_SPI_MSB | _0000_SPI_TRANSFER_END | _0004_SPI_LENGTH_16;

    SCK0_PORT_SETTING();
    
    MOSI0_PORT_SETTING();
}

void Hal_Rgb_Send_With_Loop(uint16_t *buf, uint16_t length )
{
    uint16_t i;

    SPIHS0->SPIM0 |= _0080_SPI_START_TRG_ON; 

    for(i=0;i<length;i++)
    {
        SPIHS0->SDRO0 = buf[i]; 

        while(SPIHS0->SPIS0 & _0001_SPI_UNDER_EXECUTE) 
        {
            ;
        }
    }
}

