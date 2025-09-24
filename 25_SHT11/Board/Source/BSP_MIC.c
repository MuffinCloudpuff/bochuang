/*
***************************************************************************
*    模块：BSP_ExtInt 
*    描述：板级 ExtInt 功能模块驱动
		   ExtInt1-PG13 ExtInt2-PF9 上升沿中断
*    作者：Huo
*    时间：2017.09.28
*    版本：UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "BSP_MIC.h"

/* 内部函数声明 */
static void BSP_ExtInt_GPIO_Init(void);
static void BSP_ExtInt_NVIC_Init(void);
static void BSP_ExtInt_EXTI_Init(void);

/*
***************************************************************************
*	函 数 名: BSP_ExtInt_Init
*	功能说明: 板级 ExtInt 初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
void BSP_ExtInt_Init(void)
{
	BSP_ExtInt_GPIO_Init();
	BSP_ExtInt_NVIC_Init();
	BSP_ExtInt_EXTI_Init();
}

/*
***************************************************************************
*	函 数 名: BSP_ExtInt_GPIO_Init
*	功能说明: 板级 ExtInt GPIO 内部初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
static void BSP_ExtInt_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_ExtInt1 | RCC_ExtInt2, ENABLE);	//使能对应时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_ExtInt1;
	GPIO_Init(GPIO_PORT_ExtInt1, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_ExtInt2;
	GPIO_Init(GPIO_PORT_ExtInt2, &GPIO_InitStructure);
}

/*
***************************************************************************
*	函 数 名: BSP_ExtInt_NVIC_Init
*	功能说明: 板载ExtInt NVIC初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
static void BSP_ExtInt_NVIC_Init(void)
{
 	NVIC_InitTypeDef NVIC_InitStructure;

	/* 使能按键 ExtInt2 所在的外部中断通道 */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;				
	/* 抢占优先级设置，优先级分组为 4 的情况下，抢占优先级可设置范围 0-15 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;
	/* 子优先级设置，优先级分组为 4 的情况下，子优先级无效，取数值 0 即可 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure); 

	/* 使能按键 ExtInt1 所在的外部中断通道 */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			
	/* 抢占优先级设置，优先级分组为 4 的情况下，抢占优先级可设置范围 0-15 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;
	/* 子优先级设置，优先级分组为 4 的情况下，子优先级无效，取数值 0 即可 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure);
}

/*
***************************************************************************
*	函 数 名: BSP_ExtInt_EXTI_Init
*	功能说明: 板载ExtInt EXTI初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
static void BSP_ExtInt_EXTI_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);//使能复用功能时钟

	/* GPIOG.13 ExtInt1 中断线以及中断初始化配置 上升沿触发 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource13);
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	  	

	/* GPIOF.9 ExtInt2 中断线以及中断初始化配置  上升沿触发 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF,GPIO_PinSource9);
	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
	EXTI_Init(&EXTI_InitStructure);	 	
}
