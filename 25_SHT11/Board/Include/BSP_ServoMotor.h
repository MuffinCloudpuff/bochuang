#ifndef __BSP_SERVOMOTOR_H
#define __BSP_SERVOMOTOR_H

#include "stm32f4xx.h"

#define SERVOMOTOR_CENTER         1500

#define SERVOMOTOR_DIV            1           //1us  ∂‘”¶0.09∂»
#define SERVOMOTOR_LEFT_MAX       2500
#define SERVOMOTOR_RIGHT_MAX      500

void BSP_ServoMotor_Init(void);

void BSP_ServoMotor1_Set(int ServoMotorValue);
//void BSP_ServoMotor2_Set(int ServoMotorValue);
void BSP_ServoMotor3_Set(int ServoMotorValue);
//void BSP_ServoMotor4_Set(int ServoMotorValue);
//void BSP_ServoMotor5_Set(int ServoMotorValue);
void BSP_ServoMotor6_Set(int ServoMotorValue);
//void BSP_ServoMotor7_Set(int ServoMotorValue);
//void BSP_ServoMotor8_Set(int ServoMotorValue);

#endif
