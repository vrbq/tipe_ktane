#include <Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 2);
LiquidCrystal_I2C lcd2(0x26, 20, 2);

int randNumber = 0;

void setup()
{
lcd.init();  // initialisation de l'afficheur
lcd2.init();  // initialisation de l'afficheur
randNumber = random(0, 9);
}

void loop()
{
lcd.backlight(); // Envoi du message
lcd.setCursor(0, 0);
lcd.print("TEST1");
lcd.setCursor(0,1);
lcd.print("TEST2");

lcd2.backlight(); // Envoi du message
lcd2.setCursor(0, 0);
lcd2.print("TEST3");
lcd2.setCursor(0,1);
lcd2.print("TEST4");
}

// Nota Bene : pour faire fonctionner 2 LCD
// Il faut connecter les deux au breadboard, avec le SDA et SCL qui sont amenés (en série !)
