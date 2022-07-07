/********************************************************
* @file       drv_timer.c
* @author     szhj13
* @version    V1.0
* @date       2021-08-12
* @brief      the entry of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_timer.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void Drv_Timer_IRQHandler(void );
/* Private variables ------------------------------------*/
timer_ctrl_block_t timerList[TIMER_MAX_NUM];

static void test(void *arg )
{
    if((uint8_t)arg == 0xff)
    {
        PORT_ToggleBit(PORTD, PIN10);
    }
}

void Drv_Timer_Init(void )
{
    uint8_t i;

    for(i=0;i<TIMER_MAX_NUM;i++)
    {
        timerList[i].handler = NULL;
        timerList[i].arg = NULL;
        timerList[i].ticks = 0;
        timerList[i].period = 0;
        timerList[i].isRegist = 0;
    }

    Hal_Timer_Init();

    Hal_Timer_Regist_IRQHandler_Callback(Drv_Timer_IRQHandler);

    PORT_Init(PORTD, PIN10, OUTPUT);

    Drv_Timer_Reigst_Period(test, 0, 200, (void *)255);
}

uint8_t Drv_Timer_Regist(void (*handler)(void *arg), uint16_t ticks, uint16_t period, void *arg )
{
    uint8_t i;

    for(i=0;i<TIMER_MAX_NUM;i++)
    {
        if(!timerList[i].isRegist)
        {
            timerList[i].handler = handler;
            timerList[i].arg = arg;
            timerList[i].ticks = ticks;
            timerList[i].period = period;
            timerList[i].isRegist = 1;

            break;
        }
    }

    return i;
}

uint8_t Drv_Timer_Regist_Oneshot(void (*handler)(void *arg), uint16_t ticks, void *arg )
{
    return Drv_Timer_Regist(handler, ticks, 0, arg);
}

uint8_t Drv_Timer_Reigst_Period(void (*handler)(void *arg), uint16_t ticks, uint16_t period, void *arg )
{
    return Drv_Timer_Regist(handler, ticks, period, arg);
}

void Drv_Timer_Delete(uint8_t id )
{
    if(id >= TIMER_MAX_NUM)
    {
        return ;
    }

    timerList[id].handler = NULL;
    timerList[id].arg = NULL;
    timerList[id].ticks = 0;
    timerList[id].period = 0;
    timerList[id].isRegist = 0;    
}

static void Drv_Timer_IRQHandler(void )
{
    uint8_t id;

    for(id=0;id<TIMER_MAX_NUM;id++)
    {
        if(timerList[id].ticks > 0)
        {
            timerList[id].ticks--;
        }

        if(timerList[id].ticks == 0)
        {
            if(timerList[id].handler != NULL)
            {
                timerList[id].handler(timerList[id].arg);
            }

            if(timerList[id].period)
            {
                timerList[id].ticks = timerList[id].period;
            }
        }
    }
}

