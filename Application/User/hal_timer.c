/********************************************************
* @file       hal_timer.c
* @author     szhj13
* @version    V1.0
* @date       2021-08-12
* @brief      the entry of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_timer.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void Timer4_Channel0_Init(void );
/* Private variables ------------------------------------*/
IRQHandler_callback_t IQRQHandler_Timer_Callback = NULL;


void Hal_Timer_Init(void )
{
    Timer4_Channel0_Init();
}

static void Timer4_Channel0_Init(void )
{
    //使能TM40外设时钟
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;
    //设置CKM0的时钟为Fclk=64Mhz
    TM40->TPS0  = TM40->TPS0 & ~TM40_TPS0_PRS00_Msk;
    //选择TM4通道0的时钟来自CKM0 
    TM40->TMR00 = TM40->TMR00 & ~TM40_TMR00_CKS_Msk;
    //设置TM4通道0为间隔定时器模式
    TM40->TMR00 = TM40->TMR00 & ~TM40_TMR00_MD_Msk;
    //设置定时器数据寄存器， 定时1ms
    TM40->TDR00 = SystemCoreClock / 1000;

    INTC_ClearPendingIRQ(TM00_IRQn);
    NVIC_ClearPendingIRQ(TM00_IRQn);

    INTC_EnableIRQ(TM00_IRQn);

    TM40->TS0 |= TM40_TS0_TS00_Msk;
}

void Hal_Timer_Regist_IRQHandler_Callback(IRQHandler_callback_t callback )
{
    IQRQHandler_Timer_Callback = callback;
}

void Hal_Timer_IRQHandler(void )
{
    if(IQRQHandler_Timer_Callback != NULL)
    {
        IQRQHandler_Timer_Callback();
    }
}

