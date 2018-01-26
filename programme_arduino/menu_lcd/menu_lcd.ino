#include <Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 2);

int buttonState = 0;
const int button = 24;
const int led = 26;                   

void setup() {
pinMode(button, INPUT);
pinMode(led, OUTPUT);
lcd.init();  // initialisation de l'afficheur
lcd.print("TEST");   
   }
   
void loop() {   
  
buttonState = digitalRead(button);
if (buttonState == LOW) {
  digitalWrite(led, HIGH);
  lcd.clear(); 
  lcd.print("Pulp Fiction");   

digitalWrite(led, LOW);
buttonState = digitalRead(button);
if (buttonState == LOW) {
  digitalWrite(led, HIGH);
   lcd.clear(); 
   lcd.print("Kill Bill");  
  }
  }
  }
