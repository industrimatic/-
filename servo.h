#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f4xx.h"                  // Device header

void Hongwai_Sensor_Init(void);
void Servo_Init(void);
void Servo_SetAngle(uint8_t i,uint16_t angle);
void Arm_Init(void);
void Arm_Catch_Move(void);
void Arm_Catch(void);
void Arm_Place_Move(void);
void Arm_Place(void);

#endif
