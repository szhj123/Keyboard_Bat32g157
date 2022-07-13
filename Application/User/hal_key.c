/********************************************************
* @file       hal_key.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_key.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Hal_Key_Init(void )
{
    PORT_Init(PORTA, PIN0, PULLUP_INPUT);
    PORT_Init(PORTA, PIN1, PULLUP_INPUT);
    PORT_Init(PORTA, PIN3, PULLUP_INPUT);
    PORT_Init(PORTA, PIN12, PULLUP_INPUT);
    PORT_Init(PORTA, PIN13, PULLUP_INPUT);
    PORT_Init(PORTA, PIN14, PULLUP_INPUT);

    PORT_Init(PORTB, PIN5, OUTPUT);
    PORT_Init(PORTB, PIN4, OUTPUT);
    PORT_Init(PORTB, PIN2, OUTPUT);
    PORT_Init(PORTB, PIN1, OUTPUT);
    PORT_Init(PORTH, PIN3, OUTPUT);
    PORT_Init(PORTH, PIN4, OUTPUT);
    PORT_Init(PORTB, PIN0, OUTPUT);
    PORT_Init(PORTD, PIN11, OUTPUT);
    PORT_Init(PORTD, PIN10, OUTPUT);
    PORT_Init(PORTD, PIN9, OUTPUT);
    PORT_Init(PORTD, PIN8, OUTPUT);
    PORT_Init(PORTD, PIN7, OUTPUT);
    PORT_Init(PORTD, PIN6, OUTPUT);
    PORT_Init(PORTD, PIN5, OUTPUT);
    PORT_Init(PORTD, PIN4, OUTPUT);
    PORT_Init(PORTD, PIN3, OUTPUT);
    PORT_Init(PORTD, PIN2, OUTPUT);
    PORT_Init(PORTD, PIN15, OUTPUT);
    PORT_Init(PORTD, PIN14, OUTPUT);
    PORT_Init(PORTD, PIN13, OUTPUT);
    PORT_Init(PORTD, PIN12, OUTPUT);
}

void Hal_Key_Set_Pin_High(PORT_TypeDef port, PIN_TypeDef pin )
{
    PORT_SetBit(port, pin);
}

void Hal_Key_Set_Pin_Low(PORT_TypeDef port, PIN_TypeDef pin )
{
    PORT_ClrBit(port, pin);
}

uint8_t Hal_Key_Get_Pin(PORT_TypeDef port, PIN_TypeDef pin )
{
    if(PORT_GetBit(port, pin))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
