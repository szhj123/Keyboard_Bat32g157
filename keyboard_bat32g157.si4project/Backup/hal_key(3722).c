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
    //row0, pa00, output
    PORT_Init(PORTA, PIN0, OUTPUT);
    //row1, pa01, output
    PORT_Init(PORTA, PIN1, OUTPUT);
    //rot2, pa03, output
    PORT_Init(PORTA, PIN3, OUTPUT);
    //rot3, pa12, output
    PORT_Init(PORTA, PIN12, OUTPUT);
    //rot4, pa13, output
    PORT_Init(PORTA, PIN13, OUTPUT);
    //rot5, pa14, output
    PORT_Init(PORTA, PIN14, OUTPUT);

    //col1, pb05, output
    PORT_Init(PORTB, PIN5, OUTPUT);
    //col2, pb04, output
    PORT_Init(PORTB, PIN4, OUTPUT);
    //col3, pb02, output
    PORT_Init(PORTB, PIN2, OUTPUT);
    //col4, pb01, output
    PORT_Init(PORTB, PIN1, OUTPUT);
    //col5, ph03, output
    PORT_Init(PORTH, PIN3, OUTPUT);
    //col6, ph04, output
    PORT_Init(PORTH, PIN4, OUTPUT);
    //col7, pb00, output
    PORT_Init(PORTB, PIN0, OUTPUT);
    //col8, pd11, output
    PORT_Init(PORTD, PIN11, OUTPUT);
    //col9, pd10, output
    PORT_Init(PORTD, PIN10, OUTPUT);
    //col10, pd09, output
    PORT_Init(PORTD, PIN9, OUTPUT);
    //col11, pd08, output
    PORT_Init(PORTD, PIN8, OUTPUT);
    //col12, pd07, output
    PORT_Init(PORTD, PIN7, OUTPUT);
    //col13, pd06, output
    PORT_Init(PORTD, PIN6, OUTPUT);
    //col14, pd05, output
    PORT_Init(PORTD, PIN5, OUTPUT);
    //col15, pd04, output
    PORT_Init(PORTD, PIN4, OUTPUT);
    //col16, pd03, output
    PORT_Init(PORTD, PIN3, OUTPUT);
    //col17, pd02, output
    PORT_Init(PORTD, PIN2, OUTPUT);
    //col18, pd15, output
    PORT_Init(PORTD, PIN15, OUTPUT);
    //col19, pd14, output
    PORT_Init(PORTD, PIN14, OUTPUT);
    //col20, pd13, output
    PORT_Init(PORTD, PIN13, OUTPUT);
    //col21, pd12, output
    PORT_Init(PORTD, PIN12, OUTPUT);
}


