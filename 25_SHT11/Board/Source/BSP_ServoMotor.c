/*
***************************************************************************
*    模块：BSP_ServoMotor 
*    描述：板级 ServoMotor 功能模块驱动
*		   TIM1_CH2N-PB14  TIM8_CH3N-PB1  TIM1_CH1-PA8  TIM3_CH3-PB0
*		   TIM8_CH1-PC6   TIM1_CH3N-PB15  TIM2_CH4-PB11  TIM2_CH3-PB10
*    作者：Huo
*    时间：2017.09.06
*    版本：UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "BSP_ServoMotor.h"

/* 内部函数声明 */
static void BSP_ServoMotor_GPIO_Init(void);
static void BSP_ServoMotor_TIM1_Init(void);
//static void BSP_ServoMotor_TIM8_Init(void);
//static void BSP_ServoMotor_TIM2_Init(void);
//static void BSP_ServoMotor_TIM3_Init(void);

/*
***************************************************************************
*	函 数 名: BSP_ServoMotor_Init
*	功能说明: 板载ServoMotor初始化函数
*	形    参: 无
*	返 回 值: 无
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
*	函 数 名: BSP_ServoMotor_GPIO_Init
*	功能说明: 板载ServoMotor GPIO初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
static void BSP_ServoMotor_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | \
	                  RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM1); //GPIOB14复用为定时器1
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1 ,GPIO_AF_TIM8); //GPIOB1 复用为定时器8
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8 ,GPIO_AF_TIM1); //GPIOA8 复用为定时器1
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0 ,GPIO_AF_TIM3); //GPIOB0 复用为定时器3
//	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6 ,GPIO_AF_TIM8); //GPIOC6 复用为定时器8
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM1); //GPIOB15复用为定时器1
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_TIM2); //GPIOB11复用为定时器2
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_TIM2); //GPIOB10复用为定时器2

	//设置该引脚为复用输出功能,输出TIM1 CH2N 的PWM脉冲波形	GPIOB.14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //TIM1_CH2N
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIO
//	//设置该引脚为复用输出功能,输出TIM8 CH3N 的PWM脉冲波形	GPIOB.1
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM8_CH3N
//	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIO
	//设置该引脚为复用输出功能,输出TIM1 CH1 的PWM脉冲波形	GPIOA.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM1_CH1
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化GPIO
//	//设置该引脚为复用输出功能,输出TIM3 CH3 的PWM脉冲波形	GPIOB.0
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM3_CH3
//	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIO
//	//设置该引脚为复用输出功能,输出TIM8 CH1 的PWM脉冲波形	GPIOC.6
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM8_CH1
//	GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化GPIO
	//设置该引脚为复用输出功能,输出TIM1 CH3N 的PWM脉冲波形	GPIOB.15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //TIM1_CH3N
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIO
//	//设置该引脚为复用输出功能,输出TIM2 CH4 的PWM脉冲波形	GPIOB.11
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM2_CH4
//	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIO
//	//设置该引脚为复用输出功能,输出TIM2 CH3 的PWM脉冲波形	GPIOB.10
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TIM2_CH3
//	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIO
//	GPIO_SetBits(GPIOB, GPIO_Pin_10 |GPIO_Pin_11);
}

/*
***************************************************************************
*	函 数 名: BSP_ServoMotor_TIM1_Init
*	功能说明: 板载ServoMotor TIM1初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
static void BSP_ServoMotor_TIM1_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //使能定时器1时钟
	
	TIM_TimeBaseStructure.TIM_Period = 20000-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 168-1; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //设置 周期 计数值
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	/* Channel 1 2 3 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //使能输出比较状态
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //使能 互补 输出状态
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值 占空时间
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low; //互补 输出极性高
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; //MOE=0 设置 TIM1输出比较空闲状态
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //MOE=0 重置 TIM1输出比较空闲状态
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); //设定好的参数 初始化TIM
	TIM_OC2Init(TIM1, &TIM_OCInitStructure); //设定好的参数 初始化TIM
	TIM_OC3Init(TIM1, &TIM_OCInitStructure); //设定好的参数 初始化TIM

//	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
//	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
//	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);

//	TIM_ARRPreloadConfig(TIM1, ENABLE);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE); 
	
	TIM_Cmd(TIM1, ENABLE);
}
/*
***************************************************************************
*	函 数 名: BSP_ServoMotor_TIM8_Init
*	功能说明: 板载ServoMotor TIM8初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
//static void BSP_ServoMotor_TIM8_Init(void)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); //使能定时器8时钟
//	
//	TIM_TimeBaseStructure.TIM_Period = 20000-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
//	TIM_TimeBaseStructure.TIM_Prescaler = 168-1; //设置用来作为TIMx时钟频率除数的预分频值 
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //设置 周期 计数值
//	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
//	
//	/* Channel 1 3 Configuration in PWM mode */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //使能输出比较状态
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //使能 互补 输出状态
//	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值 占空时间
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
//	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low; //互补 输出极性高
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; //MOE=0 设置 TIM8输出比较空闲状态
//	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //MOE=0 重置 TIM8输出比较空闲状态
//	TIM_OC1Init(TIM8, &TIM_OCInitStructure); //设定好的参数 初始化TIM
//	TIM_OC3Init(TIM8, &TIM_OCInitStructure); //设定好的参数 初始化TIM

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
*	函 数 名: BSP_ServoMotor_TIM2_Init
*	功能说明: 板载ServoMotor TIM2初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
//static void BSP_ServoMotor_TIM2_Init(void)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //使能定时器2时钟
//	
//	TIM_TimeBaseStructure.TIM_Period = 20000-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
//	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; //设置用来作为TIMx时钟频率除数的预分频值 
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
//	
//	/* Channel 3 4 Configuration in PWM mode */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //使能输出比较状态
//	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值 占空时间
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
//	TIM_OC3Init(TIM2, &TIM_OCInitStructure); //设定好的参数 初始化TIM
//	TIM_OC4Init(TIM2, &TIM_OCInitStructure); //设定好的参数 初始化TIM

//	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
//	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);

//	TIM_ARRPreloadConfig(TIM2, ENABLE);
//	
//	TIM_Cmd(TIM2, ENABLE);
//}
/*
***************************************************************************
*	函 数 名: BSP_ServoMotor_TIM3_Init
*	功能说明: 板载ServoMotor TIM3初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
//static void BSP_ServoMotor_TIM3_Init(void)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能定时器3时钟
//	
//	TIM_TimeBaseStructure.TIM_Period = 20000-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
//	TIM_TimeBaseStructure.TIM_Prescaler = 84-1; //设置用来作为TIMx时钟频率除数的预分频值 
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
//	
//	/* Channel 3 Configuration in PWM mode */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //使能输出比较状态
//	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值 占空时间
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
//	TIM_OC3Init(TIM3, &TIM_OCInitStructure); //设定好的参数 初始化TIM

//	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);

//	TIM_ARRPreloadConfig(TIM3, ENABLE);
//	
//	TIM_Cmd(TIM3, ENABLE);
//}

/*
***************************************************************************
*	函 数 名: BSP_ServoMotor_Set
*	功能说明: 板载ServoMotor转角功能函数
*	形    参: ServoMotorValue : 转角值
*	返 回 值: 无
***************************************************************************
*/
void BSP_ServoMotor1_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 对应左~右各90度
{
  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //限幅
    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
  else
    ;
  
  TIM_SetCompare2(TIM1, SERVOMOTOR_CENTER + ServoMotorValue);
}
//void BSP_ServoMotor2_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 对应左~右各90度
//{
//  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //限幅
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
//  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
//  else
//    ;
//  
//  TIM_SetCompare3(TIM8, SERVOMOTOR_CENTER + ServoMotorValue);
//}
void BSP_ServoMotor3_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 对应左~右各90度
{
  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //限幅
    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
  else
    ;
  
  TIM_SetCompare1(TIM1, SERVOMOTOR_CENTER + ServoMotorValue);
}
//void BSP_ServoMotor4_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 对应左~右各90度
//{
//  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //限幅
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
//  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
//  else
//    ;
//  
//  TIM_SetCompare3(TIM3, SERVOMOTOR_CENTER + ServoMotorValue);
//}
//void BSP_ServoMotor5_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 对应左~右各90度
//{
//  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //限幅
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
//  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
//  else
//    ;
//  
//  TIM_SetCompare1(TIM8, SERVOMOTOR_CENTER + ServoMotorValue);
//}
void BSP_ServoMotor6_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 对应左~右各90度
{
  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //限幅
    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
  else
    ;
  
  TIM_SetCompare3(TIM1, SERVOMOTOR_CENTER + ServoMotorValue);
}
//void BSP_ServoMotor7_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 对应左~右各90度
//{
//  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //限幅
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
//  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
//  else
//    ;
//  
//  TIM_SetCompare4(TIM2, SERVOMOTOR_CENTER + ServoMotorValue);
//}
//void BSP_ServoMotor8_Set(int ServoMotorValue)	//ServoMotorValue -1000~1000 对应左~右各90度
//{
//  if(ServoMotorValue < (SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX))   //限幅
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_LEFT_MAX;
//  else if(ServoMotorValue > (SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX))
//    ServoMotorValue = SERVOMOTOR_CENTER - SERVOMOTOR_RIGHT_MAX;
//  else
//    ;
//  
//  TIM_SetCompare3(TIM2, SERVOMOTOR_CENTER + ServoMotorValue);
//}
