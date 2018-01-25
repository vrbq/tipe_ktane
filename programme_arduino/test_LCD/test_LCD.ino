#include <Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 2);

int randNumber = 0;

void setup()
{
lcd.init();  // initialisation de l'afficheur
randNumber = random(0, 9);
}

void loop()
{
lcd.backlight(); // Envoi du message
lcd.setCursor(0, 0);
lcd.print("Serial number :");
lcd.setCursor(0,1);
lcd.print(randNumber);
lcd.setCursor(1,1);
lcd.print("SF85Z7");
}
