#ifndef __TEST_IRDA_H
#define __TEST_IRDA_H

#include "stm32f4xx.h"
#include "BSP_DebugUART.h"
#include "BSP_Delay.h"
#include "Queue.h"
#include "BSP_Delay.h"
#include "BSP_ADConverter.h"

#define READ_TIMES 10 	//读取次数
#define LOST_VAL 2	  	//丢弃值

void Test_IRDA(void);

#endif
