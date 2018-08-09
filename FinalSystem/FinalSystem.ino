//Created by Parth Sareen
//Home/Office sensor module developed for SAP Labs Toronto Office
//Read documentation on wiring, libraries and other important things you should know.
//Feel free to contact author at parthsareen00@gmail.com

#include <Wire.h>//i2c library
#include "Adafruit_HTU21DF.h"
#include <BH1750FVI.h>//use instructables to get library or use attached library
#include "SparkFunCCS811.h"
#include <math.h>//math library for doing conversion to dB

int Humidity = 0x40;// I2C Address

#define ENV A0//Envelope read for sound amplitude
#define CCS811_ADDR 0x5B //Default I2C Address for VOC
#define Temperature_val 0xF3;// adding the temp hex
#define Humidity_val 0xF5;// adding hum hex

Adafruit_HTU21DF htu = Adafruit_HTU21DF();// add the sensor
BH1750FVI LightSensor;// library adds light sensor
CCS811 mySensor(CCS811_ADDR); //library add the VOC


void setup() {
  Serial.begin(115200);  
  
  LightSensor.begin(); //start light sensor
 
  LightSensor.SetAddress(0x23);//Address 0x23 addr not connected, address changes if you connect addr, check instructables guide if you want to change.
  LightSensor.SetMode(Continuous_H_resolution_Mode);// reccomended mode for light sensor
  
  //Tell user program has begun
  Serial.println(" ");
  Serial.println("Initialized");

   CCS811Core::status returnCode = mySensor.begin();
  if (returnCode != CCS811Core::SENSOR_SUCCESS)
  {
    Serial.println(".begin() returned with an error.");
    while (1); //Hang if there was a problem.
  }
  else {
    Serial.println("VOC Connected");
    }


  //Checks if sensor is connected
  if (!htu.begin()) {
    Serial.println("Couldn't find humidity sensor!");
    while (1);
  }

}

void loop() {
  //light sensor
  uint16_t lux = LightSensor.GetLightIntensity();// Get Lux value
  Serial.print("Light: ");//Print the below
  Serial.print(lux);
  Serial.println(" lux");
  delay(100);
  
  //Prints temperature 
  Serial.print("Temp: "); Serial.print(htu.readTemperature());//print temp and hum
  Serial.print("\t\tHum: "); Serial.println(htu.readHumidity());
  delay(100);
  
  int envValue; //value for amplitude of sound

  //check env value and 
  envValue = analogRead(ENV);//assign amplitude value
  Serial.print("Sound Status: ");
  Serial.print(20*log(envValue)*0.7);//0.7 is adjustment factor for dShop
  Serial.print(" dB");
  
  if(envValue <= 10){ //can possibly be adjusted for decibels and give true reading, module is extremely sensitive
    Serial.println("\t\tQuiet");
    }
  else if(envValue<70){
    Serial.println("\t\tModerate");
    }
  else if (envValue >= 70){
    Serial.println("\t\tLoud");
    }
  delay(100);
 //Check to see if data is ready with .dataAvailable() for VOC
  if (mySensor.dataAvailable())
  {
    //If so, have the sensor read and calculate the results.
    mySensor.readAlgorithmResults();

    Serial.print("CO2 (ppm)[");
    //Returns calculated CO2 reading
    Serial.print(mySensor.getCO2());
    Serial.print("] tVOC (ppb)[");
    //Returns calculated Total Volatile Organic Compounds reading
    Serial.print(mySensor.getTVOC());
    Serial.print("] millis[");
    //Simply the time since program start
    Serial.print(millis());
    Serial.print("]");
    Serial.println(" ");
  }
  Serial.print("\n");
  delay(3000);
}
