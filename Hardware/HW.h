#ifndef __HW_H
#define	__HW_H
#include "stm32f10x.h"
#include "adcx.h"
#include "delay.h"
#include "math.h"

/*****************���絥Ƭ�����******************
											STM32
 * �ļ�			:	�����⴫����h�ļ�                   
 * �汾			: V1.0
 * ����			: 2024.8.12
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	������							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/


/***************�����Լ��������****************/
// HW GPIO�궨��

#define		HW_GPIO_CLK								RCC_APB2Periph_GPIOB
#define 	HW_GPIO_PORT							GPIOB
#define 	HW_GPIO_PIN								GPIO_Pin_5			

/*********************END**********************/


void HW_Init(void);
uint16_t HW_GetData(void);

#endif /* __ADC_H */

