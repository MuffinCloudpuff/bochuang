#ifndef __BSP_EXTINT_H
#define __BSP_EXTINT_H

#include "stm32f4xx.h"

#define RCC_ExtInt1			(RCC_AHB1Periph_GPIOG)
#define GPIO_PORT_ExtInt1	GPIOG
#define GPIO_PIN_ExtInt1	(GPIO_Pin_13)
#define RCC_ExtInt2			(RCC_AHB1Periph_GPIOF)
#define GPIO_PORT_ExtInt2  	GPIOF
#define GPIO_PIN_ExtInt2	(GPIO_Pin_9)

#define RCC_ExtInt3			(RCC_AHB1Periph_GPIOA)
#define GPIO_PORT_ExtInt3	GPIOA
#define GPIO_PIN_ExtInt3	(GPIO_Pin_1)
#define RCC_ExtInt4			(RCC_AHB1Periph_GPIOA)
#define GPIO_PORT_ExtInt4  	GPIOA
#define GPIO_PIN_ExtInt4	(GPIO_Pin_0)

void BSP_ExtInt_Init(void);

#endif
