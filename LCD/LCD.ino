/*
Arduino 2x16 LCD - Detect Buttons
modified on 18 Feb 2019
by Saeed Hosseini @ Electropeak
https://electropeak.com/learn/
*/

#include <LiquidCrystal.h>

//LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 

const int pin_BL = 10; 

LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

void setup() {
  
  lcd.begin(16, 2);


  lcd.setCursor(0,0);
  lcd.print("Depletion:");

}

void loop() {
  int x;
  x = analogRead (0);
  if (x < 60) {
    lcd.setCursor(11,0);
    lcd.print ("0 % ");
    lcd.setCursor(0,1);
    lcd.print ("                ");
  }
  else if (x < 200) {
    lcd.setCursor(11,0);
    lcd.print ("50 %    ");
    lcd.setCursor(0,1);
    lcd.print ("                ");
  }
  else if (x < 400){
    lcd.setCursor(11,0);
    lcd.print ("66 %  ");
    lcd.setCursor(0,1);
    lcd.print ("Change canister");
  }
  else if (x < 600){
    lcd.setCursor(11,0);
    lcd.print ("80 %  ");
    lcd.setCursor(0,1);
    lcd.print ("Change canister");
  }
  else if (x < 800){
    lcd.setCursor(11,0);
    lcd.print ("100 %");
    lcd.setCursor(0,1);
    lcd.print ("Change canister");
    
  }
}
