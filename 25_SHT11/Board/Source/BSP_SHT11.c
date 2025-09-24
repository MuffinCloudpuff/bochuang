/*
***************************************************************************
*    ģ�飺BSP_SHT11 
*    �������弶 SHT11 ����ģ������
*    ���ߣ�Huo
*    ʱ�䣺2017.09.25
*    �汾��UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "BSP_SHT11.h"
#include "math.h"

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_Dly
*	����˵��: ���� SHT11 ʱ����Ҫ����ʱ
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
static void BSP_SHT11_Dly(void)
{
	volatile uint16_t i;
	for(i = 1500; i > 0; i--);
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_Init
*	����˵��: ���� SHT11 ��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
void BSP_SHT11_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;        
	RCC_AHB1PeriphClockCmd(SHT11_RCC_CLK ,ENABLE);
			
	GPIO_InitStructure.GPIO_Pin = SHT11_DATA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(SHT11_DATA_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SHT11_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(SHT11_SCK_PORT, &GPIO_InitStructure);

	BSP_SHT11_ConReset();        //��λͨѶ
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_DataOut
*	����˵��: ���� SHT11 ����data����Ϊ������ܺ���
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
void BSP_SHT11_DataOut(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = SHT11_DATA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(SHT11_DATA_PORT, &GPIO_InitStructure);
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_DataIn
*	����˵��: ���� SHT11 ����data����Ϊ���빦�ܺ���
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
void BSP_SHT11_DataIn(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = SHT11_DATA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SHT11_DATA_PORT, &GPIO_InitStructure);
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_WriteByte
*	����˵��: ���� SHT11 д���ֽڹ��ܺ���
*	��    ��: value:Ҫд����ֽ�
*	�� �� ֵ: err: 0-��ȷ  1-���� 
***************************************************************************
*/
uint8_t BSP_SHT11_WriteByte(uint8_t value)
{
	uint8_t i, err = 0;

	BSP_SHT11_DataOut();	//����DATA������Ϊ���

	for(i = 0x80; i > 0; i /= 2)  //д1���ֽ�
	{
		if(i & value)
			SHT11_DATA_H();
		else
			SHT11_DATA_L();
		BSP_SHT11_Dly();
		SHT11_SCK_H();
		BSP_SHT11_Dly();
		SHT11_SCK_L();
		BSP_SHT11_Dly();
	}
	BSP_SHT11_DataIn();		//����DATA������Ϊ����,�ͷ�DATA��
	SHT11_SCK_H();
	err = SHT11_DATA_R();	//��ȡSHT11��Ӧ��λ
	SHT11_SCK_L();

	return err;
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_ReadByte
*	����˵��: ���� SHT11 �����ֽڹ��ܺ���
*	��    ��: Ack: 0-��Ӧ��  1-Ӧ��
*	�� �� ֵ: err: 0-��ȷ  1-���� 
***************************************************************************
*/
uint8_t BSP_SHT11_ReadByte(uint8_t Ack)
{
	uint8_t i, val = 0;

	BSP_SHT11_DataIn();	//����DATA������Ϊ����
	for(i = 0x80; i > 0; i /= 2)  //��ȡ1�ֽڵ�����
	{
		BSP_SHT11_Dly();
		SHT11_SCK_H();
		BSP_SHT11_Dly();
		if(SHT11_DATA_R())
			val = (val | i);
		SHT11_SCK_L();
	}
	BSP_SHT11_DataOut();   //����DATA������Ϊ���
	if(Ack)
		SHT11_DATA_L();    //Ӧ��������ȥ������ȥ������(У������)
	else
		SHT11_DATA_H();    //��Ӧ���������˽���
	BSP_SHT11_Dly();
	SHT11_SCK_H();
	BSP_SHT11_Dly();
	SHT11_SCK_L();
	BSP_SHT11_Dly();

	return val;            //���ض�����ֵ
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_TransStart
*	����˵��: ��ʼ�����źţ�ʱ�����£�
                     _____         ________
               DATA:      |_______|
                         ___     ___
               SCK : ___|   |___|   |______        
*	��    ��: ��
*	�� �� ֵ: �� 
***************************************************************************
*/
void BSP_SHT11_TransStart(void)
{
	BSP_SHT11_DataOut();   //����DATA������Ϊ���

	SHT11_DATA_H();
	SHT11_SCK_L();
	BSP_SHT11_Dly();
	SHT11_SCK_H();
	BSP_SHT11_Dly();
	SHT11_DATA_L();
	BSP_SHT11_Dly();
	SHT11_SCK_L();
	BSP_SHT11_Dly();
	SHT11_SCK_H();
	BSP_SHT11_Dly();
	SHT11_DATA_H();
	BSP_SHT11_Dly();
	SHT11_SCK_L();
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_ConReset
*	����˵��: ͨѶ��λ��ʱ�����£�
      _____________________________________________________         ________
DATA:                                                      |_______|
         _    _    _    _    _    _    _    _    _        ___     ___
SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______
*	��    ��: ��
*	�� �� ֵ: �� 
***************************************************************************
*/
void BSP_SHT11_ConReset(void)
{
	uint8_t i;

	BSP_SHT11_DataOut();

	SHT11_DATA_H();
	SHT11_SCK_L();

	for(i = 0; i < 9; i++)     //����SCKʱ��9c��
	{
		SHT11_SCK_H();
		BSP_SHT11_Dly();
		SHT11_SCK_L();
		BSP_SHT11_Dly();
	}
	BSP_SHT11_TransStart();    //��������
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_SoftReset
*	����˵��: ��λ
*	��    ��: ��
*	�� �� ֵ: err: 0-��ȷ  1-���� 
***************************************************************************
*/
uint8_t BSP_SHT11_SoftReset(void)
{
	uint8_t err = 0;

	BSP_SHT11_ConReset();                      //ͨѶ��λ
	err += BSP_SHT11_WriteByte(SOFTRESET); //дRESET��λ����

	return err;
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_ReadStatusReg
*	����˵��: ��״̬�Ĵ���
*	��    ��: p_value-���������ݣ�p_checksun-������У������
*	�� �� ֵ: err: 0-��ȷ  1-���� 
***************************************************************************
*/
uint8_t BSP_SHT11_ReadStatusReg(uint8_t *p_value, uint8_t *p_checksum)
{
	uint8_t err = 0;

	BSP_SHT11_TransStart();                 //��ʼ����
	err = BSP_SHT11_WriteByte(STATUS_REG_R);//дSTATUS_REG_R��ȡ״̬�Ĵ�������
	*p_value = BSP_SHT11_ReadByte(ACK);     //��ȡ״̬����
	*p_checksum = BSP_SHT11_ReadByte(noACK);//��ȡ���������

	return err;
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_WriteStatusReg
*	����˵��: д״̬�Ĵ���
*	��    ��: p_value-Ҫд�������ֵ
*	�� �� ֵ: err: 0-��ȷ  1-���� 
***************************************************************************
*/
uint8_t BSP_SHT11_WriteStatusReg(uint8_t *p_value)
{
	uint8_t err = 0;

	BSP_SHT11_TransStart();                  //��ʼ����
	err += BSP_SHT11_WriteByte(STATUS_REG_W);//дSTATUS_REG_Wд״̬�Ĵ�������
	err += BSP_SHT11_WriteByte(*p_value);    //д������ֵ

	return err;
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_Measure
*	����˵��: ����ʪ�ȴ�������ȡ��ʪ��
*	��    ��: p_value-������ֵ��p_checksum-������У����
*	�� �� ֵ: err: 0-��ȷ 1������
***************************************************************************
*/
uint8_t BSP_SHT11_Measure(uint16_t *p_value, uint8_t *p_checksum, uint8_t mode)
{
	uint8_t err = 0;
	uint32_t i;
	uint8_t value_H = 0;
	uint8_t value_L = 0;

	BSP_SHT11_TransStart();		//��ʼ����
	switch(mode)                                                         
	{
		case TEMP:              //�����¶�
			err += BSP_SHT11_WriteByte(MEASURE_TEMP);//дMEASURE_TEMP�����¶�����
		break;
		case HUMI:
			err += BSP_SHT11_WriteByte(MEASURE_HUMI);//дMEASURE_HUMI����ʪ������
		break;
		default:
		break;
	}
	BSP_SHT11_DataIn();
	for(i = 0; i < 72000000; i++) //�ȴ�DATA�źű�����
	{
		if(SHT11_DATA_R() == 0) break;  //��⵽DATA�������ˣ�����ѭ��
	}
	if(SHT11_DATA_R() == 1)             //����ȴ���ʱ��
		err += 1;
	value_H = BSP_SHT11_ReadByte(ACK);
	value_L = BSP_SHT11_ReadByte(ACK);
	*p_checksum = BSP_SHT11_ReadByte(noACK); //��ȡУ������
	*p_value = (value_H << 8) | value_L;
	
	return err;
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_Calculate
*	����˵��: ������ʪ�ȵ�ֵ
*	��    ��: Temp-�Ӵ������������¶�ֵ��Humi-�Ӵ�����������ʪ��ֵ
              p_humidity-�������ʵ�ʵ�ʪ��ֵ��p_temperature-�������ʵ���¶�ֵ
*	�� �� ֵ: ��
***************************************************************************
*/
void BSP_SHT11_Calculate(uint16_t t, uint16_t rh, float *p_temperature, float *p_humidity)
{
	const float d1 = -39.7;
	const float d2 = +0.01;
	const float C1 = -2.0468;
	const float C2 = +0.0367;
	const float C3 = -0.0000015955;        
	const float T1 = +0.01;
	const float T2 = +0.00008;

	float RH_Lin;   //RH����ֵ        
	float RH_Ture;  //RH��ʵֵ
	float temp_C;

	temp_C = d1 + d2 * t;                             //�����¶�ֵ        
	RH_Lin = C1 + C2 * rh + C3 * rh * rh;             //����ʪ��ֵ
	RH_Ture = (temp_C -25) * (T1 + T2 * rh) + RH_Lin; //ʪ�ȵ��¶Ȳ���������ʵ�ʵ�ʪ��ֵ

	if(RH_Ture > 100)                                 //����ʪ��ֵ����
		RH_Ture        = 100;
	if(RH_Ture < 0.1)
		RH_Ture = 0.1;                                //����ʪ��ֵ����

	*p_humidity = RH_Ture;
	*p_temperature = temp_C;
}

/*
***************************************************************************
*	�� �� ��: BSP_SHT11_CalcuDewPoint
*	����˵��: ����¶��
*	��    ��: h-ʵ�ʵ�ʪ�ȣ�t-ʵ�ʵ��¶� 
*	�� �� ֵ: dew_point-¶��
***************************************************************************
*/
float BSP_SHT11_CalcuDewPoint(float t, float h)
{
	float logEx, dew_point;

	logEx = 0.66077 + 7.5 * t / (237.3 + t) + (log10(h) - 2);
	dew_point = ((0.66077 - logEx) * 237.3) / (logEx - 8.16077);

	return dew_point; 
}

