#include "HW.h"

/*****************���絥Ƭ�����******************
											STM32
 * �ļ�			:	�����⴫����c�ļ�                   
 * �汾			: V1.0
 * ����			: 2024.8.12
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	������							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/

void HW_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd (HW_GPIO_CLK, ENABLE );	// ������ ������DO �ĵ�Ƭ�����Ŷ˿�ʱ��
		GPIO_InitStructure.GPIO_Pin = HW_GPIO_PIN;			// �������� ������DO �ĵ�Ƭ������ģʽ
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// ����Ϊ��������
		
		GPIO_Init(HW_GPIO_PORT, &GPIO_InitStructure);				// ��ʼ�� 
	
}

uint16_t HW_GetData(void)//��������ֵ
{
	uint16_t tempData;
	tempData = !GPIO_ReadInputDataBit(HW_GPIO_PORT, HW_GPIO_PIN);
	return tempData;
}



