/*
Nathaniel Talbot
GE 1502 Cornerstone of Engineering 2
Northeastern University, Boston, MA
2017
*/

//This code is a modification of the original sensor code to include the IR sensor and servo motors for the robot

//INCLUDED LIBRARIES
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <Wire.h> //I2C for sensors
#include "SparkFunMPL3115A2.h"  //Pressure Sensor
#include "SparkFun_Si7021_Breakout_Library.h" //Humidity Sensor

//#include <LiquidCrystal.h>  //library for LCD

#include <Servo.h>  //library for servo motors to move the robot

//Libraties for IR Sensor
#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

#include <SD.h>

MPL3115A2 myPressure;   //instance of pressure sensor
Weather myHumidity;     //instance of humidity sensor

const byte REFERENCE_3V3 = A3;
const byte LIGHT = A1;

int mq3_analogPin = A0;   //A0 is the analog pin for the MQ-3 Sensor

int RECV_PIN = 9;     //Pin for IR Sensor

//declare servo objects
Servo servo_R;
Servo servo_L;
Servo scoop;

//Set up IR Receiver
IRrecv irrecv(RECV_PIN);
decode_results results;


// GLOBAL VARIABLES
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
long previousMillis = 0;  //Stores last time sensors were used
long interval = 10000;  //interval for reading data, 10 seconds

//IR Values for RCA Remote
FWD 2064   //IR value for #2, moves rover forward
LEFT 16     //IR value for #1, turns rover left
RIGHT 2040     //IR value for #3, turns rover right
REV 528    //IR value for #5, reverses rover
SCOOP_UP 3600   //IR value for #8, moves scoop up
SCOOP_DOWN 2320 //IR value for #0, moves scoop down

void setup() {

  //Blue and green status LEDs
  //pinMode(STAT_BLUE, OUTPUT); 
  //pinMode(STAT_GREEN, OUTPUT); 

  pinMode(REFERENCE_3V3, INPUT);  //Reference voltage input
  pinMode(LIGHT, INPUT);  //Light Sensor input

  //Pressure Sensor Configuration
  myPressure.begin(); // Get sensor online
  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags

  //Configure humidity sensor
  myHumidity.begin();

  //Set up IR Receiver
  irrecv.enableIRIn(); 
  
  //Set up servo motors to pins
  servo_R.attach(6);
  servo_L.attach(7);
  scoop.attach(8);

  //set up pin 10 as data output to the SD Card
  pinmode(10, OUTPUT);

  fid = SD.open("data.txt", FILE_WRITE);
}

//Loop function reads out alcohol, temperature, humidity, pressure, light level readings onto LCD
void loop() {

  unsigned long currentMillis = millis();   //read current time

  //if statement 
  if (currentMillis - previousMillis > interval) {
    if (fid) {
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
  }

  if (irrecv.decode(&results)) {
    switch (results.value){
      //forward
       case FWD:
       servo_R.write (180);      
       servo_L.write (0);
    
       break;
      //left
       case LEFT:
       servo_R.write (0);      
       servo_L.write (180);

       break;
      //right
       case RIGHT:
       servo_R.write (0);      
       servo_L.write (0);

       break;
      //reverse
       case REV:
       servo_R.write (180);      
       servo_L.write (180);

       break;
       //move scoop up
       case SCOOP_UP:
       servo_R.write (90);      
       servo_L.write (90);

       break;
       //move scoop down
       case SCOOP_DOWN:
       //servo moves up
       break;
    } 
      irrecv.resume(); // Receive the next value
  }

}

//Function for the light level sensor

float get_light_level()
{
  float operatingVoltage = analogRead(REFERENCE_3V3);

  float lightSensor = analogRead(LIGHT);

  operatingVoltage = 3.3 / operatingVoltage; //The reference voltage is 3.3V

  lightSensor = operatingVoltage * lightSensor;

  return (lightSensor);
}

