/*
***************************************************************************
*    ģ�飺BSP_ParallelBus 
*    �������弶 ParallelBus ����ģ������
		   FSMC  Bank1_SRAM4_ADDR ((uint32_t)0x6C000000)
*    ���ߣ�Huo
*    ʱ�䣺2017.12.13
*    �汾��UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "BSP_ParallelBus.h"

/* �ڲ��������� */
static void BSP_PBus_GPIO_Init(void);
static void BSP_PBus_FSMC_Init(void);

/*
***************************************************************************
*	�� �� ��: BSP_PBus_Init
*	����˵��: ���� ParallelBus ��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
void BSP_PBus_Init(void)
{
	BSP_PBus_GPIO_Init();
	BSP_PBus_FSMC_Init();
}

/*
***************************************************************************
*	�� �� ��: BSP_PBus_GPIO_Init
*	����˵��: ����PBus���ƿ��ߣ�FSMC�ܽ�����Ϊ���ù���
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
static void BSP_PBus_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ʹ��FSMCʱ�� */
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

	/* ʹ�� GPIOʱ�� */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);

	/* ���� PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
	 PD.10(D15), PD.14(D0), PD.15(D1) Ϊ����������� */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
	                            GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 |
	                            GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* ���� PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
	 PE.14(D11), PE.15(D12) Ϊ����������� */
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
	                            GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
	                            GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* ���� PF.01(A1 (RS)) PF.05(A5) PF.12(A6) PF.13(A7) Ϊ����������� */
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource13, GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	/* ���� PG.12(NE4 (LCD/CS)) Ϊ����������� */
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource12, GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
}

/*
***************************************************************************
*	�� �� ��: BSP_PBus_FSMC_Init
*	����˵��: ����FSMC���ڷ���ʱ��
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************************
*/
static void BSP_PBus_FSMC_Init(void)
{
	FSMC_NORSRAMInitTypeDef  init;
	FSMC_NORSRAMTimingInitTypeDef  timingWrite;
	FSMC_NORSRAMTimingInitTypeDef  timingRead;

	/*-- FSMC Configuration ----------------------------------------------*/
	/*----------------------- SRAM Bank 4 --------------------------------*/
	/* FSMC_Bank1_NORSRAM4 configuration */
	timingWrite.FSMC_AddressSetupTime = 4;
	timingWrite.FSMC_AddressHoldTime = 0;
	timingWrite.FSMC_DataSetupTime = 6;
	timingWrite.FSMC_BusTurnAroundDuration = 1;
	timingWrite.FSMC_CLKDivision = 0;
	timingWrite.FSMC_DataLatency = 0;
	timingWrite.FSMC_AccessMode = FSMC_AccessMode_A;

	timingRead.FSMC_AddressSetupTime = 4;
	timingRead.FSMC_AddressHoldTime = 0;
	timingRead.FSMC_DataSetupTime = 8;
	timingRead.FSMC_BusTurnAroundDuration = 1;
	timingRead.FSMC_CLKDivision = 0;
	timingRead.FSMC_DataLatency = 0;
	timingRead.FSMC_AccessMode = FSMC_AccessMode_A;

	/*
	 LCD configured as follow:
	    - Data/Address MUX = Disable
	    - Memory Type = SRAM
	    - Data Width = 16bit
	    - Write Operation = Enable
	    - Extended Mode = Enable
	    - Asynchronous Wait = Disable
	*/
	init.FSMC_Bank = FSMC_Bank1_NORSRAM4;
	init.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	init.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	init.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	init.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	init.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	init.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	init.FSMC_WrapMode = FSMC_WrapMode_Disable;
	init.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	init.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	init.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	init.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	init.FSMC_WriteBurst = FSMC_WriteBurst_Disable;

	init.FSMC_ReadWriteTimingStruct = &timingRead;
	init.FSMC_WriteTimingStruct = &timingWrite;

	FSMC_NORSRAMInit(&init);

	/* - BANK 4 (of NOR/SRAM Bank 1~4) is enabled */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
}


/*******************************************************************************
* Function Name  : BSP_PBus_WriteBuffer
* Description    : Writes a Half-word buffer to the FSMC SRAM memory. 
* Input          : - pBuffer : pointer to buffer. 
*                  - WriteAddr : SRAM memory internal address from which the data 
*                    will be written.
*                  - NumHalfwordToWrite : number of half-words to write. 
*                    
* Output         : None
* Return         : None
*******************************************************************************/
void BSP_PBus_WriteBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite)
{
  for(; NumHalfwordToWrite != 0; NumHalfwordToWrite--) /* while there is data to write */
  {
    /* Transfer data to the memory */
    *(uint16_t *) (Bank1_SRAM4_ADDR + WriteAddr) = *pBuffer++;
    
    /* Increment the address*/  
    WriteAddr += 2;
  }   
}

/*******************************************************************************
* Function Name  : BSP_PBus_ReadBuffer
* Description    : Reads a block of data from the FSMC SRAM memory.
* Input          : - pBuffer : pointer to the buffer that receives the data read 
*                    from the SRAM memory.
*                  - ReadAddr : SRAM memory internal address to read from.
*                  - NumHalfwordToRead : number of half-words to read.
* Output         : None
* Return         : None
*******************************************************************************/
void BSP_PBus_ReadBuffer(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead)
{
  for(; NumHalfwordToRead != 0; NumHalfwordToRead--) /* while there is data to read */
  {
    /* Read a half-word from the memory */
    *pBuffer++ = *(volatile uint16_t*) (Bank1_SRAM4_ADDR + ReadAddr);

    /* Increment the address*/  
    ReadAddr += 2;
  }  
}
