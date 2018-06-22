#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_i2c.h"
#include "dht11.h"
#include "bmp180.h"
#include "tim4.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_bmp180.h"

extern int temperature;
extern int humidity;
extern int pressure;

char data[5];

void clearTab()
{
	for(int i = 0; i< 5;i++)
	{
		data[i]=' ';
	}
}

void sendBluetoothString()
{
	for(int i=0;i<5;i++)
	{
		if(data[i]!=52 || data[i]!=32)
		{
		sendBluetoothChar(data[i]);
		}
		else break;
	}
	sendBluetoothChar('\n');
}

void sendBluetoothChar(char item)
{
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET){}

	USART_SendData(USART3, item);

	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
}

void int_to_char(int measure)
{
	int pom = measure;
	int len = 0;
	while (pom > 0)
	{
		len++;
		pom /= 10;
	}

	while (measure > 0)
	{
		pom = measure % 10+48;
		measure /= 10;
		data[--len] = pom;
	}
}

void send_Temperature1()
{
	clearTab();
	char tab[7] = "TEMP : ";
	for(int i=0;i<7;i++)
		{
			if(tab[i]!=52 || tab[i]!=32)
			{
				sendBluetoothChar(tab[i]);
			}
		}
}

void send_Humidity()
{
	clearTab();
	char tab[7] = "HUMI : ";
	for(int i=0;i<7;i++)
		{
			if(tab[i]!=52 || tab[i]!=32)
			{
				sendBluetoothChar(tab[i]);
			}
		}
}

void send_Pressure()
{
	clearTab();
	char tab[7] = "PRES : ";
	for(int i=0;i<7;i++)
		{
			if(tab[i]!=52 || tab[i]!=32)
			{
				sendBluetoothChar(tab[i]);
			}
		}
}

int main(void)
{
	SystemInit();

	//configs
	DHT11_run_config();
	TIM4_config();
	TIM4_interrupt_config();
	TIM_Cmd(TIM4, ENABLE);
	TM_DELAY_Init();
	BMP180_check_status();

	 for(;;)
	    {
		DHT11_read_data();
		BMP180_read_data();

		Delayms(5000);

		send_Temperature1();
		int_to_char(temperature);
		sendBluetoothString(data);

		send_Pressure();
		int_to_char(pressure);
		sendBluetoothString(pressure);

		send_Humidity();
		int_to_char(humidity);
		sendBluetoothString(data);

		sendBluetoothChar('\n');
	    }
}




