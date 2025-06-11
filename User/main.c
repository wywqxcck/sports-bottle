#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "DHT11.h"
#include "HW.h"
#include "HX711.h"
#include "sys.h"
#include "mpu6050.h"
#include "bsp_i2c.h"
#include "usart2.h"
#include "timer.h"
#include "gizwits_product.h"
#include "gizwits_protocol.h"
//dataPoint_t currentDataPoint;
DHT11_Data_TypeDef DHT11_Data;
uint8_t hi,hd,ti,td,z,a;
uint16_t hwds;
int water_mlnew,water_mlold,drink_ml,water_turn;
float MPU6050_attitue;
short Accel[3];
//dataPoint_t currentDataPoint;
void DHT11dushu()
{	
	if(Read_DHT11(&DHT11_Data) == SUCCESS)
		{
			  hi=DHT11_Data.humi_int;
		
				hd=DHT11_Data.humi_deci;
			
				ti=DHT11_Data.temp_int;
		
				td=DHT11_Data.temp_deci;
		}
		
}
void OLEDDHT11()
{
	
	OLED_ShowChinese(0, 0,"温度：");
	OLED_ShowChinese(0, 16,"湿度：");
	OLED_ShowChinese(0, 32,"饮水量：");
	OLED_ShowChinese(0, 48,"剩水量：");
	
	OLED_ShowNum(48,0,ti, 2,OLED_8X16);//测试代码
	OLED_ShowString(64, 0, ".", OLED_8X16);
	OLED_ShowNum(70,0,td, 2,OLED_8X16);//测试代码
	
	OLED_ShowNum(48, 16,hi, 2,OLED_8X16);//测试代码
	OLED_ShowString(64, 16, ".", OLED_8X16);//测试代码
	OLED_ShowNum(70, 16,hd, 2,OLED_8X16);//测试代码

	OLED_Update();
}
//void MPU6050_Pro()
//{
//			MPU6050ReadAcc(Accel);
//			MPU6050_attitue = Accel[2]/ 16384.0;
//			Delay_ms(50);		
//			OLED_ShowBinNum(48, 0, MPU6050_attitue, 1,OLED_8X16);	
//		OLED_Update();
//}

void ZTjianc_Pro()
{
			hwds=HW_GetData();
			MPU6050ReadAcc(Accel);
			MPU6050_attitue = Accel[2]/ 16384.0;
			Delay_ms(50);
			if((MPU6050_attitue >=1 )&&(hwds == 1)) // 盖子拧上
			{
//				  OLED_ShowString(2, 1, "humidity:");	//测试代码
					OLED_Clear();
			/*	OLED_ShowNum(48,0,2, 1,OLED_8X16);//测试代码*/
					OLED_Update();
				
			}
			else if((MPU6050_attitue >= 1)&&(hwds == 0))//盖子打开,但水杯静止放置
			{
					Get_Weight();
					water_mlnew=Weight_Shiwu*0.25;//新净水量
					Delay_ms(50);	
					water_turn=water_mlold-water_mlnew;//转移水量
					if(water_turn > 0)
					{
						drink_ml = drink_ml + water_turn;
						water_mlold = 0;
					}	
					OLEDDHT11();
					OLED_ShowNum(65, 32,drink_ml, 4,OLED_8X16);//测试代码
					OLED_ShowNum(65, 48,water_mlnew, 4,OLED_8X16);//测试代码
				
		/*OLED_ShowNum(48,16,2, 1,OLED_8X16);//测试代码*/
					OLED_Update();
				
			}
			else if((MPU6050_attitue < 1)&&(hwds  == 1))//饮水
			{
						water_mlold = water_mlnew;//测试代码
				/*OLED_ShowNum(64,0,2, 3,OLED_8X16);//测试代码
				OLED_Update();*/
			}
			else if((MPU6050_attitue < 1)&&(hwds == 0)) // 倒水
				{		
					OLEDDHT11();
					OLED_ShowNum(65, 32,drink_ml, 4,OLED_8X16);//测试代码
					OLED_ShowNum(65, 48,water_mlnew, 4,OLED_8X16);//测试代码
					/*OLED_ShowNum(48,48,7, 1,OLED_8X16);//测试代码*/
					OLED_Update();
				}
	else
	{
		OLED_Clear();	
	}	
}
int main(void)
{
/*模块初始化*/

		DHT11_GPIO_Config();
		HW_Init();			
		OLED_Init();
		Init_HX711pin();
		Get_Maopi();				//称毛皮重量
		Delay_ms(10);
		Get_Maopi();	
		i2c_GPIO_Config();
		//MPU6050初始化                                    
		MPU6050_Init();
	
		usart2_init(9600); // wifi初始化 波特率必须为9600
		TIM4_Int_Init(1000-1, 72-1);
	
		userInit();
    gizwitsInit();
		Delay_ms(500);
//	gizwitsSetMode(WIFI_SOFTAP_MODE); 
	while (1) 
	{
		DHT11dushu();
		ZTjianc_Pro(); 

		userHandle();
		gizwitsHandle((dataPoint_t *)&currentDataPoint);
	}
}
