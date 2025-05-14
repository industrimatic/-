#include "servo.h"

void Hongwai_Sensor_Init(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //传感器对应引脚PA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	 
} 


void Servo_Init(void)
{
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 
	GPIO_InitTypeDef GPIO_InitStructure; 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_Init(GPIOE,&GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
	TIM_TimeBaseStructure.TIM_Prescaler=84-1; 
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_Period=20000-1; 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);
	
	TIM_TimeBaseStructure.TIM_Prescaler=168-1; 
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_Period=20000-1; 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;  
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC1Init(TIM12, &TIM_OCInitStructure); 
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC2Init(TIM12, &TIM_OCInitStructure); 
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC1Init(TIM9, &TIM_OCInitStructure); 

	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM12, TIM_OCPreload_Enable); 
	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable); 

	TIM_Cmd(TIM12, ENABLE); 
	TIM_Cmd(TIM9, ENABLE); 
	
}
//头PB14 == tim12cp1 ;底PB15 == tim12cp2;中间PE5 == tim9cp1;
//1 for 头; 2for中间; 3for底
void Servo_SetAngle(uint8_t i,uint16_t angle)
{

	if(i == 1)
	{
		TIM_SetCompare1(TIM12,2000*angle/180 + 500); 
	}
	else if(i == 2)
	{
		TIM_SetCompare1(TIM9 ,2000*angle/270 + 500); 
	}
	else if(i == 3)
	{
		TIM_SetCompare2(TIM12,2000*angle/180 + 500); 
	}
}

void Arm_Init(void)
{
	Servo_SetAngle(1,90);
	Servo_SetAngle(2,130);
	Servo_SetAngle(3,0);
}
void Arm_Catch_Move(void)
{
	
	Servo_SetAngle(2,50);
	Servo_SetAngle(3,60);
}
void Arm_Catch(void)
{
	Servo_SetAngle(1,20);
}

void Arm_Place_Move(void)
{
	Servo_SetAngle(2,220);
	Servo_SetAngle(3,160);
}
void Arm_Place(void)
{
	Servo_SetAngle(1,90);
}
