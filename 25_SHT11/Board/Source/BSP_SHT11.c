/*
***************************************************************************
*    模块：BSP_SHT11 
*    描述：板级 SHT11 功能模块驱动
*    作者：Huo
*    时间：2017.09.25
*    版本：UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "BSP_SHT11.h"
#include "math.h"

/*
***************************************************************************
*	函 数 名: BSP_SHT11_Dly
*	功能说明: 板载 SHT11 时序需要的延时
*	形    参: 无
*	返 回 值: 无
***************************************************************************
*/
static void BSP_SHT11_Dly(void)
{
	volatile uint16_t i;
	for(i = 1500; i > 0; i--);
}

/*
***************************************************************************
*	函 数 名: BSP_SHT11_Init
*	功能说明: 板载 SHT11 初始化函数
*	形    参: 无
*	返 回 值: 无
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

	BSP_SHT11_ConReset();        //复位通讯
}

/*
***************************************************************************
*	函 数 名: BSP_SHT11_DataOut
*	功能说明: 板载 SHT11 设置data引脚为输出功能函数
*	形    参: 无
*	返 回 值: 无
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
*	函 数 名: BSP_SHT11_DataIn
*	功能说明: 板载 SHT11 设置data引脚为输入功能函数
*	形    参: 无
*	返 回 值: 无
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
*	函 数 名: BSP_SHT11_WriteByte
*	功能说明: 板载 SHT11 写入字节功能函数
*	形    参: value:要写入的字节
*	返 回 值: err: 0-正确  1-错误 
***************************************************************************
*/
uint8_t BSP_SHT11_WriteByte(uint8_t value)
{
	uint8_t i, err = 0;

	BSP_SHT11_DataOut();	//设置DATA数据线为输出

	for(i = 0x80; i > 0; i /= 2)  //写1个字节
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
	BSP_SHT11_DataIn();		//设置DATA数据线为输入,释放DATA线
	SHT11_SCK_H();
	err = SHT11_DATA_R();	//读取SHT11的应答位
	SHT11_SCK_L();

	return err;
}

/*
***************************************************************************
*	函 数 名: BSP_SHT11_ReadByte
*	功能说明: 板载 SHT11 读入字节功能函数
*	形    参: Ack: 0-不应答  1-应答
*	返 回 值: err: 0-正确  1-错误 
***************************************************************************
*/
uint8_t BSP_SHT11_ReadByte(uint8_t Ack)
{
	uint8_t i, val = 0;

	BSP_SHT11_DataIn();	//设置DATA数据线为输入
	for(i = 0x80; i > 0; i /= 2)  //读取1字节的数据
	{
		BSP_SHT11_Dly();
		SHT11_SCK_H();
		BSP_SHT11_Dly();
		if(SHT11_DATA_R())
			val = (val | i);
		SHT11_SCK_L();
	}
	BSP_SHT11_DataOut();   //设置DATA数据线为输出
	if(Ack)
		SHT11_DATA_L();    //应答，则会接下去读接下去的数据(校验数据)
	else
		SHT11_DATA_H();    //不应答，数据至此结束
	BSP_SHT11_Dly();
	SHT11_SCK_H();
	BSP_SHT11_Dly();
	SHT11_SCK_L();
	BSP_SHT11_Dly();

	return val;            //返回读到的值
}

/*
***************************************************************************
*	函 数 名: BSP_SHT11_TransStart
*	功能说明: 开始传输信号，时序如下：
                     _____         ________
               DATA:      |_______|
                         ___     ___
               SCK : ___|   |___|   |______        
*	形    参: 无
*	返 回 值: 无 
***************************************************************************
*/
void BSP_SHT11_TransStart(void)
{
	BSP_SHT11_DataOut();   //设置DATA数据线为输出

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
*	函 数 名: BSP_SHT11_ConReset
*	功能说明: 通讯复位，时序如下：
      _____________________________________________________         ________
DATA:                                                      |_______|
         _    _    _    _    _    _    _    _    _        ___     ___
SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______
*	形    参: 无
*	返 回 值: 无 
***************************************************************************
*/
void BSP_SHT11_ConReset(void)
{
	uint8_t i;

	BSP_SHT11_DataOut();

	SHT11_DATA_H();
	SHT11_SCK_L();

	for(i = 0; i < 9; i++)     //触发SCK时钟9c次
	{
		SHT11_SCK_H();
		BSP_SHT11_Dly();
		SHT11_SCK_L();
		BSP_SHT11_Dly();
	}
	BSP_SHT11_TransStart();    //启动传输
}

/*
***************************************************************************
*	函 数 名: BSP_SHT11_SoftReset
*	功能说明: 软复位
*	形    参: 无
*	返 回 值: err: 0-正确  1-错误 
***************************************************************************
*/
uint8_t BSP_SHT11_SoftReset(void)
{
	uint8_t err = 0;

	BSP_SHT11_ConReset();                      //通讯复位
	err += BSP_SHT11_WriteByte(SOFTRESET); //写RESET复位命令

	return err;
}

/*
***************************************************************************
*	函 数 名: BSP_SHT11_ReadStatusReg
*	功能说明: 读状态寄存器
*	形    参: p_value-读到的数据；p_checksun-读到的校验数据
*	返 回 值: err: 0-正确  1-错误 
***************************************************************************
*/
uint8_t BSP_SHT11_ReadStatusReg(uint8_t *p_value, uint8_t *p_checksum)
{
	uint8_t err = 0;

	BSP_SHT11_TransStart();                 //开始传输
	err = BSP_SHT11_WriteByte(STATUS_REG_R);//写STATUS_REG_R读取状态寄存器命令
	*p_value = BSP_SHT11_ReadByte(ACK);     //读取状态数据
	*p_checksum = BSP_SHT11_ReadByte(noACK);//读取检验和数据

	return err;
}

/*
***************************************************************************
*	函 数 名: BSP_SHT11_WriteStatusReg
*	功能说明: 写状态寄存器
*	形    参: p_value-要写入的数据值
*	返 回 值: err: 0-正确  1-错误 
***************************************************************************
*/
uint8_t BSP_SHT11_WriteStatusReg(uint8_t *p_value)
{
	uint8_t err = 0;

	BSP_SHT11_TransStart();                  //开始传输
	err += BSP_SHT11_WriteByte(STATUS_REG_W);//写STATUS_REG_W写状态寄存器命令
	err += BSP_SHT11_WriteByte(*p_value);    //写入配置值

	return err;
}

/*
***************************************************************************
*	函 数 名: BSP_SHT11_Measure
*	功能说明: 从温湿度传感器读取温湿度
*	形    参: p_value-读到的值；p_checksum-读到的校验数
*	返 回 值: err: 0-正确 1—错误
***************************************************************************
*/
uint8_t BSP_SHT11_Measure(uint16_t *p_value, uint8_t *p_checksum, uint8_t mode)
{
	uint8_t err = 0;
	uint32_t i;
	uint8_t value_H = 0;
	uint8_t value_L = 0;

	BSP_SHT11_TransStart();		//开始传输
	switch(mode)                                                         
	{
		case TEMP:              //测量温度
			err += BSP_SHT11_WriteByte(MEASURE_TEMP);//写MEASURE_TEMP测量温度命令
		break;
		case HUMI:
			err += BSP_SHT11_WriteByte(MEASURE_HUMI);//写MEASURE_HUMI测量湿度命令
		break;
		default:
		break;
	}
	BSP_SHT11_DataIn();
	for(i = 0; i < 72000000; i++) //等待DATA信号被拉低
	{
		if(SHT11_DATA_R() == 0) break;  //检测到DATA被拉低了，跳出循环
	}
	if(SHT11_DATA_R() == 1)             //如果等待超时了
		err += 1;
	value_H = BSP_SHT11_ReadByte(ACK);
	value_L = BSP_SHT11_ReadByte(ACK);
	*p_checksum = BSP_SHT11_ReadByte(noACK); //读取校验数据
	*p_value = (value_H << 8) | value_L;
	
	return err;
}

/*
***************************************************************************
*	函 数 名: BSP_SHT11_Calculate
*	功能说明: 计算温湿度的值
*	形    参: Temp-从传感器读出的温度值；Humi-从传感器读出的湿度值
              p_humidity-计算出的实际的湿度值；p_temperature-计算出的实际温度值
*	返 回 值: 无
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

	float RH_Lin;   //RH线性值        
	float RH_Ture;  //RH真实值
	float temp_C;

	temp_C = d1 + d2 * t;                             //计算温度值        
	RH_Lin = C1 + C2 * rh + C3 * rh * rh;             //计算湿度值
	RH_Ture = (temp_C -25) * (T1 + T2 * rh) + RH_Lin; //湿度的温度补偿，计算实际的湿度值

	if(RH_Ture > 100)                                 //设置湿度值上限
		RH_Ture        = 100;
	if(RH_Ture < 0.1)
		RH_Ture = 0.1;                                //设置湿度值下限

	*p_humidity = RH_Ture;
	*p_temperature = temp_C;
}

/*
***************************************************************************
*	函 数 名: BSP_SHT11_CalcuDewPoint
*	功能说明: 计算露点
*	形    参: h-实际的湿度；t-实际的温度 
*	返 回 值: dew_point-露点
***************************************************************************
*/
float BSP_SHT11_CalcuDewPoint(float t, float h)
{
	float logEx, dew_point;

	logEx = 0.66077 + 7.5 * t / (237.3 + t) + (log10(h) - 2);
	dew_point = ((0.66077 - logEx) * 237.3) / (logEx - 8.16077);

	return dew_point; 
}

