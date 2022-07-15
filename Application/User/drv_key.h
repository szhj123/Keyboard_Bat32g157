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
    KEY_SHORT_PRESS,
    KEY_LONG_PRESS,
    KEY_CONT_PRESS,
    KEY_RELEASE
}key_state_t;

typedef struct _key_queue_t
{
    uint8_t buf[32];
    uint8_t front;
    uint8_t rear;
}key_queue_t;

void Drv_Key_Init(void );
void Drv_Key_Detect(void );
void Drv_Key_Get_keyTableMap_Val(void );

#endif 

