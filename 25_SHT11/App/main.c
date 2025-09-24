/*
***************************************************************************
*    ģ�飺Test_SHT11 
*    ������SHT11 Ӧ�ò���
*    ���ߣ�Huo
*    ʱ�䣺2017.09.25
*    �汾��UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "stm32f4xx.h"
#include "BSP_DebugUART.h"
#include "BSP_Delay.h"
#include "Queue.h"
#include "BSP_SHT11.h"
#include "Test_SHT11.h"
#include "BSP_ADConverter.h"
#include "Test_IRDA.h"
#include "BSP_LEDBuzzer.h"
#include "Test_LEDBuzzer.h"
#include "BSP_ServoMotor.h"
#include "Test_ServoMotor.h"
#include "Test_Rain.h"
#include "BSP_ExtInt.h"

/* ������ */
int main(void)
{
	uint8_t i=0,j=0;
	uint16_t buf[READ_TIMES]={0},temp=0;
	uint32_t sum=0;
	
	u16 humi_val, temp_val;
	u8 err = 0, checksum = 0;
	float humi_val_real = 0.0; 
	float temp_val_real = 0.0;
	float dew_point = 0.0;
	int state =0;
	/* ���ȼ���������Ϊ 4����ʹ��Ĭ�Ϸ��鷽�� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	BSP_DebugUART_Init(115200);
	BSP_Delay_Init();
	
  printf("***********************TEST********************\r\n");	
	/* ��ʼ�� */
	BSP_SHT11_Init();
	BSP_ADConverter_Init();
	BSP_LEDBuzzer_Init();
	BSP_ExtInt_Init();
	BSP_ServoMotor_Init();
//	
	
//	Test_SHT11();
//	Test_IRDA();
//	Test_LEDBuzzer();
	
	while(1)
	{
		for(i=0;i<READ_TIMES;i++)
		{
			buf[i] = BSP_ADConverter_Get(ADC_Channel_11);
		}

		for(i=0;i<READ_TIMES-1;i++)//����
		{
			for(j=i+1;j<READ_TIMES;j++)
			{
				if(buf[i]>buf[j])//��������
				{
					temp=buf[i];
					buf[i]=buf[j];
					buf[j]=temp;
				}
			}
		}

		sum=0;
		for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)
			sum += buf[i];
		temp = sum/(READ_TIMES-2*LOST_VAL);

		if(temp > 2400 )
		{
			state =1;
		}
	
		if(!GPIO_ReadInputDataBit(GPIO_PORT_ExtInt3,GPIO_PIN_ExtInt3))
		{
			BSP_LEDBuzzer_Off(Buzzer);
		}
	
		if(state ==1)
		{
			BSP_LEDBuzzer_On(LED);
			BSP_ServoMotor1_Set(500);
		}
		if(state ==0)
		{
			BSP_LEDBuzzer_Off(LED);
			BSP_ServoMotor1_Set(-500);
			
		}
		
		printf("ADCֵ : %d \r\n",temp);
		printf("stateֵ : %d \r\n",state);
		err += BSP_SHT11_Measure(&temp_val, &checksum, TEMP);//��ȡ�¶Ȳ���ֵ
		err += BSP_SHT11_Measure(&humi_val, &checksum, HUMI);//��ȡʪ�Ȳ���ֵ
		if(err != 0)
			BSP_SHT11_ConReset();
		else
		{
			/* ����ʵ�ʵ���ʪ��ֵ */
			BSP_SHT11_Calculate(temp_val, humi_val, &temp_val_real, \
													&humi_val_real);
			/* ����¶���¶� */
			dew_point = BSP_SHT11_CalcuDewPoint(temp_val_real, humi_val_real);                 
		} 
		printf("��ǰ�����¶�Ϊ:%2.1f�棬ʪ��Ϊ:%2.1f%%��¶���¶�Ϊ%2.1f��\r\n",\
									temp_val_real, humi_val_real, dew_point);
//		BSP_Delay_ms(1000);
//		
//		BSP_ServoMotor1_Set(0);
//				BSP_Delay_ms(2000);
//		
//		BSP_ServoMotor1_Set(1000);
//		BSP_Delay_ms(2000);
//		
//		BSP_ServoMotor1_Set(0);
//				BSP_Delay_ms(2000);

//		BSP_ServoMotor1_Set(-1000);
//		
//				BSP_Delay_ms(2000);
		state = 0;

	}
	
	
}
