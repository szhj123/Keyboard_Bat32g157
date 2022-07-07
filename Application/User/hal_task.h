#ifndef _HAL_TASK_H
#define _HAL_TASK_H

#include "hal_bat32g157.h"

void Hal_Task_Init(void );
void Hal_Task_Regist_IRQHandler_Callback(IRQHandler_callback_t callback );
void Hal_Task_IRQHandler(void );


#endif 

