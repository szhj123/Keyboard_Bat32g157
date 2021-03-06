/********************************************************
* @file       hal_interrupt.c
* @author     szhj13
* @version    V1.0
* @date       2021-08-12
* @brief      the entry of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_task.h"
#include "hal_timer.h"
#include "hal_spi_flash.h"
#include "hal_lcd.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void IRQ18_Handler(void) __attribute__((alias("tm40_channel0_interrupt")));
void IRQ12_Handler(void) __attribute__((alias("spi1_interrupt")));
void IRQ15_Handler(void) __attribute__((alias("lcdb_interrupt")));
/* Private variables ------------------------------------*/

void SysTick_Handler(void )
{
    Hal_Task_IRQHandler();
}

void tm40_channel0_interrupt(void )
{
    INTC_ClearPendingIRQ(TM00_IRQn);    /* clear INTTM00 interrupt flag */

    Hal_Timer_IRQHandler();
}

void spi1_interrupt(void)
{
    INTC_ClearPendingIRQ(SPI1_IRQn);

    Hal_Spi_Tx_Isr_Handler();

    Hal_Spi_Rx_Isr_Handler();

    Hal_Lcd_Gif_Isr_Handler();
}

void lcdb_interrupt(void )
{
    INTC_ClearPendingIRQ(LCDB_IRQn);     /* clear LCDB interrupt flag */

    Hal_Lcd_Clr_Isr_Handler();
}


