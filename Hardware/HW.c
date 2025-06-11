#include "HW.h"

/*****************辰哥单片机设计******************
											STM32
 * 文件			:	光电红外传感器c文件                   
 * 版本			: V1.0
 * 日期			: 2024.8.12
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥

**********************BEGIN***********************/

void HW_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd (HW_GPIO_CLK, ENABLE );	// 打开连接 传感器DO 的单片机引脚端口时钟
		GPIO_InitStructure.GPIO_Pin = HW_GPIO_PIN;			// 配置连接 传感器DO 的单片机引脚模式
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// 设置为上拉输入
		
		GPIO_Init(HW_GPIO_PORT, &GPIO_InitStructure);				// 初始化 
	
}

uint16_t HW_GetData(void)//读数返回值
{
	uint16_t tempData;
	tempData = !GPIO_ReadInputDataBit(HW_GPIO_PORT, HW_GPIO_PIN);
	return tempData;
}



