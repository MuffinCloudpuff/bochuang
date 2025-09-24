/*
***************************************************************************
*    ģ�飺BSP_LEDBuzzer 
*    �������弶 LEDBuzzer ����ģ������
		   LED-PG15 �ߵ�ƽ������Buzzer-PF11 �ߵ�ƽ����
*    ���ߣ�Huo
*    ʱ�䣺2017.09.05
*    �汾��UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "BSP_LEDBuzzer.h"

/* �ڲ��������� */
static void BSP_LEDBuzzer_GPIO_Init(void);

/*
***************************************************************************
*	�� �� ��: BSP_LEDBuzzer_Init
*	����˵��: �弶 LEDBuzzer ��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
void BSP_LEDBuzzer_Init(void)
{
	BSP_LEDBuzzer_GPIO_Init();
}

/*
***************************************************************************
*	�� �� ��: BSP_LEDBuzzer_GPIO_Init
*	����˵��: �弶 LEDBuzzer GPIO �ڲ���ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
static void BSP_LEDBuzzer_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_LED | RCC_Buzzer, ENABLE);//ʹ�ܶ�Ӧʱ��
	
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
*	�� �� ��: BSP_LEDBuzzer_On
*	����˵��: �弶 LED������Buzzer���� ���ܺ���
*	��    ��: LEDBuzzer
*	�� �� ֵ: ��
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
*	�� �� ��: BSP_LEDBuzzer_Off
*	����˵��: �弶 LEDϨ��BuzzerϢ�� ���ܺ���
*	��    ��: LEDBuzzer
*	�� �� ֵ: ��
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
*	�� �� ��: BSP_LEDBuzzer_Toggle
*	����˵��: �弶 LED��Buzzer ״̬��ת���ܺ���
*	��    ��: LEDBuzzer
*	�� �� ֵ: ��
***************************************************************************
*/
void BSP_LEDBuzzer_Toggle(uint8_t LEDBuzzer)
{
	if (LEDBuzzer & LED)
		GPIO_PORT_LED->ODR ^= GPIO_PIN_LED;
	if (LEDBuzzer & Buzzer)
		GPIO_PORT_Buzzer->ODR ^= GPIO_PIN_Buzzer;
}
