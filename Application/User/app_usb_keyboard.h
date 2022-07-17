#ifndef _APP_USB_KEYBOARD_H
#define _APP_USB_KEYBOARD_H

#include "hal_bat32g157.h"

#define USB_CONFIG_SUCCESS                 0
#define USB_CONFIG_ERROR                   (!USB_CONFIG_SUCCESS)

void App_Usb_Keyboard_Init(void );
uint8_t App_Usb_Get_Config_State(void );


#endif 

