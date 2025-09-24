/*
***************************************************************************
*    ģ�飺Test_LEDBuzzer 
*    ������LEDBuzzer Ӧ�ò���
*    ���ߣ�Huo
*    ʱ�䣺2017.09.06
*    �汾��UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "Test_LEDBuzzer.h"
#include "Test_IRDA.h"

/*
***************************************************************************
*	�� �� ��: Test_LEDBuzzer
*	����˵��: LEDBuzzer Ӧ�ú���
*	��    ��: ��
*	�� �� ֵ: ��
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
			BSP_LEDBuzzer_On(LED);
		BSP_Delay_ms(1000);
		
	}
	

	
		if(!QueueMemDataDel(&Command))
			switch(Command)
			{
				case '1':
					BSP_LEDBuzzer_On(LED);    printf("LED ��\r\n");    break;
				case '2':
					BSP_LEDBuzzer_Off(LED);   printf("LED ��\r\n");   break;
				case '4':
					BSP_LEDBuzzer_On(Buzzer); printf("������ ����\r\n"); break;
				case '5':
					BSP_LEDBuzzer_Off(Buzzer);printf("������ Ϣ��\r\n");break;
				default:
					printf("����������������룡\r\n\r\n");
			
	}
}
