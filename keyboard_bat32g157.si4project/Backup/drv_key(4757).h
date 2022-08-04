#ifndef _DRV_KEY_H
#define _DRV_KEY_H

#include "hal_key.h"

#define KEY_MAX_NUM                0x08

typedef enum
{
    KEY_STATE_NULL = 0,
    KEY_SHORT_PRESS,
    KEY_LONG_PRESS,
    KEY_CONT_PRESS,
    KEY_RELEASE
}key_state_t;

typedef struct 
{
    key_state_t state;
    uint8_t buf[KEY_MAX_NUM];
}key_t;

typedef struct
{
    PORT_TypeDef port;
    PIN_TypeDef  pin;
}keyPin_typedef;

typedef enum
{
    KEY_DET_NULL = 0,
    KEY_DET_DEBOUNCE,
    KEY_DET_SHORT_PRESS,
    KEY_DET_LONG_PRESS,
    KEY_DET_CONT_PRESS,
    KEY_DET_RELEASE
}key_det_t;

typedef struct _key_detect_para_t
{
    key_det_t keyDetState;
    
    uint8_t keyNewBuf[KEY_MAX_NUM];
    uint8_t keyOldBuf[KEY_MAX_NUM];
    uint8_t keyNewCnt;
    uint8_t keyOldCnt;

    uint16_t keyDelayCnt;
    uint8_t keyNewAddFlag;
    uint8_t keyPressFlag;    
}key_detect_para_t;

void Drv_Key_Init(void );
void Drv_Key_Scan(void );
void Drv_Key_Get_Val(key_t *pKey );
void Drv_Key_Col_Set_All_Pin_High(void );
void Drv_Key_Col_Set_All_Pin_Low(void );
void Drv_Key_Col_Set_Pin_Low(uint8_t colNum );
void Drv_Key_Col_Set_Pin_High(uint8_t colNum );

#endif 

