#ifndef _HAL_TIMER_H
#define _HAL_TIMER_H

#include "hal_bat32g157.h"

void Hal_Timer_Init(void );
void Hal_Timer_Regist_IRQHandler_Callback(IRQHandler_callback_t callback );
void Hal_Timer_IRQHandler(void );

#endif 

