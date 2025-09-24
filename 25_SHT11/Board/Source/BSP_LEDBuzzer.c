/*
***************************************************************************
*    模块：BSP_LEDBuzzer 
*    描述：板级 LEDBuzzer 功能模块驱动
		   LED-PG15 高电平点亮，Buzzer-PF11 高电平发声
*    作者：Huo
*    时间：2017.09.05
*    版本：UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "BSP_LEDBuzzer.h"

/* 内部函数声明 */
static void BSP_LEDBuzzer_GPIO_Init(void);

/*
***************************************************************************
*	函 数 名: BSP_LEDBuzzer_Init
*	功能说明: 板级 LEDBuzzer 初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
void BSP_LEDBuzzer_Init(void)
{
	BSP_LEDBuzzer_GPIO_Init();
}

/*
***************************************************************************
*	函 数 名: BSP_LEDBuzzer_GPIO_Init
*	功能说明: 板级 LEDBuzzer GPIO 内部初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
static void BSP_LEDBuzzer_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_LED | RCC_Buzzer, ENABLE);//使能对应时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIO_PORT_LED, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_Buzzer;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIO_PORT_Buzzer, &GPIO_InitStructure);
	
	BSP_LEDBuzzer_Off(LED | Buzzer);
}

/*
***************************************************************************
*	函 数 名: BSP_LEDBuzzer_On
*	功能说明: 板级 LED点亮、Buzzer发声 功能函数
*	形    参: LEDBuzzer
*	返 回 值: 无
***************************************************************************
*/
void BSP_LEDBuzzer_On(uint8_t LEDBuzzer)
{
	if (LEDBuzzer & LED)
		GPIO_PORT_LED->BSRRL = GPIO_PIN_LED;
	if (LEDBuzzer & Buzzer)
		GPIO_PORT_Buzzer->BSRRL = GPIO_PIN_Buzzer;
}

/*
***************************************************************************
*	函 数 名: BSP_LEDBuzzer_Off
*	功能说明: 板级 LED熄灭、Buzzer息声 功能函数
*	形    参: LEDBuzzer
*	返 回 值: 无
***************************************************************************
*/
void BSP_LEDBuzzer_Off(uint8_t LEDBuzzer)
{
	if (LEDBuzzer & LED)
		GPIO_PORT_LED->BSRRH = GPIO_PIN_LED;
	if (LEDBuzzer & Buzzer)
		GPIO_PORT_Buzzer->BSRRH = GPIO_PIN_Buzzer;
}

/*
***************************************************************************
*	函 数 名: BSP_LEDBuzzer_Toggle
*	功能说明: 板级 LED、Buzzer 状态翻转功能函数
*	形    参: LEDBuzzer
*	返 回 值: 无
***************************************************************************
*/
void BSP_LEDBuzzer_Toggle(uint8_t LEDBuzzer)
{
	if (LEDBuzzer & LED)
		GPIO_PORT_LED->ODR ^= GPIO_PIN_LED;
	if (LEDBuzzer & Buzzer)
		GPIO_PORT_Buzzer->ODR ^= GPIO_PIN_Buzzer;
}
