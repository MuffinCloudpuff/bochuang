/*
***************************************************************************
*    模块：Test_LEDBuzzer 
*    描述：LEDBuzzer 应用测试
*    作者：Huo
*    时间：2017.09.06
*    版本：UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "Test_LEDBuzzer.h"
#include "Test_IRDA.h"

/*
***************************************************************************
*	函 数 名: Test_LEDBuzzer
*	功能说明: LEDBuzzer 应用函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
void Test_LEDBuzzer(void)
{
	uint8_t Command;
	
		uint8_t i=0,j=0;
	uint16_t buf[READ_TIMES]={0},temp=0;
	uint32_t sum=0;
	
	
	
		for(i=0;i<READ_TIMES;i++)
			buf[i] = BSP_ADConverter_Get(ADC_Channel_11);		 		    
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
	
	if(temp > 2400 )
	{
			BSP_LEDBuzzer_On(LED);
		BSP_Delay_ms(1000);
		
	}
	

	
		if(!QueueMemDataDel(&Command))
			switch(Command)
			{
				case '1':
					BSP_LEDBuzzer_On(LED);    printf("LED 亮\r\n");    break;
				case '2':
					BSP_LEDBuzzer_Off(LED);   printf("LED 灭\r\n");   break;
				case '4':
					BSP_LEDBuzzer_On(Buzzer); printf("蜂鸣器 发声\r\n"); break;
				case '5':
					BSP_LEDBuzzer_Off(Buzzer);printf("蜂鸣器 息声\r\n");break;
				default:
					printf("输入错误，请重新输入！\r\n\r\n");
			
	}
}
