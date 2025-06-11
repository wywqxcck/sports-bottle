/************************************************************************************
						
*************************************************************************************/
#include "HX711.h"
#include "Delay.h"
u32 HX711_Buffer;
u32 Weight_Maopi;
s32 Weight_Shiwu;
u8 Flag_Error = 0;

//У׼����
//��Ϊ��ͬ�Ĵ������������߲��Ǻ�һ�£���ˣ�ÿһ����������Ҫ�������������������ʹ����ֵ��׼ȷ��
//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
//������Գ���������ƫСʱ����С����ֵ��
//��ֵ����ΪС��
#define GapValue 106.5


void Init_HX711pin(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PF�˿�ʱ��

	//HX711_SCK
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;				 // �˿�����
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStruct);					 //�����趨������ʼ��GPIOB
	
	//HX711_DOUT
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOB, &GPIO_InitStruct);  
	
	GPIO_SetBits(GPIOB,GPIO_Pin_0);					//��ʼ������Ϊ0
}



//****************************************************
//��ȡHX711
//****************************************************
u32 HX711_Read(void)	//����128
{
	unsigned long count; 
	unsigned char i; 
  	HX711_DOUT=1; 
	Delay_us(1);
  	HX711_SCK=0; 
  	count=0; 
  	while(HX711_DOUT); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK=1; 
	  	count=count<<1; 
		Delay_us(1);
		HX711_SCK=0; 
	  	if(HX711_DOUT)
			count++; 
		Delay_us(1);
	} 
 	HX711_SCK=1; 
    count=count^0x800000;//��25�������½�����ʱ��ת������
	Delay_us(1);
	HX711_SCK=0;  
	return(count);
}

//****************************************************
//��ȡëƤ����
//****************************************************
void Get_Maopi(void)
{
	Weight_Maopi = HX711_Read();	
} 

//****************************************************
//����
//****************************************************
void Get_Weight(void)
{
	HX711_Buffer = HX711_Read();
	if(HX711_Buffer > Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//��ȡʵ���AD������ֵ��
	
		Weight_Shiwu = (s32)((float)Weight_Shiwu/GapValue); 	//����ʵ���ʵ������
																		//��Ϊ��ͬ�Ĵ������������߲�һ������ˣ�ÿһ����������Ҫ���������GapValue���������
																		//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
																		//������Գ���������ƫСʱ����С����ֵ��
	}	
}
