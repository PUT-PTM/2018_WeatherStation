#include "dht11.h"

int temperature;
int humidity;
int status = 1;

void DHT11_run_config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 83999999;
	TIM_TimeBaseStructure.TIM_Prescaler = 84;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM2, ENABLE);
}

void DHT11_output_config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DHT11_input_config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DHT11_delay(int time)
{
	TIM2->CNT = 0;
	while ((TIM2->CNT) <= time);
}

int DHT11_read_data()
{
	u8 bytes [5] = { 0, 0, 0, 0, 0 };
	u8 index = 0;

	DHT11_output_config();
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	DHT11_delay(18000);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	DHT11_delay(40);
	DHT11_input_config();

	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		return -1;
	}

	DHT11_delay(80);

	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
	{
		return -1;
	}

	DHT11_delay(80);

	// read 5 bytes
	for (int i = 1; i <= 40; i++ )
	{
		// waiting for a high state
		while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1));
		DHT11_delay(35);

		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
		{
			// after 35ms logic 1
			bytes[index] <<= 1;
			bytes[index] |= 1;
		}
		else
		{
			//logic 0
			bytes[index] <<= 1;
		}

		// byte++ -> index++
		if ((i % 8) == 0)
		{
			index++;
		}

		// waiting for a low state
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1));
	}

	// check sum
	if (!(bytes[0] + bytes[1] + bytes[2] + bytes[3] == bytes[4]))
	{
		return -1;
	}

	humidity = bytes[0];
	DHT11_delay(35000);
	temperature = bytes[2];

	return 0;
}
