#include "stm32f4xx.h"
#include "delay.h"
#include "servo.h"
//1 for Õ∑; 2for÷–º‰; 3forµÕ
int main(void)
{ 
	delay_init(168);
	Hongwai_Sensor_Init();
	Servo_Init();
	Arm_Init();
	
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == RESET)
		{
			Arm_Catch_Move();
			delay_ms(1000);
			Arm_Catch();
			delay_ms(2000);
			Arm_Place_Move();
			delay_ms(1000);
			Arm_Place();
			delay_ms(2000);
		}
		else
		{
			Arm_Init();
		}
	}
}
