/*
Nathaniel Talbot
GE 1502 Cornerstone of Engineering 2
Northeaster University, Boston, MA
2017
*/

//This code is a modification of the original sensor code to include the IR sensor and servo motors for the robot


//INCLUDED LIBRARIES
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <Wire.h> //I2C for sensors
#include "SparkFunMPL3115A2.h"  //Pressure Sensor
#include "SparkFun_Si7021_Breakout_Library.h" //Humidity Sensor


#include <LiquidCrystal.h>  //library for LCD

#include <Servo.h>  //library for servo motors to move the robot

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

//declare servo objects
Servo servo_R;
Servo servo_L;

// GLOBAL VARIABLES
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
long lastSecond;  //Millisecond counter to see when a second goes by





void setup() {
  

  //Blue and green status LEDs
  pinMode(STAT_BLUE, OUTPUT); 
  pinMode(STAT_GREEN, OUTPUT); 

  pinMode(REFERENCE_3V3, INPUT);  //Reference voltage input
  pinMode(LIGHT, INPUT);  //Light Sensor input

  //Pressure Sensor Configuration
  myPressure.begin(); // Get sensor online
  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags

  //Configure humidity sensor
  myHumidity.begin();

  //Set up time readout
  lastSecond = millis();

  //Setup for the LCD Readout (Temporary for the 3/26 iteration of the prototype)

  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Welcome!");
  delay(1000);
}

//Loop function reads out alcohol, temperature, humidity, pressure, light level readings onto LCD
void loop() {

  //Read out Alcohol Level
  int mq3_value = analogRead(mq3_analogPin);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Alcohol Level");

  lcd.setCursor(0,1);

  lcd.print(mq3_value);

  delay(4000);

  //Read out Temperature
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperature");

  lcd.setCursor(0,1);
  float temp_h = myHumidity.getTempF();
  lcd.print(temp_h, 2);
  lcd.print(" F");
  
  delay(4000);

  //Read out humidity
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humidity:");
  
  float humidity = myHumidity.getRH();
  lcd.setCursor(0,1);
  lcd.print(humidity);
  lcd.print("%");
  
  delay(4000);

  //Read out pressure
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pressure:");

  lcd.setCursor(0,1);
  float pressure = myPressure.readPressure();
  lcd.print(pressure);
  lcd.print(" Pa");

  delay(4000);
  
  //Read out light level
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Light Level");

  lcd.setCursor(0,1);
  float light_lvl = get_light_level();
  lcd.print(light_lvl);
  lcd.print(" V");
  
  delay(4000);

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

