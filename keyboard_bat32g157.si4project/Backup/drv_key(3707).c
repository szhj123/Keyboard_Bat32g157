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

 key_detect_para_t keyDetPara;
 
 void Drv_Key_Init(void )
 {    
     Hal_Key_Init();    
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

  void Drv_Key_Col_Set_All_Pin_Low(void )
 {
     uint8_t i;
 
     for(i=0;i<sizeof(colBuf)/sizeof(keyPin_typedef);i++)
     {
         Hal_Key_Set_Pin_Low(colBuf[i].port, colBuf[i].pin);
     }
 }

 void Drv_Key_Col_Set_Pin_High(uint8_t colNum )
 {
    Hal_Key_Set_Pin_High(colBuf[colNum].port, colBuf[colNum].pin);
 }
 
 void Drv_Key_Col_Set_Pin_Low(uint8_t colNum )
 { 
     Hal_Key_Set_Pin_Low(colBuf[colNum].port, colBuf[colNum].pin);
 }
 
 void Drv_Key_Delay_Us(uint16_t us)
 {
     uint16_t i,j;
 
     for(i=0;i<us;i++)
     {
         for(j=0;j<48;j++);
     }
 }
 
 void Drv_Key_Scan(void )
 {
     uint8_t i,j;
 
     for(i=0;i<sizeof(colBuf)/sizeof(keyPin_typedef);i++)
     {
         Drv_key_Row_Set_All_Pin_High();

         Drv_Key_Col_Set_All_Pin_High();
             
         Drv_Key_Col_Set_Pin_Low(i);
 
         for(j=0;j<sizeof(rowBuf)/sizeof(keyPin_typedef);j++)
         {
             if(Hal_Key_Get_Pin(rowBuf[j].port, rowBuf[j].pin) == 0)
             {
                 Drv_Key_Delay_Us(25);
 
                 if(Hal_Key_Get_Pin(rowBuf[j].port, rowBuf[j].pin) == 0)
                 {
                     keyTableMap[j][i] = 1;
                 }
             }
             else
             {
                 keyTableMap[j][i] = 0;
             }
         }
     }
 }
 
 void Drv_Key_Get_Val(key_t *pKey )
 {
     static uint8_t tmpkeyTableMap[6][21] = {0};
     uint8_t i,j;
 
     if(keyDetPara.keyDelayCnt  < 0xffff)
     {
         keyDetPara.keyDelayCnt++;
     }
     
     keyDetPara.keyPressFlag = 0;
     
     for(i=0;i<6;i++)
     {
         for(j=0;j<21;j++)
         {
             if(keyTableMap[i][j] != tmpkeyTableMap[i][j])
             {
                 tmpkeyTableMap[i][j] = keyTableMap[i][j];
 
                 if(keyTableMap[i][j])
                 {
                     keyDetPara.keyNewBuf[keyDetPara.keyNewCnt++] = keyTableVal[i][j];

                     if(keyDetPara.keyNewCnt >= KEY_MAX_NUM)
                     {
                         keyDetPara.keyNewCnt = 0;
                     }

                     keyDetPara.keyNewAddFlag = 1;
                 }
                 else
                 {
                     keyDetPara.keyNewAddFlag = 0;
                 }
 
                 keyDetPara.keyDetState = KEY_DET_DEBOUNCE;
                 
                 keyDetPara.keyDelayCnt = 0;
             }

             if(keyTableMap[i][j])
             { 
                 keyDetPara.keyPressFlag = 1;
             }
         }
     }
 
     switch(keyDetPara.keyDetState)
     {
         case KEY_DET_DEBOUNCE:
         {
             uint8_t i,j;
             
             if(keyDetPara.keyDelayCnt > 50)
             {
                keyDetPara.keyDelayCnt  = 0;

                for(i=0;i<6;i++)
                {
                    for(j=0;j<21;j++)
                    {
                        if(keyTableMap[i][j])
                        {
                            keyDetPara.keyOldBuf[keyDetPara.keyOldCnt++] =  keyTableVal[i][j];

                            if(keyDetPara.keyOldCnt >= KEY_MAX_NUM)
                            {
                               keyDetPara.keyOldCnt = 0;
                            }
                        }
                    }
                }

                for(i=0;i<sizeof(pKey->buf);i++)
                {
                    pKey->buf[i] = 0;
                }

                for(i=0;i<keyDetPara.keyOldCnt;i++)
                {
                    switch(keyDetPara.keyOldBuf[i])
                    {
                       case 0xe0: pKey->buf[0] |= 0x01; break;
                       case 0xe1: pKey->buf[0] |= 0x02; break;
                       case 0xe2: pKey->buf[0] |= 0x04; break;
                       case 0xe3: pKey->buf[0] |= 0x08; break;
                       case 0xe4: pKey->buf[0] |= 0x10; break;
                       case 0xe5: pKey->buf[0] |= 0x20; break;
                       case 0xe6: pKey->buf[0] |= 0x40; break;
                       case 0xe7: pKey->buf[0] |= 0x80; break;
                       default: break;
                    }
                }
               
                keyDetPara.keyDetState = KEY_DET_SHORT_PRESS;
             }

             break;
         }
         case KEY_DET_SHORT_PRESS:
         {

             j=2;

             if(keyDetPara.keyNewAddFlag == 0)
             {                
                 for(i=0;i<keyDetPara.keyOldCnt;i++)
                 {
                     if(keyDetPara.keyOldBuf[i] < 0xe0 || keyDetPara.keyOldBuf[i] > 0xe7)
                     {
                         pKey->buf[j++] = keyDetPara.keyOldBuf[i];
                     }
                 }
             }
             else
             {
                 for(i=0;i<keyDetPara.keyNewCnt;i++)
                 {
                     if(keyDetPara.keyNewBuf[i] < 0xe0 || keyDetPara.keyNewBuf[i] > 0xe7)
                     {
                         pKey->buf[j++] = keyDetPara.keyNewBuf[i];
                     }
                 }
             }
             
             keyDetPara.keyOldCnt = 0;
             keyDetPara.keyNewCnt = 0;
             keyDetPara.keyDelayCnt = 0;
             keyDetPara.keyDetState = KEY_DET_LONG_PRESS;

             pKey->state = KEY_SHORT_PRESS;
             
             break;
              
         }
         case KEY_DET_LONG_PRESS:
         {
             if(keyDetPara.keyPressFlag)
             {
                 if(keyDetPara.keyDelayCnt > 500)
                 {
                     keyDetPara.keyDelayCnt = 0;
 
                     keyDetPara.keyDetState = KEY_DET_CONT_PRESS;

                     pKey->state = KEY_LONG_PRESS;
                 }
             }
             else
             {
                 keyDetPara.keyDetState = KEY_DET_RELEASE;
             }
             break;
         }
         case KEY_DET_CONT_PRESS:
         {
             if(keyDetPara.keyPressFlag)
             {
                 if(keyDetPara.keyDelayCnt > 50)
                 {
                    keyDetPara.keyDelayCnt = 0;
                    
                     pKey->state = KEY_CONT_PRESS;
                 }
             }
             else
             {
                 keyDetPara.keyDetState = KEY_DET_RELEASE;
             }

             break;
         }
         case KEY_DET_RELEASE:
         {
             for(i=0;i<KEY_MAX_NUM;i++)
             {
                 keyDetPara.keyOldBuf[i] = 0;
                 keyDetPara.keyNewBuf[i] = 0;
                 pKey->buf[i] = 0;
             }

             keyDetPara.keyDetState = KEY_DET_NULL;
             
             pKey->state = KEY_RELEASE;
         }

         default:  break;
     }
 }
 
