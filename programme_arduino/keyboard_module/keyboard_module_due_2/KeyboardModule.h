#ifndef Keyboard_h
#define Keyboard_h

#include "buzz.h"
#include "Arduino.h"

#define DEFAULT_BEEP_DURATION 120
#define DEFAULT_BEEP_FREQUENCY 440

enum
{
  DO, RE, MI, FA, SOL
};

// DO, RE, MI, FA, SOL
int NOTE_FREQUENCIES[] = {262, 294, 330, 349, 392};

const int note_duration = 165;

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

    enum Result
    {
      CORRECT_INPUT, WRONG_INPUT, CODE_FOUND
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

      // Choose a code randomly among the ones in the database
      code_index_ = random(1, 4);
      Serial.print("Selected code: ");
      Serial.println(code_index_);

      // Indicate the sequence and shift value to the user
      indicateNumberWithLedsCode(code_index_);

      // Generate a random shift
      shift_ = random(1,4);
      Serial.print("Selected shift: ");
      Serial.println(shift_);

      indicateNumberWithLedsShift(shift_);
    }

    void playNote(int input_value)
    {
      buzz(speaker_pin_, NOTE_FREQUENCIES[input_value],note_duration);
    }

    Result newInput(int input_value)
    {
      // reverse the button order so that the keyboard reads from left ro right when looking towards the Arduino
      input_value = (num_inputs_ - 1) - input_value;

      // shift the buttons so that button number i (starting from zero) corresponds to the note 'DO'
      input_value = (input_value + num_inputs_ - shift_) % num_inputs_;

      playNote(input_value);
      
      if(input_value == codeValueAt(index_next_button_in_code_)) // has the user hit the next key in the sequence?
      {
        Serial.print("Correct input => ");
        Serial.print(index_next_button_in_code_ + 1);
        Serial.print(" / ");
        Serial.println(CODE_LENGTH);
        
        index_next_button_in_code_++;

        if(index_next_button_in_code_ == CODE_LENGTH) // is that the last key of the sequence?
        {
          Serial.println("Congrats, you completed the code!");
          
          playVictorySequence();
          
          return CODE_FOUND;
        }
        else
        {
          return CORRECT_INPUT;
        }
      }
      else
      {
        Serial.println("Wrong input. Start again from scratch.");
        
        index_next_button_in_code_ = 0;
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



    void blinkLedAndBeep(int led_pin, int speaker_pin, int duration, int beep_frequency=DEFAULT_BEEP_FREQUENCY)
    {
      digitalWrite(led_pin, HIGH);
      buzz(speaker_pin, beep_frequency,duration);
      
      //digitalWrite(led_pin, HIGH);
      //delay(duration);
      //noTone(speaker_pin);
      
      digitalWrite(led_pin, LOW);
    }

    void playErrorSequence()
    {
      const int error_pin = led_pins_[4];
      digitalWrite(error_pin, HIGH);
      delay(note_duration);
      for(int i=0; i<2; ++i)
      {
        buzz(speaker_pin_, DEFAULT_BEEP_FREQUENCY,90);
        //delay(90);
        //noTone(speaker_pin_);
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

    void setLeds(int red_value, int green_value, int blue_led)
    {
      digitalWrite(led_pins_[0], red_value);
      digitalWrite(led_pins_[1], green_value);
      digitalWrite(led_pins_[2], blue_led);
    }


    int num_inputs_;
    int code_index_;
    int shift_;
    int index_next_button_in_code_;

    int speaker_pin_;
    int num_leds_;
    const int *led_pins_;
};


#endif
