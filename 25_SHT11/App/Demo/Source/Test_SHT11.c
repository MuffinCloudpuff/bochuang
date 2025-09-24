/*
***************************************************************************
*    ģ�飺Test_SHT11 
*    ������SHT11 Ӧ�ò���
*    ���ߣ�Huo
*    ʱ�䣺2017.09.25
*    �汾��UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "Test_SHT11.h"

/*
***************************************************************************
*	�� �� ��: Test_SHT11
*	����˵��: SHT11 Ӧ�ú���
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
void Test_SHT11(void)
{
	u16 humi_val, temp_val;
	u8 err = 0, checksum = 0;
	float humi_val_real = 0.0; 
	float temp_val_real = 0.0;
	float dew_point = 0.0;

	
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
		BSP_Delay_ms(1000);
	
}
