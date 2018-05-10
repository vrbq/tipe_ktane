//de mémoire, c'est celui qui marche

#include <Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 2);

int randNumber = 0;

void setup()
{
lcd.init();  // initialisation de l'afficheur
lcd.backlight(); // Envoi du message
lcd.setCursor(0, 0);
lcd.print("Serial number :");
lcd.setCursor(0,1);
lcd.print("BITE");
}

void loop()
{

}
