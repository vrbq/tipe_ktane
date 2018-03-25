#include <AnalogMultiButton.h>

const int BUTTON_PIN = A0;
const int BUTTONS_TOTAL = 1;
const int BUTTONS_VALUES[BUTTONS_TOTAL] = {512};

const int BUTTON_BLUE = 0;
AnalogMultiButton buttons(BUTTON_PIN,BUTTONS_TOTAL,BUTTONS_VALUES);

void setup()
{
  Serial.begin(9600);
  
}

void loop()
{
  buttons.update();
//Serial.println(analogRead(BUTTON_PIN));

// do this if BUTTON_BLUE was released, and it was held for 1 second or less
  if(buttons.isPressedAfter(BUTTON_BLUE, 1000))
  {
    Serial.println("Blue has been released after less than 1 second of pressing");
    Serial.print("Blue was held for ");
    Serial.print(buttons.getLastReleasePressDuration());
    Serial.println(" ms");
  }









delay(10);

}
