# 2018_WeatherStation

Overview:
Our project is a project of a weather station, which allows us to measure basic weather conditions (temperature, humidity, pressure). Moreover read data is transmited to mobile phone via bluetooth.

Description:
We used "Serial Bluetooth Terminal" application to check transmited data.

Components:
-BMP180 - pressure and temperature sensor;
-DHT11 - humidity and temperature sensor;
-HC-05 - full-duplex wireless bluetooth module;
-STM32F4DISCOVERY - high performance microcontroller.

How to run:
Read sensors.h header, which has descripted all pins. Plug in pins to the modules. Download bluetooth application terminal. Compile project and flash program into the board. Data will be read autonomously.

Future improvements:
- Graphical application on Android OS, instead of using terminal
- More sensors such as: light sensor, carbon monoxide detector


License:
Distributed under MIT license

Credits:
-Kamil Zieliñski,
-Marcin Stasiak.

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.

Supervisor: Adam Bondyra.
