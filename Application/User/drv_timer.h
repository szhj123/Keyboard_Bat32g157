#ifndef _DRV_TIMER_H
#define _DRV_TIMER_H

#include "hal_timer.h"

#define TIMER_MAX_NUM                16
#define TIMER_NUL                    (TIMER_MAX_NUM)

typedef struct _timer_ctrl_block_t
{
    void (*handler)(void *arg);
    void *arg;
    uint16_t ticks;
    uint16_t period;
    uint8_t  isRegist;
}timer_ctrl_block_t;

void Drv_Timer_Init(void );
uint8_t Drv_Timer_Regist_Oneshot(void (*handler)(void *arg), uint16_t ticks, void *arg );
uint8_t Drv_Timer_Reigst_Period(void (*handler)(void *arg), uint16_t ticks, uint16_t period, void *arg );
void Drv_Timer_Delete(uint8_t id );


#endif 
