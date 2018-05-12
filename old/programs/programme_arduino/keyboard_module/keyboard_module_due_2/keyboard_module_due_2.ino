#include <AnalogMultiButton.h>
#include "KeyboardModule.h"
#include "CustomRandom.h"

//#define DEBUG

const int BUTTONS_PIN = A0;
const int SPEAKER_PIN = 53;

const int NUM_LEDS = 6;
const int LED_PINS[NUM_LEDS] = {19, 14, 15, 16, 17, 18}; // R, G, Y, W, Error, Victory

const int BUTTONS_TOTAL = 5;
const int BUTTONS_VALUES[BUTTONS_TOTAL] = {170, 370, 520, 840, 930};

AnalogMultiButton buttons(BUTTONS_PIN, BUTTONS_TOTAL, BUTTONS_VALUES);
Keyboard keyboard;

void setup()
{
  Serial.begin(9600);

  reseedRandom();
  
  keyboard = Keyboard(BUTTONS_TOTAL, SPEAKER_PIN, NUM_LEDS, LED_PINS);
}


void loop()
{
  Serial.println(analogRead(BUTTONS_PIN));
  buttons.update();

  for(int i=0; i<BUTTONS_TOTAL; ++i)
  {
    if(buttons.onPress(i))
    {
      keyboard.newInput(i);
    }

    
  }

#ifdef DEBUG
  if(buttons.onPressAfter(4, 1500))
  {
    Serial.println("Reset button manually pressed");
    keyboard.reset();
  }
#endif

  delay(10);
}

