#ifndef _DRV_RGB_H
#define _DRV_RGB_H

#include "hal_rgb.h"

typedef struct _rgb_color_t
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}rgb_color_t;

typedef struct _rgb_horse_t
{
    rgb_color_t rgbColor;
    uint8_t rgbNum;
    uint8_t rgbCol;
    uint8_t rgbRow;
    uint8_t rowSwitchFlag;
}rgb_horse_t;

void Drv_Rgb_Init(void );
void Drv_Rgb_All_Turn_Off(void );
void Drv_Rgb_Set_Row_Data(uint8_t *buf, uint8_t length );
void Drv_Rgb_Show_Horse_Single_Color(uint8_t rgbNum, uint16_t speed, rgb_color_t color );

#endif 

