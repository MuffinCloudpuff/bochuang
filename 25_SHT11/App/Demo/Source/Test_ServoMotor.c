/*
***************************************************************************
*    模块：Test_ServoMotor 
*    描述：ServoMotor 应用测试
*    作者：Huo
*    时间：2017.09.07
*    版本：UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "Test_ServoMotor.h"

/*
***************************************************************************
*	函 数 名: Test_ServoMotor
*	功能说明: ServoMotor 应用函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
void Test_ServoMotor(void)
{
	
	
		BSP_ServoMotor1_Set(1000);		//最左
//		BSP_ServoMotor2_Set(1000);		//最左
//		BSP_ServoMotor3_Set(1000);		//最左
//		BSP_ServoMotor4_Set(1000);		//最左
//		BSP_ServoMotor5_Set(1000);		//最左
//		BSP_ServoMotor6_Set(1000);		//最左
//		BSP_ServoMotor7_Set(1000);		//最左
//		BSP_ServoMotor8_Set(1000);		//最左
		BSP_Delay_ms(1000);
		/* 舵机左中右 右中左往复 */
		BSP_ServoMotor1_Set(0);
//		BSP_ServoMotor2_Set(0);
//		BSP_ServoMotor3_Set(0);
//		BSP_ServoMotor4_Set(0);
//		BSP_ServoMotor5_Set(0);
//		BSP_ServoMotor6_Set(0);
//		BSP_ServoMotor7_Set(0);
//		BSP_ServoMotor8_Set(0);
		BSP_Delay_ms(1000);
		
		BSP_ServoMotor1_Set(1000);		//最左
//		BSP_ServoMotor2_Set(1000);		//最左
//		BSP_ServoMotor3_Set(1000);		//最左
//		BSP_ServoMotor4_Set(1000);		//最左
//		BSP_ServoMotor5_Set(1000);		//最左
//		BSP_ServoMotor6_Set(1000);		//最左
//		BSP_ServoMotor7_Set(1000);		//最左
//		BSP_ServoMotor8_Set(1000);		//最左
		BSP_Delay_ms(1000);
		/* 舵机左中右 右中左往复 */
		BSP_ServoMotor1_Set(0);
//		BSP_ServoMotor2_Set(0);
//		BSP_ServoMotor3_Set(0);
//		BSP_ServoMotor4_Set(0);
//		BSP_ServoMotor5_Set(0);
//		BSP_ServoMotor6_Set(0);
//		BSP_ServoMotor7_Set(0);
//		BSP_ServoMotor8_Set(0);
//		BSP_Delay_ms(1000);
		
	
}
