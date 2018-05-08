#include <AnalogMultiButton.h>

#include "CustomRandom.h"
#include "SevSeg.h"

#include "timer.h"
#include "KeyboardModule.h"
#include "MorseModule.h"




//#define DEBUG

///////////// VARIABLES PROPRES AU JEU ///////////////
int bomb_explosed = 0;

unsigned long startMicros = 0; 
unsigned long currentMicros = micros();




///////////////// KEYBOARD //////////////////

int keyboard_toomanyerrors = 0;
int keyboard_solved = 0;

Keyboard keyboard;



///////////////////// TIMER /////////////
Timer timer;

//////////////////MORSE ///////////
//Morse morse;

//////////////////////////// SETUP /////////////////////////

void setup()
{

  Serial.begin(9600); //set monitor display
  randomSeed(analogRead(0));  //re-seed a new random value

  //KEYBOARD
  keyboard = Keyboard(BUTTONS_TOTAL, SPEAKER_PIN, NUM_LEDS, LED_PINS); //definition of keyboard class
  

  //TIMER 
  timer = Timer(); //definition of timer class

  //MORSE
  //morse = Morse();
  
}


//////////////////////////// LOOP /////////////////////////

void loop()
{
          
      
      /////////// TIMER /////////

      timer.update_timer();
      


      /////////// KEYBOARD MODULE /////////

      keyboard.update_keyboard();


      ///////// MORSE MODULE /////////
      //morse.update_morse();


      ////// COMPTEUR D'ERREUR TOTAL /////

      if (keyboard.error_count_keyboard_ == 3) //Penser a ajouter les erreurs des autres modules quand ils seront faits
      {
        Serial.println("You loose, too many errors.");
        bomb_explosed = 1;
        sevseg.setNumber(0, 2);
        sevseg.refreshDisplay();
      }
      

#ifdef DEBUG
  if(button_keyboard.onPressAfter(4, 1500))
  {
    Serial.println("Reset button manually pressed");
    keyboard.reset();
  }
#endif

}

