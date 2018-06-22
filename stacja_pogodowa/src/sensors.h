#ifndef SENSORS_H_
#define SENSORS_H_

//<<<<<<<<<<<<<<<<<<<<<<<<BMP180>>>>>>>>>>>>>>>>>>>>>>>

/*
	BMP180	STM32F4Discovery	Description
	VIN		3					Power supply
	GND		GND					Ground
	SCL		PA8					I2C3 Serial clock
	SDA		PC9 				I2C3 Serial data
*/

//<<<<<<<<<<<<<<<<<<<<<<<<DHT11>>>>>>>>>>>>>>>>>>>>>>>

/*
	DHT11	STM32F4Discovery	Description
	VCC		3V					Power supply
	GND		GND					Ground
	OUT		PA1					OneWire
*/

//<<<<<<<<<<<<<<<<<<<<<<<<HC-05>>>>>>>>>>>>>>>>>>>>>>>

/*
	HC-05	STM32F4Discovery	Description
	VCC		5V					Power supply
	GND		GND					Ground
	RxD		PC10				Receive Data
	TxD		PC11 				Transmit Data
*/

#endif /* SENSORS_H_ */
