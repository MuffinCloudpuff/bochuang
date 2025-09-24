/*
***************************************************************************
*    ģ�飺Test_IRDA 
*    ������IRDA Ӧ�ò���
*    ���ߣ�Huo
*    ʱ�䣺2017.09.26
*    �汾��UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "Test_IRDA.h"

/*
***************************************************************************
*	�� �� ��: Test_IRDA
*	����˵��: IRDA Ӧ�ú���
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
void Test_IRDA(void)
{
	uint8_t i=0,j=0;
	uint16_t buf[READ_TIMES]={0},temp=0;
	uint32_t sum=0;
	
	
	
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

		printf("ADCֵ : %d \r\n",temp);

		//printf("ADConverter1 : %d \r\n",BSP_ADConverter_Get(ADC_Channel_11));
		//printf("ADConverter3 : %d \r\n",BSP_ADConverter_Get(ADC_Channel_13));
		BSP_Delay_ms(500);
	
}
