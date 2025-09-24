/*
***************************************************************************
*    ģ�飺BSP_ExtInt 
*    �������弶 ExtInt ����ģ������
		   ExtInt1-PG13 ExtInt2-PF9 �������ж�
*    ���ߣ�Huo
*    ʱ�䣺2017.09.28
*    �汾��UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "BSP_MIC.h"

/* �ڲ��������� */
static void BSP_ExtInt_GPIO_Init(void);
static void BSP_ExtInt_NVIC_Init(void);
static void BSP_ExtInt_EXTI_Init(void);

/*
***************************************************************************
*	�� �� ��: BSP_ExtInt_Init
*	����˵��: �弶 ExtInt ��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
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
*	�� �� ��: BSP_ExtInt_GPIO_Init
*	����˵��: �弶 ExtInt GPIO �ڲ���ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
static void BSP_ExtInt_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_ExtInt1 | RCC_ExtInt2, ENABLE);	//ʹ�ܶ�Ӧʱ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_ExtInt1;
	GPIO_Init(GPIO_PORT_ExtInt1, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_ExtInt2;
	GPIO_Init(GPIO_PORT_ExtInt2, &GPIO_InitStructure);
}

/*
***************************************************************************
*	�� �� ��: BSP_ExtInt_NVIC_Init
*	����˵��: ����ExtInt NVIC��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
static void BSP_ExtInt_NVIC_Init(void)
{
 	NVIC_InitTypeDef NVIC_InitStructure;

	/* ʹ�ܰ��� ExtInt2 ���ڵ��ⲿ�ж�ͨ�� */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;				
	/* ��ռ���ȼ����ã����ȼ�����Ϊ 4 ������£���ռ���ȼ������÷�Χ 0-15 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;
	/* �����ȼ����ã����ȼ�����Ϊ 4 ������£������ȼ���Ч��ȡ��ֵ 0 ���� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure); 

	/* ʹ�ܰ��� ExtInt1 ���ڵ��ⲿ�ж�ͨ�� */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			
	/* ��ռ���ȼ����ã����ȼ�����Ϊ 4 ������£���ռ���ȼ������÷�Χ 0-15 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;
	/* �����ȼ����ã����ȼ�����Ϊ 4 ������£������ȼ���Ч��ȡ��ֵ 0 ���� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure);
}

/*
***************************************************************************
*	�� �� ��: BSP_ExtInt_EXTI_Init
*	����˵��: ����ExtInt EXTI��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
static void BSP_ExtInt_EXTI_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);//ʹ�ܸ��ù���ʱ��

	/* GPIOG.13 ExtInt1 �ж����Լ��жϳ�ʼ������ �����ش��� */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource13);
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	  	

	/* GPIOF.9 ExtInt2 �ж����Լ��жϳ�ʼ������  �����ش��� */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF,GPIO_PinSource9);
	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
	EXTI_Init(&EXTI_InitStructure);	 	
}
