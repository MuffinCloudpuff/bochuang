#ifndef __BSP_EXTINT_H
#define __BSP_EXTINT_H

#include "stm32f4xx.h"

#define RCC_ExtInt1			(RCC_AHB1Periph_GPIOA)
#define GPIO_PORT_ExtInt1	GPIOA
#define GPIO_PIN_ExtInt1	(GPIO_Pin_2)
#define RCC_ExtInt2			(RCC_AHB1Periph_GPIOA)
#define GPIO_PORT_ExtInt2  	GPIOA
#define GPIO_PIN_ExtInt2	(GPIO_Pin_3)



void BSP_ExtInt_Init(void);

#endif
