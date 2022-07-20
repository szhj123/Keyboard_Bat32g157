/********************************************************
* @file       app_key.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_task.h"
#include "drv_timer.h"

#include "app_usb_keyboard.h"
#include "app_key.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Key_Handler(void *arg );
/* Private variables ------------------------------------*/
key_t key;

void App_Key_Init(void )
{
    Drv_Key_Init();

    //Drv_Timer_Regist_Period(App_Key_Handler, 0, 1, NULL);
}

static void App_Key_Handler(void *arg )
{
    if(App_Usb_Get_Config_State() != USB_CONFIG_SUCCESS)
    {
        return ;
    }

    Drv_Key_Scan();

    Drv_Key_Get_Val(&key);

    if(key.state != KEY_STATE_NULL)
    {
        key.state = KEY_STATE_NULL;
    }
}

