/*
***************************************************************************
*    ģ�飺Test_TFTLCD 
*    ������TFTLCD Ӧ�ò���
*    ���ߣ�Huo
*    ʱ�䣺2017.12.13
*    �汾��UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "Test_TFTLCD.h"

/* �Ǿ�ȷ��ʱ���� */
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
*	�� �� ��: Test_TFTLCD
*	����˵��: TFTLCD Ӧ�ú���
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
void Test_TFTLCD(void)
{
	uint16_t x,y;
	FONT_T tFont;			/* ����һ������ṹ���������������������� */

	/* ����LCD������� */
	//#define VER_INFO	"�������� ħ��ʦ���⾺��ƽ̨ STM32������(V1.0h)"
	char VER_INFO[] =	"�������� ħ��ʦ���⾺��ƽ̨ STM32������(V1.0h)";

	LCD_ClrScr(CL_WHITE);	/* ��������ʾȫ�� */
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
	
	/* ����������� */
//	{
	//	tFont.FontCode = FC_ST_16;		/* ������� 16���� */
	//	tFont.FrontColor = CL_WHITE;	/* ������ɫ */
	//	tFont.BackColor = CL_RED;		/* ���ֱ�����ɫ */
	//	tFont.Space = 0;				/* ���ּ�࣬��λ = ���� */
	//}
	//LCD_DispStr(400, 0, VER_INFO, &tFont);	/* ��ʾ����汾��Ϣ */

	while(1)
	{
	
	}
}
