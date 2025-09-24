/*
***************************************************************************
*    模块：BSP_ADConverter 
*    描述：板级 ADConverter 功能模块驱动
		   ADC1CH11-PC1 ADC1CH13-PC3
*    作者：Huo
*    时间：2017.09.26
*    版本：UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "BSP_ADConverter.h"

/* 内部函数声明 */
static void BSP_ADConverter_GPIO_Init(void);
static void BSP_ADConverter_ADC_Init(void);

/*
***************************************************************************
*	函 数 名: BSP_ADConverter_Init
*	功能说明: 板级 ADConverter 初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
void BSP_ADConverter_Init(void)
{
	BSP_ADConverter_GPIO_Init();
	BSP_ADConverter_ADC_Init();
}

/*
***************************************************************************
*	函 数 名: BSP_ADConverter_GPIO_Init
*	功能说明: 板载ADConverter GPIO初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
static void BSP_ADConverter_GPIO_Init(void)
{ 	
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟

	//先初始化ADC1通道11 IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PC1 通道11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化  
	//先初始化ADC1通道13 IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PC3 通道13
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化  
}

/*
***************************************************************************
*	函 数 名: BSP_ADConverter_ADC_Init
*	功能说明: 板载ADConverter ADC初始化函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
static void BSP_ADConverter_ADC_Init(void)
{ 	
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束	 

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化

	ADC_Cmd(ADC1, ENABLE);//开启AD转换器	
}				  

/*
***************************************************************************
*	函 数 名: BSP_ADConverter_Get
*	功能说明: 板载ADConverter Get功能函数
*	形    参: ADConverterChannel : 指示ADConverterChannel序号
*	返 回 值: ADConverterChannel 转换结果
***************************************************************************
*/
uint16_t BSP_ADConverter_Get(uint8_t ADConverterChannel)
{
	

 	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ADConverterChannel, 1, ADC_SampleTime_480Cycles);	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  	

	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
	 	

	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
