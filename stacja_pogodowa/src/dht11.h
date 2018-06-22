#ifndef DHT11_H_
#define DHT11_H_

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"

void DHT11_run_config();
void DHT11_output_config();	//GPIOA
void DHT11_input_config();	//GPIOA
void DHT11_delay(int time);
int DHT11_read_data();

#endif /* DHT11_H_ */
