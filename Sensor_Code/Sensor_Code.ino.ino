#include <Wire.h> 

#include "SparkFunMPL3115A2.h"


int mq3_analogPin = A0;   //A0 is the analog 

#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
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
