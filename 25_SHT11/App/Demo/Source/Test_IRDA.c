/*
***************************************************************************
*    模块：Test_IRDA 
*    描述：IRDA 应用测试
*    作者：Huo
*    时间：2017.09.26
*    版本：UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "Test_IRDA.h"

/*
***************************************************************************
*	函 数 名: Test_IRDA
*	功能说明: IRDA 应用函数
*	形    参: 无
*	返 回 值: 无
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

		for(i=0;i<READ_TIMES-1;i++)//排序
		{
			for(j=i+1;j<READ_TIMES;j++)
			{
				if(buf[i]>buf[j])//升序排列
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

		printf("ADC值 : %d \r\n",temp);

		//printf("ADConverter1 : %d \r\n",BSP_ADConverter_Get(ADC_Channel_11));
		//printf("ADConverter3 : %d \r\n",BSP_ADConverter_Get(ADC_Channel_13));
		BSP_Delay_ms(500);
	
}
