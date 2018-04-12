//Library Multi Button Analog
#include <AnalogMultiButton.h>

//Library LCD
#include <Wire.h>
#include<LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 20, 2);
long randNumber = 0;

// define the pin you want to use
const int BUTTONS_PIN = A1;

// set how many buttons you have connected
const int BUTTONS_TOTAL = 1;

// find out what the value of analogRead is when you press each of your buttons and put them in this array
// you can find this out by putting Serial.println(analogRead(BUTTONS_PIN)); in your loop() and opening the serial monitor to see the values
// make sure they are in order of smallest to largest
const int BUTTONS_VALUES[BUTTONS_TOTAL] = {512};

// you can also define constants for each of your buttons, which makes your code easier to read
// define these in the same order as the numbers in your BUTTONS_VALUES array, so whichever button has the smallest analogRead() number should come first
const int BUTTON_ONE = 0;

void setup() {
  randomSeed(analogRead(0)); //Il semble que cette fonction marche sur due, par essentiellement sur uno : dans ce cas, voir https://github.com/sebnil/DueFlashStorage/blob/master/examples/DueFlashStorageExample/DueFlashStorageExample.ino
  Serial.begin(9600);
  lcd.init();  // initialisation de l'afficheur
  randNumber = random(0, 10);
  lcd.backlight(); // Envoi du message
  lcd.setCursor(0, 0);
  lcd.print("Serial number :");
  lcd.setCursor(0,1);
  lcd.print(randNumber);
  lcd.setCursor(1,1);
  lcd.print("SF85RS7");
}

void loop() {
  //Serial.println(analogRead(BUTTONS_PIN)); // c'est pour voir la valeur de la résistance
  
}
