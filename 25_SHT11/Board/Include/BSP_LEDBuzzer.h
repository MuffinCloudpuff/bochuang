#ifndef __BSP_LEDBUZZER_H
#define __BSP_LEDBUZZER_H

#include "stm32f4xx.h"

#define LED					((uint8_t)0x01)
#define Buzzer				((uint8_t)0x02)


#define RCC_LED				(RCC_AHB1Periph_GPIOG)
#define GPIO_PORT_LED		GPIOG
#define GPIO_PIN_LED		(GPIO_Pin_15)
#define RCC_Buzzer			(RCC_AHB1Periph_GPIOF)
#define GPIO_PORT_Buzzer	GPIOF
#define GPIO_PIN_Buzzer		(GPIO_Pin_11)

void BSP_LEDBuzzer_Init(void);

void BSP_LEDBuzzer_On(uint8_t LEDBuzzer);
void BSP_LEDBuzzer_Off(uint8_t LEDBuzzer);
void BSP_LEDBuzzer_Toggle(uint8_t LEDBuzzer);

#endif
