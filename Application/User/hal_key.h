#ifndef _HAL_KEY_H
#define _HAL_KEY_H

#include "hal_bat32g157.h"

void Hal_Key_Init(void );
void Hal_Key_Set_Pin_High(PORT_TypeDef port, PIN_TypeDef pin );
void Hal_Key_Set_Pin_Low(PORT_TypeDef port, PIN_TypeDef pin );
uint8_t Hal_Key_Get_Pin(PORT_TypeDef port, PIN_TypeDef pin );


#endif 

