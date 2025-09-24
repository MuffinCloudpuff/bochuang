/*
***************************************************************************
*    模块：Test_SHT11 
*    描述：SHT11 应用测试
*    作者：Huo
*    时间：2017.09.25
*    版本：UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "Test_SHT11.h"

/*
***************************************************************************
*	函 数 名: Test_SHT11
*	功能说明: SHT11 应用函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
void Test_SHT11(void)
{
	u16 humi_val, temp_val;
	u8 err = 0, checksum = 0;
	float humi_val_real = 0.0; 
	float temp_val_real = 0.0;
	float dew_point = 0.0;

	
		err += BSP_SHT11_Measure(&temp_val, &checksum, TEMP);//获取温度测量值
		err += BSP_SHT11_Measure(&humi_val, &checksum, HUMI);//获取湿度测量值
		if(err != 0)
			BSP_SHT11_ConReset();
		else
		{
			/* 计算实际的温湿度值 */
			BSP_SHT11_Calculate(temp_val, humi_val, &temp_val_real, \
													&humi_val_real);
			/* 计算露点温度 */
			dew_point = BSP_SHT11_CalcuDewPoint(temp_val_real, humi_val_real);                 
		} 
		printf("当前环境温度为:%2.1f℃，湿度为:%2.1f%%，露点温度为%2.1f℃\r\n",\
									temp_val_real, humi_val_real, dew_point);
		BSP_Delay_ms(1000);
	
}
