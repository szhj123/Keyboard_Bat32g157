/********************************************************
* @file       drv_task.c
* @author     szhj13
* @version    V1.0
* @date       2021-08-12
* @brief      the entry of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_task.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
IRQHandler_callback_t IQRHandler_Task_Callback = NULL;

void Hal_Task_Init(void )
{
    SysTick_Config(SystemCoreClock/1000);    
}

void Hal_Task_Regist_IRQHandler_Callback(IRQHandler_callback_t callback )
{
    IQRHandler_Task_Callback = callback;
}

void Hal_Task_IRQHandler(void )
{
    if(IQRHandler_Task_Callback != NULL)
    {
        IQRHandler_Task_Callback();
    }
}

