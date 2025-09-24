/*
***************************************************************************
*    ģ�飺BSP_ADConverter 
*    �������弶 ADConverter ����ģ������
		   ADC1CH11-PC1 ADC1CH13-PC3
*    ���ߣ�Huo
*    ʱ�䣺2017.09.26
*    �汾��UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "BSP_ADConverter.h"

/* �ڲ��������� */
static void BSP_ADConverter_GPIO_Init(void);
static void BSP_ADConverter_ADC_Init(void);

/*
***************************************************************************
*	�� �� ��: BSP_ADConverter_Init
*	����˵��: �弶 ADConverter ��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
void BSP_ADConverter_Init(void)
{
	BSP_ADConverter_GPIO_Init();
	BSP_ADConverter_ADC_Init();
}

/*
***************************************************************************
*	�� �� ��: BSP_ADConverter_GPIO_Init
*	����˵��: ����ADConverter GPIO��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
static void BSP_ADConverter_GPIO_Init(void)
{ 	
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOCʱ��

	//�ȳ�ʼ��ADC1ͨ��11 IO��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PC1 ͨ��11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��  
	//�ȳ�ʼ��ADC1ͨ��13 IO��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PC3 ͨ��13
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��  
}

/*
***************************************************************************
*	�� �� ��: BSP_ADConverter_ADC_Init
*	����˵��: ����ADConverter ADC��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
static void BSP_ADConverter_ADC_Init(void)
{ 	
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
	ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��

	ADC_Cmd(ADC1, ENABLE);//����ADת����	
}				  

/*
***************************************************************************
*	�� �� ��: BSP_ADConverter_Get
*	����˵��: ����ADConverter Get���ܺ���
*	��    ��: ADConverterChannel : ָʾADConverterChannel���
*	�� �� ֵ: ADConverterChannel ת�����
***************************************************************************
*/
uint16_t BSP_ADConverter_Get(uint8_t ADConverterChannel)
{
	

 	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ADConverterChannel, 1, ADC_SampleTime_480Cycles);	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  	

	ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	
	 	

	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}
