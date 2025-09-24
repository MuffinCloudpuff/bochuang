#ifndef __BSP_SHT11_H
#define __BSP_SHT11_H

#include "stm32f4xx.h"

enum {TEMP, HUMI};

/* GPIO��غ궨�� */
#define SHT11_RCC_CLK		(RCC_AHB1Periph_GPIOB)
#define SHT11_DATA_PIN		GPIO_Pin_7
#define SHT11_SCK_PIN			GPIO_Pin_6
#define SHT11_DATA_PORT		GPIOB
#define SHT11_SCK_PORT		GPIOB

#define SHT11_DATA_H()		GPIO_SetBits(SHT11_DATA_PORT, SHT11_DATA_PIN)          //����DATA������
#define SHT11_DATA_L()      GPIO_ResetBits(SHT11_DATA_PORT, SHT11_DATA_PIN)        //����DATA������
#define SHT11_DATA_R()      GPIO_ReadInputDataBit(SHT11_DATA_PORT, SHT11_DATA_PIN) //��DATA������

#define SHT11_SCK_H()       GPIO_SetBits(SHT11_SCK_PORT, SHT11_SCK_PIN)            //����SCKʱ����
#define SHT11_SCK_L()       GPIO_ResetBits(SHT11_SCK_PORT, SHT11_SCK_PIN)          //����SCKʱ����

/* ��������غ궨�� */
#define noACK		       0
#define ACK                1
                                       //addr      command        r/w
#define STATUS_REG_W       0x06        //000         0011          0          д״̬�Ĵ���
#define STATUS_REG_R       0x07        //000         0011          1          ��״̬�Ĵ���
#define MEASURE_TEMP       0x03        //000         0001          1          �����¶�
#define MEASURE_HUMI       0x05        //000         0010          1          ����ʪ��
#define SOFTRESET		   0x1E        //000         1111          0          ��λ


void BSP_SHT11_Init(void);
void BSP_SHT11_ConReset(void);
uint8_t BSP_SHT11_SoftReset(void);
uint8_t BSP_SHT11_Measure(uint16_t *p_value, uint8_t *p_checksum, uint8_t mode);
void BSP_SHT11_Calculate(uint16_t t, uint16_t rh,float *p_temperature, float *p_humidity);
float BSP_SHT11_CalcuDewPoint(float t, float h);

#endif
