/*
Nathaniel Talbot
GE 1502 Cornerstone of Engineering 2
Northeaster University, Boston, MA
2017


*/
//INCLUDED LIBRARIES
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <Wire.h> //I2C for sensors
#include "SparkFunMPL3115A2.h"  //Pressure Sensor
#include "SparkFun_Si7021_Breakout_Library.h"   //
//LCD
#include <LiquidCrystal.h>

MPL3115A2 myPressure;   //instance of pressure sensor
Weather myHumidity;     //instance of humidity sensor

//ALL PIN DEFINITIONS
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
const byte STAT_BLUE = 7;
const byte STAT_GREEN = 8;

const byte REFERENCE_3V3 = A3;
const byte LIGHT = A1;

int mq3_analogPin = A0;   //A0 is the analog pin for the MQ-3 Sensor

LiquidCrystal lcd(12,11,5,4,3,2);

// GLOBAL VARIABLES
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
long lastSecond;  //Millisecond counter to see when a second goes by





void setup() {
  
  //Setup 
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Welcome!")
  delay(1000);
  lcd.clear();
}

void loop() {

  //Read out Alcohol Level
  int mq3_value = analogRead(mq3_analogPin);
  lcd.setCursor(0,0);
  lcd.print("Alcohol Level");

  lcd.setCursor(0,1);

  lcd.print(mq3_value);

  delay(4000);

  //Read out Temperature
  lcd.setCursor(0,0);
  lcd.print("Temperature");

  //Read out Pressure

 

  

}

//FUNCTION FOR THE LIGHT LEVEL SENSOR

float get_light_level()
{
  float operatingVoltage = analogRead(REFERENCE_3V3);

  float lightSensor = analogRead(LIGHT);

  operatingVoltage = 3.3 / operatingVoltage; //The reference voltage is 3.3V

  lightSensor = operatingVoltage * lightSensor;

  return (lightSensor);
}

