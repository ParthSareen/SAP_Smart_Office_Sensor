# SAP_Smart_Office_Sensor
# Documentation for Office IoT Sensor Project

All code and documentation are written by Parth Sareen
For questions and concerns, contact parthsareen00@gmail.com

The code and libraries are written for the Adafruit Huzzah Feather ESP 8266.
Libraries are found on: https://drive.google.com/drive/folders/1CyhYKxWswg9NYkEvjxO64VX-nQSEW3ly?usp=sharing 
<br> Please do not edit unnecessarily </br> 

# Attention
Code and fritzing files explain how to connect sensors to the Feather.
Please only use libraries attached to the project. They have been modified by me to work with the Feather. 
The Feather uses I2C to communicate with the different sensors. The attached sensors are sound, light, temperature & humidity and a VOC sensor.  


When done connecting everything, run I2C Scanner to make sure everything is attached. The addresses will be printed for the attached devices. There should be three address. If need be, modify the code to match the sensor addresses. 
The addresses identified by my feather are:
0x23: Light
0x5B: VOC
0x40: Humidity and Temperature.


Humidity and Temperature internal addresses are given in the code. If need be, refer to the datasheet that can be found by googling the sensor’s model number (HTU21D-F).

The VOC sensor needs to run for a recommended 48 hours before it starts giving relatively accurate readings. Please scrap data for first 48 hours.

Adjust the sound sensor and if statements to realistically map the values to the environment. The dB conversion also needs to be adjusted to the environment and realistic dB compared to already determined values. This can be done by measuring white noise in the room and accounting for it. Then, map values and create different threshold values for quiet, moderate and loud.
The entire project was shifted out of SAP’s HANA to make sure all components are functioning properly, as well as adding sensors and fixing a step up and down issue with voltage and logic. 

Further developments to the project should include linking the data to SAP HANA and creating a web app so that the data is readily available to the public/employees.

The data can also be more accurate if the Humidity module shares temperature information to the VOC module. This can be accomplished by using I2C.

Demo of the protype can be found on: https://drive.google.com/file/d/1zggMTVNAm3fkhvnvfvVVdvFDZF9zh9oH/view?usp=sharing 
