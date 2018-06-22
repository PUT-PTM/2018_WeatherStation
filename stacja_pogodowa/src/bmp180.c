#include "tm_stm32f4_bmp180.h"
#include "tm_stm32f4_delay.h"

TM_BMP180_t BMP180_Data;

int bmp_temperature;
int pressure;

void BMP180_check_status()
{
	if (TM_BMP180_Init(&BMP180_Data) != TM_BMP180_Result_Ok)
	{
		// error
		while (1);
	}
}

void BMP180_read_data()
{
	TM_BMP180_StartTemperature(&BMP180_Data);
	Delay(BMP180_Data.Delay);
	TM_BMP180_ReadTemperature(&BMP180_Data);

	TM_BMP180_StartPressure(&BMP180_Data, TM_BMP180_Oversampling_UltraHighResolution);
	Delay(BMP180_Data.Delay);
	TM_BMP180_ReadPressure(&BMP180_Data);

	Delayms(1000);

	bmp_temperature = BMP180_Data.Temperature;
	pressure = BMP180_Data.Pressure / 100;
}
