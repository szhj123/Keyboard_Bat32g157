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

const uint8_t keyTableVal[6][21] = 
{
    0x29,0x00,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x00,0x00,0x00,0x00,
    0x35,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x2d,0x2e,0x2a,0x49,0x4a,0x4b,0x53,0x54,0x55,0x56,
    0x2b,0x14,0x1a,0x08,0x15,0x17,0x1c,0x18,0x0c,0x12,0x13,0x2f,0x30,0x31,0x4c,0x4d,0x4e,0x5f,0x60,0x61,0x57,
    0x39,0x04,0x16,0x07,0x09,0x0a,0x0b,0x0d,0x0e,0x0f,0x33,0x34,0x00,0x28,0x00,0x00,0x00,0x5c,0x5d,0x5e,0x00,
    0xe1,0x1d,0x1b,0x06,0x19,0x05,0x11,0x10,0x36,0x37,0x38,0x00,0x00,0xe5,0x00,0x52,0x00,0x59,0x5a,0x5b,0x58,
    0xe0,0xe3,0xe2,0x00,0x00,0x2c,0x00,0x00,0xe6,0xff,0x65,0x00,0x00,0xe4,0x50,0x51,0x4f,0x62,0x00,0x63,0x00
};

uint8_t keyTableMap[6][21] = {0};
key_queue_t keyQueue;


void test(void *arg )
{

    Drv_Key_Detect();
    
    Drv_Key_Get_keyTableMap_Val();
    
}

void Drv_Key_Init(void )
{
    UART0_Init(SystemCoreClock, 9600);
    
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

                keyState = KEY_SHORT_PRESS;
                
            }
            else
            {
                keyState = KEY_COL_INIT;
            }
            break;
        }
        case KEY_SHORT_PRESS:
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
                            keyTableMap[i][colIndex] = 1;
                        }
                        else
                        {
                            keyTableMap[i][colIndex] = 0;
                        }
                    }
                    
                    keyState = KEY_COL_INIT;
                }
            }
            else
            {
                for(i=0;i<sizeof(rowBuf)/sizeof(keyPin_typedef);i++)
                {
                    keyTableMap[i][colIndex] = 0;
                }
                
                keyState = KEY_COL_INIT;
            }
            break;
        }
        default: break;
    }
}


void Drv_Key_Get_keyTableMap_Val(void )
{
    static uint8_t tmpkeyTableMap[6][21] = {0};
    static uint8_t isKeyPress;
    static uint16_t keyDelayCnt;
    
    static uint8_t txBuf[8];
    static uint8_t txLen;
    uint8_t i,j;

    if(keyDelayCnt > 0)
    {
        keyDelayCnt--;
    }

    isKeyPress = 0;
    
    for(i=0;i<6;i++)
    {
        for(j=0;j<21;j++)
        {
            if(keyTableMap[i][j] != tmpkeyTableMap[i][j])
            {
                tmpkeyTableMap[i][j] = keyTableMap[i][j];

                if(tmpkeyTableMap[i][j])
                {
                    keyQueue.buf[keyQueue.rear] = keyTableVal[i][j];
                }
                else
                {
                    keyQueue.buf[keyQueue.rear] = 0;
                }

                keyQueue.rear = (keyQueue.rear + 1) % 32;

                isKeyPress = 1;
            }
        }
    }

    if(isKeyPress)
    {
        txLen = keyQueue.rear-keyQueue.front;
        
        for(i=0;i<txLen;i++)
        {
            txBuf[i] = keyQueue.buf[keyQueue.front];
            
            if(keyQueue.buf[keyQueue.front] != 0)
            {
                UART0_Send(keyQueue.buf[keyQueue.front]);
            }
            
            keyQueue.front = (keyQueue.front + 1) %32;
        }

        keyDelayCnt = 500;
    }
    else
    {
        if(keyDelayCnt == 0)
        {
            for(i=0;i<txLen;i++)
            {
                if(txBuf[i] != 0)
                {
                    UART0_Send(txBuf[i]);
                }
            }

            keyDelayCnt = 50;
        }
        
    }
}

