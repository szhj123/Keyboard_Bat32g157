/********************************************************
* @file       main.c
* @author     szhj13
* @version    V1.0
* @date       2021-08-12
* @brief      the entry of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_task.h"
#include "drv_timer.h"
#include "drv_spi_flash.h"

#include "app_lcd.h"
#include "app_usb_keyboard.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void Clk_Init(void );
/* Private variables ------------------------------------*/
int main(void )
{
    Clk_Init();
    
	Drv_Task_Init();

    Drv_Timer_Init();

    Drv_Spi_Flash_Init();

    App_Lcd_Init();

    App_Usb_Keyboard_Init();

    while(1)
    {
        Drv_Task_Scheduler();

        App_Lcd_Handler();
    }
}

void Clk_Init(void )
{
    uint32_t waitCnt;
    
    //HOCO = 32MHz / fIH = 8MHz, UPLL = 48MHz, fclk = 64MHz
    
    CLK_Fclk_Select(MAINCLK_FIH);
    CLK_PLL_Setting(PLL_SR_fIH,PLL_DIV_2,PLL_MUL_16);
    CLK_UPLL_Setting(PLL_SR_fIH,PLL_DIV_2,PLL_MUL_12);
    CLK_PLL_Start();
    waitCnt = 10000;
    while(waitCnt--);
    CLK_UPLL_Start();
    waitCnt = 10000;
    while(waitCnt--);
    CLK_Fclk_Select(MAINCLK_FPLL);

    SystemCoreClock = 64000000;
}


void usb_cpu_delay_1us (uint16_t time)
{
    uint16_t sf_cnt;
    sf_cnt = time * 20;

    while(sf_cnt)
    {
        sf_cnt --;
    }
}

void usb_cpu_delay_xms(uint16_t n)
{
    uint16_t i;

    for(i=0;i<n;i++)
    {
        usb_cpu_delay_1us(1000);
    }
}


