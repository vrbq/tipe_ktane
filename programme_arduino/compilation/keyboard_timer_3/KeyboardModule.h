#ifndef Keyboard_h
#define Keyboard_h

#include "buzz.h"
#include "Arduino.h"
#include "timer.h"


#define DEFAULT_BEEP_DURATION 120
#define DEFAULT_BEEP_FREQUENCY 440

enum
{
  DO, RE, MI, FA, SOL
};

// DO, RE, MI, FA, SOL
int NOTE_FREQUENCIES[] = {262, 294, 330, 349, 392};

const int note_duration = 165;



const int BUTTONS_PIN = A1;
const int SPEAKER_PIN = 53;

const int NUM_LEDS = 6;
const int LED_PINS[NUM_LEDS] = {19, 14, 15, 16, 17, 18}; // R, G, Y, W, Error, Victory

const int BUTTONS_TOTAL = 5;
const int BUTTONS_VALUES[BUTTONS_TOTAL] = {170, 370, 520, 840, 930};

AnalogMultiButton button_keyboard(BUTTONS_PIN, BUTTONS_TOTAL, BUTTONS_VALUES);



//// DECLARATION POUR LE TIMER




// Dictionary of codes
// A random dictionary can be generated using the python script in scripts/generate_random_dictionary.py
const byte CODE_LENGTH=9;
const byte CODE_DB_SIZE=7;
const byte CODE_DB[CODE_LENGTH * CODE_DB_SIZE] = 
    {SOL, SOL, SOL, SOL, SOL, SOL, SOL, SOL, SOL, 
     MI, FA, FA, DO, SOL, RE, SOL, FA, DO, 
     FA, SOL, DO, DO, FA, RE, RE, MI, MI, 
     SOL, RE, FA, SOL, DO, SOL, DO, DO, SOL, 
     RE, RE, RE, RE, RE, RE, RE, RE, RE, 
     RE, SOL, SOL, DO, MI, SOL, MI, MI, DO, 
     RE, SOL, RE, SOL, SOL, MI, MI, FA, MI};



class Keyboard
{  
  public:


    enum Result1
    {
      KEYBOARD_PAUSE, KEYBOARD_GAME
    };

    enum Result2
    {
      NOTE_PLAYING
    };

    enum Result3
    {
      CORRECT_INPUT, CODE_FOUND, WRONG_INPUT, BOMB_EXPLOSED   //State "BOMB_EXPLOSED" not yet done
    };


    Keyboard() {}

    Keyboard(int num_inputs, int speaker_pin,
             int num_leds, const int* led_pins)
    {
      if(num_inputs > 8)
      {
        Serial.println("Error: maximum number of keyboard inputs supported is 8!");
        return;
      }

      //Local variable to global variable
      num_inputs_ = num_inputs;
      speaker_pin_ = speaker_pin;
      num_leds_ = num_leds;
      led_pins_ = led_pins;

      pinMode(speaker_pin_, OUTPUT);
      for(int i=0; i<num_leds_;++i)
      {
        pinMode(led_pins_[i], OUTPUT);
      }
      
      
      reset();
    }

    int codeValueAt(int index)
    {
        return (int) CODE_DB[code_index_ * CODE_LENGTH + index];
    }
    
    void reset()
    {
      
      index_next_button_in_code_ = 0;
      error_count_keyboard_= 0;
      intern_state_keyboard_ = 1; //0 = PAUSE ; 1 = GAME ; 11 = NOTE_PLAYING ; 1111 = CORRECT_INPUT ; 1112 = CODE_FOUND ; 1121 = WRONG_INPUT (ERROR) ; 1122 = BOMB_EXPLOSED
      

      // Choose a code randomly among the ones in the database
      code_index_ = random(1, 5);
      Serial.print("Selected code: ");
      Serial.println(code_index_);

      // Indicate the sequence and shift value to the user
      indicateNumberWithLedsCode(code_index_);

      // Generate a random shift
      shift_ = random(1,5);
      Serial.print("Selected shift: ");
      Serial.println(shift_);

      indicateNumberWithLedsShift(shift_);
    }

    void playNote(int input_value)
    {
      buzz(speaker_pin_, NOTE_FREQUENCIES[input_value],note_duration);
    }




   Result1 update_keyboard()
    {
      
      if (intern_state_keyboard_ == 0){ //Game is on pause
        return KEYBOARD_PAUSE;
      }

      if(intern_state_keyboard_ != 0
      //&& timer.intern_state_timer_ == 1*          // Comment faire pour utiliser une variable de ma classe ?  /// EDIT : ON PEUT LE FAIRE GERER PAR UNE AUTRE CLASSE CA NAN ?
      ){ //Game is running


        if (intern_state_keyboard_ == 1){ //Keyboard is running

                  button_keyboard.update();
        
                for(int i=0; i<BUTTONS_TOTAL; ++i)
              {
        
                if(button_keyboard.onPress(i))
                {
                  newInput(i);
                }  
             
              }
        
                return KEYBOARD_GAME;
                
        }

        if(intern_state_keyboard_ == 11)
        {
          
          playNote(input_value); //PROBLEME QUE ON SATI PAS CE QUE C'EST LE INPUT VALUE ICI

          InputResult(); //IL FAUDRAIT FAIRE LE INPUT RESULT UN FOIS LA NOTE FINIE : IMPOSSIBLE DE LA METTRE DANS LE BUZZ QUI EST UTILISEE PAR D'AUTRES FONCTIONS
        }




        

    }

  }
    
    Result2 newInput(int input_value)
    {
      // reverse the button order so that the keyboard reads from left ro right when looking towards the Arduino
      input_value = (num_inputs_ - 1) - input_value;

      // shift the buttons so that button number i (starting from zero) corresponds to the note 'DO'
      input_value = (input_value + num_inputs_ - shift_) % num_inputs_;

      intern_state_keyboard_ = 11;
      
      
      return NOTE_PLAYING

    }


    Result3 InputResult() //PROBLEME QUE ON SATI PAS CE QUE C'EST LE INPUT VALUE ICI
    {


      if(input_value == codeValueAt(index_next_button_in_code_)) // has the user hit the next key in the sequence?
          {
            Serial.print("Correct input => ");
            Serial.print(index_next_button_in_code_ + 1);
            Serial.print(" / ");
            Serial.println(CODE_LENGTH);
            
            index_next_button_in_code_++;
    
            if(index_next_button_in_code_ == CODE_LENGTH) // is that the last key of the sequence?
            {
              intern_state_keyboard_ = 4; //Game Victory
              
              Serial.println("Congrats, you completed the code!");
              
              playVictorySequence();
    
              intern_state_keyboard_ = 1112;
    
              return CODE_FOUND;
            }
    
            
            else
            {
              intern_state_keyboard_ = 1111; 
              return CORRECT_INPUT;
            }
    
            
          }
    
          
      else
          {
            Serial.println("Wrong input. Start again from scratch.");
    
            intern_state_keyboard_ = 1121;
            
            index_next_button_in_code_ = 0;
            error_count_keyboard_ ++;
            Serial.println("Number of errors :");
            Serial.println(error_count_keyboard_);
            playErrorSequence();
    
             return WRONG_INPUT;
             
    
          }
  
    }


    void indicateNumberWithLedsCode (int number)
    {
      

      if(number == 1)
      {
        digitalWrite(led_pins_[0],LOW);
        digitalWrite(led_pins_[1],LOW);
      }

      if(number == 2)
      {
        digitalWrite(led_pins_[0],HIGH);
        digitalWrite(led_pins_[1],LOW);
      }

      if(number == 3)
      {
        digitalWrite(led_pins_[0],LOW);
        digitalWrite(led_pins_[1],HIGH);
      }

      if(number == 4)
      {
        digitalWrite(led_pins_[0],HIGH);
        digitalWrite(led_pins_[1],HIGH);
      }
      
    }


    void indicateNumberWithLedsShift (int number)
    {
     if(number == 1)
      {
        digitalWrite(led_pins_[2],LOW);
        digitalWrite(led_pins_[3],LOW);
      }

      if(number == 2)
      {
        digitalWrite(led_pins_[2],HIGH);
        digitalWrite(led_pins_[3],LOW);
      }

      if(number == 3)
      {
        digitalWrite(led_pins_[2],LOW);
        digitalWrite(led_pins_[3],HIGH);
      }

      if(number == 4)
      {
        digitalWrite(led_pins_[2],HIGH);
        digitalWrite(led_pins_[3],HIGH);
      }
      
    }



    /*void blinkLedAndBeep(int led_pin, int speaker_pin, int duration, int beep_frequency=DEFAULT_BEEP_FREQUENCY)
    {
      digitalWrite(led_pin, HIGH);
      buzz(speaker_pin, beep_frequency,duration);
      
      digitalWrite(led_pin, LOW);
    }*/

    void playErrorSequence()
    {
      
      const int error_pin = led_pins_[4];
      digitalWrite(error_pin, HIGH);
      delay(note_duration);
      for(int i=0; i<2; ++i)
      {
        buzz(speaker_pin_, DEFAULT_BEEP_FREQUENCY,90);
        delay(90);
      }
      digitalWrite(error_pin, LOW);
    }

    void playVictorySequence()
    {
      const int victory_pin = led_pins_[5];
      digitalWrite(victory_pin, HIGH);
      delay(note_duration);
      for(int i=0; i<2; ++i)
      {
        buzz(speaker_pin_, DEFAULT_BEEP_FREQUENCY,180); //le 180 etait 90 a la base, pour le "error"
        //delay(90);
        //noTone(speaker_pin_);
        delay(90);
      }
    }

    /////// VARIABLES INTERNE DE LA CLASSE

    int num_inputs_;
    int code_index_;
    int shift_;
    int index_next_button_in_code_;
    int error_count_keyboard_;
    int intern_state_keyboard_;

    int speaker_pin_;
    int num_leds_;
    const int *led_pins_;
};


#endif
