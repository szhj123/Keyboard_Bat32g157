/********************************************************
* @file       drv_key.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_timer.h"
#include "drv_key.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
keyPin_typedef rowBuf[] =
{
    {
        .port = PORTA,
        .pin  = PIN0
    },
    {
        .port = PORTA,
        .pin  = PIN1
    },
    {
        .port = PORTA,
        .pin  = PIN3
    },
    {
        .port = PORTA,
        .pin  = PIN12
    },
    {
        .port = PORTA,
        .pin  = PIN13
    },
    {
        .port = PORTA,
        .pin  = PIN14
    }
};

keyPin_typedef colBuf[] = 
{
    {
        .port = PORTB,
        .pin  = PIN5
    },
    {
        .port = PORTB,
        .pin  = PIN4
    },
    {
        .port = PORTB,
        .pin  = PIN2
    },
    {
        .port = PORTB,
        .pin  = PIN1
    },
    {
        .port = PORTH,
        .pin  = PIN3
    },
    {
        .port = PORTH,
        .pin  = PIN4
    },
    {
        .port = PORTB,
        .pin  = PIN0
    },
    {
        .port = PORTD,
        .pin  = PIN11
    },
    {
        .port = PORTD,
        .pin  = PIN10
    },
    {
        .port = PORTD,
        .pin  = PIN9
    },
    {
        .port = PORTD,
        .pin  = PIN8
    },
    {
        .port = PORTD,
        .pin  = PIN7
    },
    {
        .port = PORTD,
        .pin  = PIN6
    },
    {
        .port = PORTD,
        .pin  = PIN5
    },
    {
        .port = PORTD,
        .pin  = PIN4
    },
    {
        .port = PORTD,
        .pin  = PIN3
    },
    {
        .port = PORTD,
        .pin  = PIN2
    },
    {
        .port = PORTD,
        .pin  = PIN15
    },
    {
        .port = PORTD,
        .pin  = PIN14
    },
    {
        .port = PORTD,
        .pin  = PIN13
    },
    {
        .port = PORTD,
        .pin  = PIN12
    },
};

uint8_t keyTable[6][21] = {0};

void test(void *arg )
{
    Drv_Key_Detect();
}

void Drv_Key_Init(void )
{
    Hal_Key_Init();    

    Drv_Timer_Regist_Period(test, 0, 1, NULL);
}

void Drv_key_Row_Set_All_Pin_High(void )
{
    uint8_t i;

    for(i=0;i<sizeof(rowBuf)/sizeof(keyPin_typedef);i++)
    {
        Hal_Key_Set_Pin_High(rowBuf[i].port, rowBuf[i].pin);
    }
}

void Drv_Key_Col_Set_All_Pin_High(void )
{
    uint8_t i;

    for(i=0;i<sizeof(colBuf)/sizeof(keyPin_typedef);i++)
    {
        Hal_Key_Set_Pin_High(colBuf[i].port, colBuf[i].pin);
    }
}

void Drv_Key_Col_Set_Pin_Low(uint8_t colNum )
{
    Drv_Key_Col_Set_All_Pin_High();

    Hal_Key_Set_Pin_Low(colBuf[colNum].port, colBuf[colNum].pin);
}

uint8_t Drv_Key_Scan_Row(void )
{
    uint8_t i;
    uint8_t rowPortVal = 0;

    for(i=0;i<sizeof(rowBuf)/sizeof(keyPin_typedef);i++)
    {
        if(Hal_Key_Get_Pin(rowBuf[i].port, rowBuf[i].pin) == 0)
        {
            rowPortVal |= (1 << i);
        }
    }

    return rowPortVal;
}

void Drv_Key_Detect(void )
{
    static key_state_t keyState = KEY_COL_INIT;
    static uint8_t rowIndex;
    static uint8_t colIndex;
    static uint8_t tmpColIndex;
    static uint16_t keyDelayCnt;
    uint8_t rowPortVal = 0;

    if(keyDelayCnt < 0xffff)
    {
        keyDelayCnt++;
    }

    switch(keyState)
    {
        case KEY_COL_INIT:
        {
            tmpColIndex++;

            colIndex = tmpColIndex-1;

            if(colIndex == (sizeof(colBuf)/sizeof(keyPin_typedef)))
            {
                tmpColIndex = 0;
            }
            
            Drv_Key_Col_Set_Pin_Low(colIndex);
            
            Drv_key_Row_Set_All_Pin_High();

            keyState = KEY_ROW_INIT;
            
            break;
        }
        case KEY_ROW_INIT:
        {
                            rowPortVal = Drv_Key_Scan_Row();

            if(rowPortVal != 0)
            {
                keyDelayCnt = 0;

                keyState = KEY_DOWN;
                
            }
            else
            {
                keyState = KEY_COL_INIT;
            }
            break;
        }
        case KEY_DOWN:
        {
            uint8_t i;
            
            rowPortVal = Drv_Key_Scan_Row();

            if(rowPortVal != 0)
            {
                if(keyDelayCnt > 5)
                {
                    keyDelayCnt = 0;
                    
                    for(i=0;i<sizeof(rowBuf)/sizeof(keyPin_typedef);i++)
                    {
                        if(rowPortVal & (1 << i))
                        {
                            keyTable[i][colIndex] = 1;
                        }
                    }
                    
                    keyState = KEY_COL_INIT;
                }
            }
            else
            {
                keyState = KEY_COL_INIT;
            }
            break;
        }
    }
}

