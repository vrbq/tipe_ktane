#ifndef Keyboard_h
#define Keyboard_h

#include "buzz.h"
#include "Arduino.h"
#include "timer.h"

  //LCD DECLARATION
#include <Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd_keyboard(0x27, 20, 2); //SERIAL NUMBER : KEYBOARD
LiquidCrystal_I2C lcd_morse_and_error(0x27, 20, 2); //COMPTEUR MORSE + ERROR COUNT

#define DEFAULT_BEEP_DURATION 120
#define DEFAULT_BEEP_FREQUENCY 440

enum
{
  DO, RE, MI, FA, SOL
};

// FREQUENCIES {DO, RE, MI, FA, SOL}
int NOTE_FREQUENCIES[] = {262, 294, 330, 349, 392};


const int SPEAKER_PIN = 53;
const int NUM_LEDS = 6;
const int LED_PINS[NUM_LEDS] = {19, 14, 15, 16, 17, 18}; // Red, Green, Yellow, White, Error, Victory

const int BUTTONS_PIN = A1;
const int BUTTONS_TOTAL = 5;
const int BUTTONS_VALUES[BUTTONS_TOTAL] = {196, 430, 573, 855, 962};

AnalogMultiButton button_keyboard(BUTTONS_PIN, BUTTONS_TOTAL, BUTTONS_VALUES);


// Dictionary of codes
// A random dictionary can be generated using the python script in scripts/generate_random_dictionary.py
const byte CODE_LENGTH=9;
const byte CODE_DB_SIZE=9;
const byte CODE_DB[CODE_LENGTH * CODE_DB_SIZE] = 
    {DO, RE, MI, RE, DO, MI, RE, RE, DO, //AU CLAIR DE LA LUNE
     DO, DO, RE, DO, FA, MI, DO, DO, RE, //FRERES JACQUES
     MI, MI, FA, SOL, SOL, FA, MI, RE, DO, //ODE A LA JOIE
     MI, FA, SOL, FA, MI, RE, MI, RE, MI, //OLE
     DO, SOL, FA, DO, MI, MI, RE, DO, SOL, //AU PIF
     DO, SOL, SOL, FA, RE, FA, SOL, RE, MI, //SUZUKI
     MI, FA, SOL, SOL, MI, SOL, DO, SOL, MI, //FORREST GUMP
     RE, SOL, FA, DO, MI, SOL, MI, FA, DO, //AU PIF
     MI, RE, DO, RE, MI, RE, MI, SOL, SOL}; //AU PIF



class Keyboard
{  
  public:

    enum State
    {
      PAUSE, GAME, NOTE_PLAYING, CHECK_INPUT_VALUE, PLAY_FEEDBACK_CORRECT, PLAY_FEEDBACK_WRONG, CODE_FOUND
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

    /////////////////// CONSTRUCTOR //////////////
    void reset()
    {
      
      state_ = PAUSE;
      
    }

   void start()
   {
    if (state_ == PAUSE){ //Game is on pause

        last_time_note_playing_updated_ = 0;
        digitalWrite(speaker_pin_,LOW);
        current_cycle_number_ = 0;
        
        first_time_play_feedback_correct_ = true;
        first_time_play_feedback_wrong_ = true;

        index_next_button_in_code_ = 0;
        error_count_keyboard_= 0;
        keyboard_solved_ = false;

        // Choose a code randomly among the ones in the database
        code_index_ = random(0, 9);
        Serial.println("Keyboard : ");
        
        Serial.print("Selected code : ");
        Serial.println(code_index_);
  
        // Indicate the sequence and shift value to the user
        indicateNumberWithLedsCode(code_index_);
  
        // Generate a random shift
        shift_ = random(0,5);
        Serial.print("Selected shift : ");
        Serial.println(shift_);
  
        indicateNumberWithLedsShift(shift_);

        state_ = GAME;
        
        return;
    }
       
   }




   void update_keyboard()
    {
      
      if (state_ == PAUSE){ //Game is on pause
        return;
      }

      else if(state_ == GAME){ 
          //Serial.println(analogRead(BUTTONS_PIN));
          button_keyboard.update();
        
          for(int i=0; i<BUTTONS_TOTAL; ++i)
          {   
              if(button_keyboard.onPress(i))
              {

                  // reverse the button order so that the keyboard reads from left ro right when looking towards the Arduino
                  input_value_ = (num_inputs_ - 1) - i;
            
                  // shift the buttons so that button number i (starting from zero) corresponds to the note 'DO'
                  input_value_ = (input_value_ + num_inputs_ - shift_) % num_inputs_;

                  state_ = NOTE_PLAYING;
                  return;
      
              }  
             
          }
       return;

      }

      else if(state_ == NOTE_PLAYING)
      {
        int frequency = NOTE_FREQUENCIES[input_value_];
        
        long delayValue = 1000000 / frequency / 2; //delay in microsecondes
        long numCycles = frequency * note_duration / 1000;

        unsigned long current_time = micros();
        
        if(current_time - last_time_note_playing_updated_ >= delayValue)
        {       
          int state_targetpin = digitalRead(speaker_pin_);

          if (state_targetpin == HIGH)
          {
            digitalWrite(speaker_pin_,LOW);
            current_cycle_number_ ++;
          }

          else
          {
            digitalWrite(speaker_pin_,HIGH);  
          }
          
        last_time_note_playing_updated_ = micros();
          
        }

        if(current_cycle_number_ == numCycles)
        {
          state_ = CHECK_INPUT_VALUE;
          current_cycle_number_ = 0;
          last_time_note_playing_updated_ = 0;
          digitalWrite(speaker_pin_,LOW);   //this is not necessary
        }

        return;
            
          
      }

      else if(state_ == CHECK_INPUT_VALUE)
      {

        if(input_value_ == codeValueAt(index_next_button_in_code_)) // has the user hit the next key in the sequence?
        {
            Serial.print("Keyboard : Correct input => ");
            Serial.print(index_next_button_in_code_ + 1);
            Serial.print(" / ");
            Serial.println(CODE_LENGTH);
            
            index_next_button_in_code_++;
    
            if(index_next_button_in_code_ == CODE_LENGTH) // is that the last key of the sequence?
            {
              
              Serial.println("Keyboard Solved");
              keyboard_solved_ = true;
              state_ = CODE_FOUND;
            }
    
            
            else
            {
              state_ = PLAY_FEEDBACK_CORRECT; 
            }
    
            
        }
    
          
        else
        {
            Serial.println("Keyboard : Wrong input. Start again from scratch.");
    
            state_ = PLAY_FEEDBACK_WRONG;
            
            index_next_button_in_code_ = 0;
            error_count_keyboard_ ++;
            Serial.println("Number of errors :");
            Serial.println(error_count_keyboard_);  
    
        }
        
      }

      else if(state_ == PLAY_FEEDBACK_CORRECT)
      {

        if(first_time_play_feedback_correct_) //means if(first_time_play_feedback_correct_ == true)
        {
          previousMillis_correct_led_ = millis();
          first_time_play_feedback_correct_ = false;
        }

        unsigned long currentMillis_correct_led = millis();
        digitalWrite(led_pins_[5], HIGH);

        if (currentMillis_correct_led - previousMillis_correct_led_ >= note_duration) 
        {
          digitalWrite(led_pins_[5], LOW);
          first_time_play_feedback_correct_ = true;
          state_ = GAME;
        }

      }

      else if(state_ == PLAY_FEEDBACK_WRONG)
      {

        if(first_time_play_feedback_wrong_ == true)
        {
          previousMillis_error_led_ = millis();
          first_time_play_feedback_wrong_ = false;
        }

        unsigned long currentMillis_error_led = millis();
        digitalWrite(led_pins_[4], HIGH);

        if (currentMillis_error_led - previousMillis_error_led_ >= note_duration) 
        {
          digitalWrite(led_pins_[4], LOW);
          first_time_play_feedback_wrong_ = true;
          state_ = GAME;
        }

      }

      else if(state_ == CODE_FOUND){
        digitalWrite(led_pins_[4], HIGH);
        digitalWrite(led_pins_[5], HIGH);
        state_ = PAUSE;
        
      }

  }
    



    void indicateNumberWithLedsCode (int number) //INDICATION : BINARY MODE
    {
      
      // led_pins_[0] = 1
      // led_pins_[2] = 2
      // led_pins_[3] = 4
      // led_pins_[4] = 8

      if(number == 0) //A
      {
        digitalWrite(led_pins_[0],HIGH);
        digitalWrite(led_pins_[1],LOW);
        digitalWrite(led_pins_[2],HIGH);
        digitalWrite(led_pins_[3],HIGH);
      }
      

      if(number == 1) //B
      {
        digitalWrite(led_pins_[0],HIGH);
        digitalWrite(led_pins_[1],LOW);
        digitalWrite(led_pins_[2],HIGH);
        digitalWrite(led_pins_[3],LOW);
      }

      if(number == 2) //C
      {
        digitalWrite(led_pins_[0],LOW);
        digitalWrite(led_pins_[1],LOW);
        digitalWrite(led_pins_[2],HIGH);
        digitalWrite(led_pins_[3],HIGH);
      }

      if(number == 3) //D
      {
        digitalWrite(led_pins_[0],LOW);
        digitalWrite(led_pins_[1],HIGH);
        digitalWrite(led_pins_[2],LOW);
        digitalWrite(led_pins_[3],HIGH);
      }

      if(number == 4) //E
      {
        digitalWrite(led_pins_[0],LOW);
        digitalWrite(led_pins_[1],LOW);
        digitalWrite(led_pins_[2],LOW);
        digitalWrite(led_pins_[3],LOW);
      }

      if(number == 5) //F
      {
        digitalWrite(led_pins_[0],LOW);
        digitalWrite(led_pins_[1],HIGH);
        digitalWrite(led_pins_[2],HIGH);
        digitalWrite(led_pins_[3],HIGH);
      }

      if(number == 6) //G
      {
        digitalWrite(led_pins_[0],HIGH);
        digitalWrite(led_pins_[1],HIGH);
        digitalWrite(led_pins_[2],HIGH);
        digitalWrite(led_pins_[3],HIGH);
      }

      if(number == 7) //H
      {
        digitalWrite(led_pins_[0],LOW);
        digitalWrite(led_pins_[1],LOW);
        digitalWrite(led_pins_[2],LOW);
        digitalWrite(led_pins_[3],HIGH);
      }

      if(number == 8) //I
      {
        digitalWrite(led_pins_[0],HIGH);
        digitalWrite(led_pins_[1],LOW);
        digitalWrite(led_pins_[2],LOW);
        digitalWrite(led_pins_[3],HIGH);
      }
      
    }


    void indicateNumberWithLedsShift (int number)
    {

     if(number == 0) //AU MOINS QUATRE VOYELLES DANS LE SERIAL
      {
        lcd_keyboard.init();  // initialisation of lcd scree
        lcd_keyboard.backlight(); // send the message
        lcd_keyboard.setCursor(0, 0);
        lcd_keyboard.print("285-576-432");
      }
    
     if(number == 1) //SOMMES CHIFFRES SERIAL => NOMBRE PREMIER
      {
        lcd_keyboard.init();  // initialisation of lcd_keyboard scree
        lcd_keyboard.backlight(); // send the message
        lcd_keyboard.setCursor(0, 0);
        lcd_keyboard.print("536-914-104");
      }

      if(number == 2) //PRODUIT CHIFFRES SERIAL => PAIR
      {
        lcd_keyboard.init();  
        lcd_keyboard.backlight(); 
        lcd_keyboard.setCursor(0, 0);
        lcd_keyboard.print("222-574-137");
      }

      if(number == 3) //ON PEUT FORMER LANOIX ou DELEGUE
      {
        lcd_keyboard.init(); 
        lcd_keyboard.backlight();
        lcd_keyboard.setCursor(0, 0);
        lcd_keyboard.print("126-789-483");
      }

      if(number == 4) //SI AUCUN DES ELEMENTS NE CORRESPOND
      {
        lcd_keyboard.init();  
        lcd_keyboard.backlight();
        lcd_keyboard.setCursor(0, 0);
        lcd_keyboard.print("359-786-423");
      }
      
      
    }


    /////// INTERN VARIABLES TO KEYBOARD CLASS

    int num_inputs_;
    int code_index_;
    int shift_;
    int input_value_; //Last input from the user (for check_input_value)
    int index_next_button_in_code_;
    int error_count_keyboard_;
    boolean keyboard_solved_;
    State state_;

    //Variables utiles pour note_playing
    unsigned long last_time_note_playing_updated_;     
    int current_cycle_number_;

    //Play Feedback Correct
    unsigned long previousMillis_correct_led_;
    boolean first_time_play_feedback_correct_;

    //Play Feedback Error
    unsigned long previousMillis_error_led_;
    boolean first_time_play_feedback_wrong_;
        
    int speaker_pin_;
    int num_leds_;
    const int *led_pins_;
};


#endif
