/*
***************************************************************************
*    ģ�飺BSP_ServoMotor 
*    �������弶 ServoMotor ����ģ������
*		   TIM1_CH2N-PB14  TIM8_CH3N-PB1  TIM1_CH1-PA8  TIM3_CH3-PB0
*		   TIM8_CH1-PC6   TIM1_CH3N-PB15  TIM2_CH4-PB11  TIM2_CH3-PB10
*    ���ߣ�Huo
*    ʱ�䣺2017.09.06
*    �汾��UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "BSP_ServoMotor.h"

/* �ڲ��������� */
static void BSP_ServoMotor_GPIO_Init(void);
static void BSP_ServoMotor_TIM1_Init(void);
//static void BSP_ServoMotor_TIM8_Init(void);
//static void BSP_ServoMotor_TIM2_Init(void);
//static void BSP_ServoMotor_TIM3_Init(void);

/*
***************************************************************************
*	�� �� ��: BSP_ServoMotor_Init
*	����˵��: ����ServoMotor��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
void BSP_ServoMotor_Init(void)
{
	BSP_ServoMotor_GPIO_Init();
	BSP_ServoMotor_TIM1_Init();
//	BSP_ServoMotor_TIM8_Init();
//	BSP_ServoMotor_TIM2_Init();
//	BSP_ServoMotor_TIM3_Init();
	
	BSP_ServoMotor1_Set(0);
//	BSP_ServoMotor2_Set(0);
	BSP_ServoMotor3_Set(0);
//	BSP_ServoMotor4_Set(0);
//	BSP_ServoMotor5_Set(0);
	BSP_ServoMotor6_Set(0);
//	BSP_ServoMotor7_Set(0);
//	BSP_ServoMotor8_Set(0);
}

/*
***************************************************************************
*	�� �� ��: BSP_ServoMotor_GPIO_Init
*	����˵��: ����ServoMotor GPIO��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
static void BSP_ServoMotor_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | \
	                  RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM1); //GPIOB14����Ϊ��ʱ��1
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1 ,GPIO_AF_TIM8); //GPIOB1 ����Ϊ��ʱ��8
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8 ,GPIO_AF_TIM1); //GPIOA8 ����Ϊ��ʱ��1
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0 ,GPIO_AF_TIM3); //GPIOB0 ����Ϊ��ʱ��3
//	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6 ,GPIO_AF_TIM8); //GPIOC6 ����Ϊ��ʱ��8
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM1); //GPIOB15����Ϊ��ʱ��1
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_TIM2); //GPIOB11����Ϊ��ʱ��2
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_TIM2); //GPIOB10����Ϊ��ʱ��2

	//���ø�����Ϊ�����������,���TIM1 CH2N ��PWM���岨��	GPIOB.14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //TIM1_CH2N
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO
//	//���ø�����Ϊ�����������,���TIM8 CH3N ��PWM���岨��	GPIOB.1
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM8_CH3N
//	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO
	//���ø�����Ϊ�����������,���TIM1 CH1 ��PWM���岨��	GPIOA.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM1_CH1
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��GPIO
//	//���ø�����Ϊ�����������,���TIM3 CH3 ��PWM���岨��	GPIOB.0
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM3_CH3
//	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO
//	//���ø�����Ϊ�����������,���TIM8 CH1 ��PWM���岨��	GPIOC.6
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM8_CH1
//	GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��GPIO
	//���ø�����Ϊ�����������,���TIM1 CH3N ��PWM���岨��	GPIOB.15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //TIM1_CH3N
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO
//	//���ø�����Ϊ�����������,���TIM2 CH4 ��PWM���岨��	GPIOB.11
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM2_CH4
//	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO
//	//���ø�����Ϊ�����������,���TIM2 CH3 ��PWM���岨��	GPIOB.10
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TIM2_CH3
//	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO
//	GPIO_SetBits(GPIOB, GPIO_Pin_10 |GPIO_Pin_11);
}

/*
***************************************************************************
*	�� �� ��: BSP_ServoMotor_TIM1_Init
*	����˵��: ����ServoMotor TIM1��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
static void BSP_ServoMotor_TIM1_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʹ�ܶ�ʱ��1ʱ��
	
	TIM_TimeBaseStructure.TIM_Period = 20000-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 168-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //���� ���� ����ֵ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/* Channel 1 2 3 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //ʹ������Ƚ�״̬
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //ʹ�� ���� ���״̬
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ ռ��ʱ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low; //���� ������Ը�
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; //MOE=0 ���� TIM1����ȽϿ���״̬
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //MOE=0 ���� TIM1����ȽϿ���״̬
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); //�趨�õĲ��� ��ʼ��TIM
	TIM_OC2Init(TIM1, &TIM_OCInitStructure); //�趨�õĲ��� ��ʼ��TIM
	TIM_OC3Init(TIM1, &TIM_OCInitStructure); //�趨�õĲ��� ��ʼ��TIM

//	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
//	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);

//	TIM_ARRPreloadConfig(TIM1, ENABLE);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE); 
	
	TIM_Cmd(TIM1, ENABLE);
}
/*
***************************************************************************
*	�� �� ��: BSP_ServoMotor_TIM8_Init
*	����˵��: ����ServoMotor TIM8��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
//static void BSP_ServoMotor_TIM8_Init(void)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); //ʹ�ܶ�ʱ��8ʱ��
//	
//	TIM_TimeBaseStructure.TIM_Period = 20000-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//	TIM_TimeBaseStructure.TIM_Prescaler = 168-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //���� ���� ����ֵ
//	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
//	
//	/* Channel 1 3 Configuration in PWM mode */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //ʹ������Ƚ�״̬
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //ʹ�� ���� ���״̬
//	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ ռ��ʱ��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
//	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low; //���� ������Ը�
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; //MOE=0 ���� TIM8����ȽϿ���״̬
//	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //MOE=0 ���� TIM8����ȽϿ���״̬
//	TIM_OC1Init(TIM8, &TIM_OCInitStructure); //�趨�õĲ��� ��ʼ��TIM
//	TIM_OC3Init(TIM8, &TIM_OCInitStructure); //�趨�õĲ��� ��ʼ��TIM

////	TIM_OC1PreloadConfig(TIM8,TIM_OCPreload_Enable);
////	TIM_OC3PreloadConfig(TIM8,TIM_OCPreload_Enable);

////	TIM_ARRPreloadConfig(TIM8, ENABLE);
//	
//	TIM_CtrlPWMOutputs(TIM8,ENABLE); 
//	
//	TIM_Cmd(TIM8, ENABLE);
//}
/*
***************************************************************************
*	�� �� ��: BSP_ServoMotor_TIM2_Init
*	����˵��: ����ServoMotor TIM2��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
//static void BSP_ServoMotor_TIM2_Init(void)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʹ�ܶ�ʱ��2ʱ��
//	
//	TIM_TimeBaseStructure.TIM_Period = 20000-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
//	
//	/* Channel 3 4 Configuration in PWM mode */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //ʹ������Ƚ�״̬
//	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ ռ��ʱ��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
//	TIM_OC3Init(TIM2, &TIM_OCInitStructure); //�趨�õĲ��� ��ʼ��TIM
//	TIM_OC4Init(TIM2, &TIM_OCInitStructure); //�趨�õĲ��� ��ʼ��TIM

//	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
//	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);

//	TIM_ARRPreloadConfig(TIM2, ENABLE);
//	
//	TIM_Cmd(TIM2, ENABLE);
//}
/*
***************************************************************************
*	�� �� ��: BSP_ServoMotor_TIM3_Init
*	����˵��: ����ServoMotor TIM3��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
//static void BSP_ServoMotor_TIM3_Init(void)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ�ܶ�ʱ��3ʱ��
//	
//	TIM_TimeBaseStructure.TIM_Period = 20000-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
//	
//	/* Channel 3 Configuration in PWM mode */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //ʹ������Ƚ�״̬
//	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ ռ��ʱ��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
//	TIM_OC3Init(TIM3, &TIM_OCInitStructure); //�趨�õĲ��� ��ʼ��TIM

//	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);

//	TIM_ARRPreloadConfig(TIM3, ENABLE);
//	
//	TIM_Cmd(TIM3, ENABLE);
//}

/*
***************************************************************************
*	�� �� ��: BSP_ServoMotor_Set
*	����˵��: ����ServoMotorת�ǹ��ܺ���
*	��    ��: ServoMotorValue : ת��ֵ
*	�� �� ֵ: ��
***************************************************************************
*/
void BSP_ServoMotor1_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 ��Ӧ��~�Ҹ�90��
{
  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //�޷�
    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
  else
    ;
  
  TIM_SetCompare2(TIM1, SERVOMOTOR_CENTER + ServoMotorValue);
}
//void BSP_ServoMotor2_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 ��Ӧ��~�Ҹ�90��
//{
//  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //�޷�
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
//  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
//  else
//    ;
//  
//  TIM_SetCompare3(TIM8, SERVOMOTOR_CENTER + ServoMotorValue);
//}
void BSP_ServoMotor3_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 ��Ӧ��~�Ҹ�90��
{
  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //�޷�
    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
  else
    ;
  
  TIM_SetCompare1(TIM1, SERVOMOTOR_CENTER + ServoMotorValue);
}
//void BSP_ServoMotor4_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 ��Ӧ��~�Ҹ�90��
//{
//  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //�޷�
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
//  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
//  else
//    ;
//  
//  TIM_SetCompare3(TIM3, SERVOMOTOR_CENTER + ServoMotorValue);
//}
//void BSP_ServoMotor5_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 ��Ӧ��~�Ҹ�90��
//{
//  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //�޷�
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
//  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
//  else
//    ;
//  
//  TIM_SetCompare1(TIM8, SERVOMOTOR_CENTER + ServoMotorValue);
//}
void BSP_ServoMotor6_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 ��Ӧ��~�Ҹ�90��
{
  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //�޷�
    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
  else
    ;
  
  TIM_SetCompare3(TIM1, SERVOMOTOR_CENTER + ServoMotorValue);
}
//void BSP_ServoMotor7_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 ��Ӧ��~�Ҹ�90��
//{
//  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //�޷�
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
//  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
//  else
//    ;
//  
//  TIM_SetCompare4(TIM2, SERVOMOTOR_CENTER + ServoMotorValue);
//}
//void BSP_ServoMotor8_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 ��Ӧ��~�Ҹ�90��
//{
//  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //�޷�
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
//  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
//  else
//    ;
//  
//  TIM_SetCompare3(TIM2, SERVOMOTOR_CENTER + ServoMotorValue);
//}
