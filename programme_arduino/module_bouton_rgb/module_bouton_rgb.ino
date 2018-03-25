//Library Multi Button Analog
#include <AnalogMultiButton.h>
//Library LCD
#include <Wire.h>
#include<LiquidCrystal_I2C.h>

#include "serial.h"

LiquidCrystal_I2C lcd(0x27, 20, 2);
long randNumber = 0;
long partie_une = 0;
long partie_deux = 0;
long serial = 0;

/////////////////////////////// Variables boutons ///////////////////////////////
const int BUTTONS_PIN = A1;
const int BUTTONS_TOTAL = 1;
const int BUTTONS_VALUES[BUTTONS_TOTAL] = {512};
const int BUTTON_ONE = 0;
AnalogMultiButton buttons(BUTTONS_PIN, BUTTONS_TOTAL, BUTTONS_VALUES);

/////////////////////////////// VARAIBLES LED RGB ///////////////////////////////
//on commence en spécifiant les broches vont être utilisées pour chacune des couleurs:
int redPin = 4;
int greenPin = 3;
int bluePin = 2;
//#define COMMON_ANODE

void setup() {
Serial.begin(9600);
randomSeed(analogRead(0)); //Il semble que cette fonction marche sur due, peut être pas sur uno : dans ce cas, voir https://github.com/sebnil/DueFlashStorage/blob/master/examples/DueFlashStorageExample/DueFlashStorageExample.ino

//1ere partie
partie_une = random(0, 100);
randomSeed(analogRead(1));
partie_deux = random(0, 100);
serial = partie_une + partie_deux;
Serial.println(partie_une);
Serial.println(partie_une);

pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);
}


void loop() {
buttons.update();
//Serial.println(analogRead(BUTTONS_PIN)); // c'est pour voir la valeur de la résistance

if (randNumber < 5){
  setColor(10, 0, 0); // rouge
}
else{
  setColor(0, 20, 0); // vert
}

}








/////////////////////////////// FONCTIONS ///////////////////////////////
void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
red = 255 - red;
green = 255 - green;
blue = 255 - blue;
#endif
analogWrite(redPin, red);
analogWrite(greenPin, green);
analogWrite(bluePin, blue);
}





