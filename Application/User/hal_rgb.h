#ifndef _HAL_RGB_H
#define _HAL_RGB_H

#include "hal_bat32g157.h"
#include "hal_key.h"

#define DCLK_L()                PORT_ClrBit(PORTC, PIN3)
#define DCLK_H()                PORT_SetBit(PORTC, PIN3)

#define SIN_L()                 PORT_ClrBit(PORTC, PIN4)
#define SIN_H()                 PORT_SetBit(PORTC, PIN4)

#define LE_L()                  PORT_ClrBit(PORTA, PIN4)
#define LE_H()                  PORT_SetBit(PORTA, PIN4)


void Hal_Rgb_Init(void );
void Hal_Rgb_Gclk_Init(void );
void Hal_Rgb_Spi_Init(void );
void Hal_Rgb_Send_With_Loop(uint16_t *buf, uint16_t length );

#endif 

