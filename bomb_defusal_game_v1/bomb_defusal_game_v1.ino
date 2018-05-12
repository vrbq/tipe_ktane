#include <AnalogMultiButton.h>

#include "CustomRandom.h"
#include "SevSeg.h"

#include "timer.h"
#include "KeyboardModule.h"
#include "MorseModule.h"


///////////// VARIABLES PROPRES AU JEU ///////////////
boolean bomb_explosed = false;
boolean bomb_solved = false;
boolean game_launched = false;

int error_count_total = 0;

  //LED ERROR
const int led_error_1 = 44;
const int led_error_2 = 46;


  // CONSTANTES START BOUTON
int button_launch_bomb = 48;


///////////////// KEYBOARD //////////////////

int keyboard_toomanyerrors = 0;
int keyboard_solved = 0;

Keyboard keyboard;



///////////////////// TIMER /////////////
Timer timer;

//////////////////MORSE ///////////
Morse morse;

//////////////////////////// SETUP /////////////////////////

void setup()
{
  

  Serial.begin(9600); //set monitor display
  Serial.println("//////////////////////////// NEW BOMB ! ///////////////////////////");
  Serial.println("Welcome into the Defusal Bomb Game : choose a friend to play with !");
  
  randomSeed(analogRead(0));  //re-seed a new random value
  pinMode(button_launch_bomb, INPUT);
  
  pinMode(led_error_1, OUTPUT);
  pinMode(led_error_2, OUTPUT);


  //KEYBOARD
  keyboard = Keyboard(BUTTONS_TOTAL, SPEAKER_PIN, NUM_LEDS, LED_PINS); //definition of keyboard class
  

  //TIMER 
  timer = Timer(); //definition of timer class
  
  //MORSE
  morse = Morse();
  lcd_morse_and_error.init(); //Initialization LCD MORSE + ERROR COUNT
  
}


//////////////////////////// LOOP /////////////////////////

void loop()
{
  
      
      if(game_launched == false and digitalRead(button_launch_bomb) == HIGH and bomb_explosed == false and bomb_solved == false) //to relaunch the bomb, we need to remove condition : bomb_explosed == false
      {
        Serial.println("Starting modules : Morse + Keyboard");
        timer.start();
        keyboard.start();
        morse.start();
        
        game_launched = true;
        bomb_explosed = false;

      }

      if(bomb_explosed == false and bomb_solved == false){

        /////////// TIMER /////////
  
        timer.update_timer();
  
        /////////// KEYBOARD MODULE /////////
  
        keyboard.update_keyboard();
  
        ///////// MORSE MODULE /////////
        
        morse.update_morse();
  
        ////// COMPTEUR D'ERREUR TOTAL /////
  
        error_count_total = keyboard.error_count_keyboard_ + error_count_morse; 

        if (error_count_total == 1 )
        {
          digitalWrite(led_error_1, HIGH);
        }

        if (error_count_total == 2)
        {
          digitalWrite(led_error_1, HIGH);
          digitalWrite(led_error_2, HIGH);
        }
  
        if (error_count_total == 3)
        {
          Serial.println("You loose ! :(");
          Serial.println("Cause : too many errors.");
          bomb_explosed = true;
        }

        if (time_out == true){
          Serial.println("You loose ! :(");
          Serial.println("Cause : run out of time");
          bomb_explosed = true;
        }

        if(morse_solved == true and keyboard.keyboard_solved_ == true)
        {
          Serial.println("WOW ! YOU SAVE THE WORLD ! CONGRATS !");
          bomb_solved = true;
        }

        
      }

      else if(bomb_explosed == true){
      sevseg.setNumber(0, 2);
      sevseg.refreshDisplay();
      game_launched = false;
      }

}

