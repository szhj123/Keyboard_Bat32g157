#ifndef _DRV_KEY_H
#define _DRV_KEY_H

#include "hal_key.h"

typedef struct
{
    PORT_TypeDef port;
    PIN_TypeDef  pin;
}keyPin_typedef;

typedef enum
{
    KEY_COL_INIT = 0,
    KEY_ROW_INIT,
    KEY_DOWN
}key_state_t;

void Drv_Key_Init(void );
void Drv_Key_Detect(void );

#endif 

