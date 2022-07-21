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
    PORT_Init(PORTB, PIN5, OUTPUT);
    PORT_Init(PORTB, PIN4, OUTPUT);
    PORT_Init(PORTB, PIN2, OUTPUT);
    PORT_Init(PORTB, PIN1, OUTPUT);
    PORT_Init(PORTH, PIN3, OUTPUT);
    PORT_Init(PORTH, PIN4, OUTPUT);
    PORT_Init(PORTB, PIN0, OUTPUT);
    PORT_Init(PORTD, PIN11, OUTPUT);
    PORT_Init(PORTD, PIN10, OUTPUT);
    PORT_Init(PORTD, PIN9, OUTPUT);
    PORT_Init(PORTD, PIN8, OUTPUT);
    PORT_Init(PORTD, PIN7, OUTPUT);
    PORT_Init(PORTD, PIN6, OUTPUT);
    PORT_Init(PORTD, PIN5, OUTPUT);
    PORT_Init(PORTD, PIN4, OUTPUT);
    PORT_Init(PORTD, PIN3, OUTPUT);
    PORT_Init(PORTD, PIN2, OUTPUT);
    PORT_Init(PORTD, PIN15, OUTPUT);
    PORT_Init(PORTD, PIN14, OUTPUT);
    PORT_Init(PORTD, PIN13, OUTPUT);
    PORT_Init(PORTD, PIN12, OUTPUT);
    
    PORT_Init(PORTC, PIN4, OUTPUT);
    PORT_Init(PORTC, PIN3, OUTPUT);
    PORT_Init(PORTA, PIN4, OUTPUT);
    PORT_Init(PORTA, PIN5, OUTPUT);
}

void Hal_Rgb_Gclk_Init(void )
{
    CGC->PER0 |= CGC_PER0_TM81EN_Msk;    /* enables input clock supply */
    TM81->TPS1 = _0000_TM8_CKM3_fCLK_8 | _0000_TM8_CKM2_fCLK_1 | _0000_TM8_CKM1_fCLK_0 | _0000_TM8_CKM0_fCLK_0; 

    /* stop specify channel */
    TM81->TT1 |= TM8_CHANNEL_0; 

    /* clear interrupt flag */
    INTC_ClearPendingIRQ(TM10_IRQn);
    NVIC_ClearPendingIRQ(TM10_IRQn);
    /* Channel 0 is used as interval timer */
    TM81->TMR10 = _0000_TM8_CLOCK_SELECT_CKM0 | _0000_TM8_CLOCK_MODE_CKS | _0000_TM8_TRIGGER_SOFTWARE |
                  _0000_TM8_MODE_INTERVAL_TIMER | _0000_TM8_START_INT_UNUSED;
    TM81->TDR10 = 5 - 1;
    TM81->TO1  &= ~_0001_TM8_CH0_OUTPUT_VALUE_1;
    TM81->TOE1 |=  _0001_TM8_CH0_OUTPUT_ENABLE;
    
    PORT->PA05CFG = PTCFG_TO10;  /* allocate TO10 to PA05 */ \
    PORT->PCLRA =  (1 << 5);    /* PA05 output low level */ \
    PORT->PMA  &= ~(1 << 5);    /* PA05 is used as TO10 output */ \
    PORT->POMA &= ~(1 << 5);    /* PA05 is normal output mode */ \
    PORT->PMCA &= ~(1 << 5);    /* PA05 digital function */ \
        
    //INTC_EnableIRQ(TM10_IRQn);
    /* Start specify channel */
    TM81->TS1 |= TM8_CHANNEL_0;
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

    PORT_SetBit(PORTA, PIN4);
}

