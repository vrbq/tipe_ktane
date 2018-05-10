#include <AnalogMultiButton.h>

#include "CustomRandom.h"
#include "SevSeg.h"

#include "timer.h"
#include "KeyboardModule.h"
#include "MorseModule.h"


///////////// VARIABLES PROPRES AU JEU ///////////////
boolean bomb_explosed = false;

boolean game_launched = false;

int error_count_total = 0;


  // CONSTANTES START BOUTON
const int BUTTON_START_BOMB_PIN = A2;            
const int NB_BUTTON_START_BOMB = 1;
const int BUTTON_START_BOMB_VALUES[NB_BUTTON_START_BOMB] = {512};

const int button_launch_bomb = 0;
AnalogMultiButton button_start_bomb(BUTTON_START_BOMB_PIN, NB_BUTTON_START_BOMB, BUTTON_START_BOMB_VALUES);


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
  pinMode(BUTTON_START_BOMB_PIN, INPUT);

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
  
    button_start_bomb.update();
       
      if(game_launched == false and button_start_bomb.onPress(button_launch_bomb) and bomb_explosed == false)
      {

        game_launched = true;
        
          /////////// TIMER /////////
  
        timer.update_timer();
  
        /////////// KEYBOARD MODULE /////////
  
        keyboard.update_keyboard();
  
        ///////// MORSE MODULE /////////
        
        //morse.update_morse();
  
        ////// COMPTEUR D'ERREUR TOTAL /////
  
        error_count_total = keyboard.error_count_keyboard_; //Penser a ajouter les erreurs des autres modules quand ils seront faits
  
        if (error_count_total == 3)
        {
          Serial.println("You loose, too many errors.");
          bomb_explosed = true;
          sevseg.setNumber(0, 2);
          sevseg.refreshDisplay();
          game_launched = false;
        }
        
      }
      
     

}
