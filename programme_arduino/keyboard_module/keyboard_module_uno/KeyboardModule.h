#ifndef Keyboard_h
#define Keyboard_h

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
    {SOL, SOL, RE, MI, MI, SOL, FA, FA, DO, 
     MI, FA, FA, DO, SOL, RE, SOL, FA, DO, 
     FA, SOL, DO, DO, FA, RE, RE, MI, MI, 
     SOL, RE, FA, SOL, DO, SOL, DO, DO, SOL, 
     RE, RE, MI, FA, RE, DO, MI, FA, FA, 
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
      playResetSequence();
      
      index_next_button_in_code_ = 0;

      // Choose a code randomly among the ones in the database
      code_index_ = random(1, CODE_DB_SIZE);
      Serial.print("Selected code: ");
      Serial.println(code_index_);

      // Indicate the sequence and shift value to the user
      indicateNumberWithLeds(code_index_);

      // Generate a random shift
      shift_ = random(1, num_inputs_)-1;
      Serial.print("Selected shift: ");
      Serial.println(shift_);

      indicateNumberWithLeds(shift_);
      
      setLeds(LOW, LOW, LOW);
    }

    void playNote(int input_value)
    {
      tone(speaker_pin_, NOTE_FREQUENCIES[input_value]);
      delay(note_duration);
      noTone(speaker_pin_);
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
          reset();
          
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

    void indicateNumberWithLeds(int number)
    {
      // Indicate a number to the user by switching on a set of leds.
      //
      // We look at the last num_leds_ digits in the binary representation of number
      // and activate some of the LEDs based on these values.
      //
      
      if(number == 0)
      {
        // to avoid having no leds switched on when the number is 0
        // (which would be confusing for the user),
        // we replace zero with the max value in the range
        // so that all leds will be switched on instead
        
        number = bit(num_leds_)-1;
      }
      
      for(int i=0; i<num_leds_; ++i)
      {
        if (number & (1 << i))  // if bit i is set
        {
          digitalWrite(led_pins_[i], HIGH);
        }
        else
        {
          digitalWrite(led_pins_[i], LOW);
        }
      }

      tone(speaker_pin_, DEFAULT_BEEP_FREQUENCY);
      delay(DEFAULT_BEEP_DURATION);
      noTone(speaker_pin_);

      delay(1800);
      
    }

    void blinkLedAndBeep(int led_pin, int speaker_pin, int duration, int beep_frequency=DEFAULT_BEEP_FREQUENCY)
    {
      tone(speaker_pin, beep_frequency);
      digitalWrite(led_pin, HIGH);
      delay(duration);

      noTone(speaker_pin);
      digitalWrite(led_pin, LOW);
    }

    void playResetSequence()
    {
      for(int i=0; i<3; ++i)
      {
        for(int j=0; j<num_leds_; ++j)
        {
          blinkLedAndBeep(led_pins_[j], speaker_pin_, DEFAULT_BEEP_DURATION);
        }
      }
      delay(350);
    }

    void playErrorSequence()
    {
      const int red_led_pin_ = led_pins_[0];
      digitalWrite(red_led_pin_, HIGH);
      delay(note_duration);
      for(int i=0; i<2; ++i)
      {
        tone(speaker_pin_, DEFAULT_BEEP_FREQUENCY);
        delay(90);
        noTone(speaker_pin_);
        delay(90);
      }
      digitalWrite(red_led_pin_, LOW);
    }
    
    void playVictorySequence()
    {
      const int green_led_pin_ = led_pins_[1];
      digitalWrite(green_led_pin_, HIGH);
      noTone(speaker_pin_);
      delay(note_duration);
      for(int i=0; i<num_inputs_; ++i)
      {
        tone(speaker_pin_, NOTE_FREQUENCIES[i]);
        delay(100);
      }
      for(int i=num_inputs_-2; i>=0; --i)
      {
        tone(speaker_pin_, NOTE_FREQUENCIES[i]);
        delay(100);
      }
      noTone(speaker_pin_);
      digitalWrite(green_led_pin_, LOW);
      delay(300);
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

void buzz(int speaker_pin, long NOTE_FREQUENCIES[], long note_duration) {
  long delayValue = 1000000 / NOTE_FREQUENCIES[] / 2; // calculate the delay value between transitions

  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = NOTE_FREQUENCIES[] * note_duration / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(speaker_pin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(speaker_pin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
 
}

#endif
