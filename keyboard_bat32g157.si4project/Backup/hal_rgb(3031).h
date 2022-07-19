#ifndef _HAL_RGB_H
#define _HAL_RGB_H

#include "hal_bat32g157.h"
#include "hal_key.h"

void Hal_Rgb_Init(void );
void Hal_Rgb_Spi_Init(void );
void Hal_Rgb_Send_With_Loop(uint16_t *buf, uint16_t length );

#endif 

