#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int buttonPin = 10;     
const int buttonPin2 = 6;     
  int buttonState = 0;         
int buttonState2 = 0;
   void setup() {
     lcd.begin(16, 2);
     lcd.print("TEST");   
   }
  void loop() {   
buttonState = digitalRead(buttonPin);
buttonState2 = digitalRead(buttonPin2);
pinMode(buttonPin, INPUT);
pinMode(buttonPin2, INPUT);
if (buttonState == HIGH) {
  delay(500); //on évite de sauter les menus d'un coup
   lcd.clear(); 
  lcd.print("menu #1");/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (buttonState2 == HIGH){
      delay(300);
      lcd.clear();
      lcd.print("SOUS menu 1");   
buttonState = digitalRead(buttonPin);
buttonState2 = digitalRead(buttonPin2);
if (buttonState == HIGH) {
  delay(500); //on évite de sauter les menus d'un coup
   lcd.clear(); 
   lcd.print("menu #2");
  if (buttonState2 == HIGH){
      delay(500);
      lcd.clear();
      lcd.print("SOUS menu 2");   
  }
  }
  }
  }
  }
