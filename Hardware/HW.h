#ifndef __HW_H
#define	__HW_H
#include "stm32f10x.h"
#include "adcx.h"
#include "delay.h"
#include "math.h"

/*****************辰哥单片机设计******************
											STM32
 * 文件			:	光电红外传感器h文件                   
 * 版本			: V1.0
 * 日期			: 2024.8.12
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥

**********************BEGIN***********************/


/***************根据自己需求更改****************/
// HW GPIO宏定义

#define		HW_GPIO_CLK								RCC_APB2Periph_GPIOB
#define 	HW_GPIO_PORT							GPIOB
#define 	HW_GPIO_PIN								GPIO_Pin_5			

/*********************END**********************/


void HW_Init(void);
uint16_t HW_GetData(void);

#endif /* __ADC_H */

