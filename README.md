# PIR_Alarm

# Overview 
A simple alarm that should scare a burglar.

# Description 
The project is supported by means of the Pin Pad connected to the stm32 PCB. All necessary information is displayed in Polish. The alarm 
detects the burglar via the PIR motion sensor.

# Tools  
STM32F4 Discovery board
LCD display 2x16 characters with Driver compatible with HD44780
RGB diode
12 Button 3x4 Keypad
PIR Motion Detector
Buzzer
potentiometer

# How to run 
Fetch our project, and run it using System Workbench for STM32. Upload program to STM32F4 Discovery and connect all needed pins. Then follow the steps listed on the display.

PinPad
Pin 1 = column 2 = PE12
Pin 2 = row 1 = PE7
Pin 3 = column 1 = PE11
Pin 4 = row 4 = PE10 - fioletowy
Pin 5 = column 3 = PE13
Pin 6 = row 3 = PE9
Pin 7 = row 2 = PE8

LCD:
1 - GND - GND
2 - VCC - +5V
3 - V0 - potentiometer
4 - RS -PB2
5 - RW - GND
6 - E - PB7
7 - D0 - unused
8 - D1 - unused
9 - D2 - unused
10 - D3 - unused
11 - D4 - PC12
12 - DP - PC13
13 - D6 - PB12
14 - D7 - PB13
15 - A - +3V
16 - K - GND

RGB Diode:
- R: PC6
- G: PC8
- B: PC9
- GND: GND

Potentiometer:
Left - 3.3V 
Middle - V0 LCD
Right - GND

Buzzer:
+ -PB14
- - GND

# How to compile 
Just copy Project and compile. 

# Future improvements 
We are going to change Keypad.

# Attributions 
We used HAL library 15- HD44780 for LCD Display.

Link to HAL libraries: https://stm32f4-discovery.net/2015/07/all-stm32-hal-libraries/ 
# License  MIT License
# Credits 
Created by:
Cezary Waligóra
Jędrzej Magdans

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.
Supervisor: Marek Kraft

