/*
***************************************************************************
*    模块：Test_TFTLCD 
*    描述：TFTLCD 应用测试
*    作者：Huo
*    时间：2017.12.13
*    版本：UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "Test_TFTLCD.h"

/* 非精确延时函数 */
//static void _DelayMs(volatile uint16_t xMs)
//{
//	volatile uint32_t Count=24000;
//	while(xMs--)
//	{
//		Count=24000;
//		while(Count--);
//	}
//}

/*
***************************************************************************
*	函 数 名: Test_TFTLCD
*	功能说明: TFTLCD 应用函数
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
void Test_TFTLCD(void)
{
	uint16_t x,y;
	FONT_T tFont;			/* 定义一个字体结构体变量，用于设置字体参数 */

	/* 用于LCD界面标题 */
	//#define VER_INFO	"博创智联 魔法师创意竞赛平台 STM32开发板(V1.0h)"
	char VER_INFO[] =	"博创智联 魔法师创意竞赛平台 STM32开发板(V1.0h)";

	LCD_ClrScr(CL_WHITE);	/* 清屏，显示全白 */
//	LCD_DrawLine(0,240,800,240,CL_BLACK);
//	LCD_DrawLine(400,0,400,480,CL_BLACK);
	LCD_DrawBMP(0,0,480,800,(uint16_t*)0x0800F000);
//	for(y=0;y<240;y++)
//		for(x=0;x<400;x++)
//		{
//			LCD_PutPixel(x,y+240,LCD_GetPixel(x,y));
//		}
//	LCD_DrawRect(450,60,100,120,CL_BLACK);
//	LCD_Fill_Rect(650,60,100,120,CL_BLACK);
//	LCD_DrawRoundRect(450,60,100,120,15,CL_BLACK);
//	LCD_FillRoundRect(650,60,100,120,15,CL_BLACK);
//	LCD_DrawCircle(500,360,60,CL_BLACK);
//	LCD_FillCircle(700,360,60,CL_BLACK);
	
	/* 设置字体参数 */
//	{
	//	tFont.FontCode = FC_ST_16;		/* 字体代码 16点阵 */
	//	tFont.FrontColor = CL_WHITE;	/* 字体颜色 */
	//	tFont.BackColor = CL_RED;		/* 文字背景颜色 */
	//	tFont.Space = 0;				/* 文字间距，单位 = 像素 */
	//}
	//LCD_DispStr(400, 0, VER_INFO, &tFont);	/* 显示软件版本信息 */

	while(1)
	{
	
	}
}
