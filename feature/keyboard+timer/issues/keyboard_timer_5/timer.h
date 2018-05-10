#ifndef Timer_h
#define Timer_h

#include "SevSeg.h"


// NOT SURE IT IS USEFUL ?
int etat_button_timer_pin = 0;



  // VARIABLES RELATIVES AU TEMPS
long time_elapsed_since_launched_sec = 0; //Time elapsed since the timer was launched
long temps_max_bomb;  


  //BUZZER
const int buzzer_timer_pin = 52;
const int note_duration = 165;




SevSeg sevseg; //7 segment du timer


class Timer
{

  public:

   
   enum State
    {
      PAUSE, TIMER_RUN, TIMER_SOUND, TIMER_STOP
    };


  Timer(){


    byte numDigits = 4;
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
    sevseg.setBrightness(90);

    reset();

  }


  void reset()
    {
      state_ = PAUSE;

      first_time_second_refreshed_ = 0;
      last_time_note_playing_updated_ = 0;
      digitalWrite(buzzer_timer_pin,LOW);
      current_cycle_number_ = 0;

    }


   void update_timer()
    {

        if(state_ == PAUSE)
        {
          
         if (game_launched == true) {
          
            temps_max_bomb = 60; //s                                             
            state_ = TIMER_RUN;
            Serial.println("Launched");
            time_timer_launched_ = millis();
            return;
         }
         
        }

        else if(state_ == TIMER_RUN)
        {
           
            time_elapsed_since_launched_sec = (millis() - time_timer_launched_) / 1000; //en s
            //Serial.println(time_elapsed_since_launched_sec);

            /*if(time_elapsed_since_launched_sec != last_time_elapsed_)
            {
              Serial.println("A beep is playing");
              state_ = TIMER_SOUND;
              return;
            }*/
            
            if(time_elapsed_since_launched_sec >= temps_max_bomb)
            {
              Serial.println("Bomb exploded");
              state_ = PAUSE;
              return;
            }
            
            sevseg.setNumber(calcul_temps_restant(time_elapsed_since_launched_sec), 2);
            sevseg.refreshDisplay();

            last_time_elapsed_ = time_elapsed_since_launched_sec;                
          
        }


        /*if(state_ == TIMER_SOUND)
        {
            int frequency = 330;
            
            long delayValue = 1000000 / frequency / 2; //delay en microsecondes
            //Serial.println("Delay Value is");
            //Serial.println(delayValue);
            long numCycles = frequency * 165 / 1000; //165 = note_duration (defined in KeyboardModule.h)
    
            unsigned long current_time = micros();
            //Serial.println("Current time is");
            //Serial.println(current_time);
            
            if(current_time - last_time_note_playing_updated_ >= delayValue)
            {       
              int state_targetpin = digitalRead(buzzer_timer_pin);
    
              if (state_targetpin == HIGH)
              {
                digitalWrite(buzzer_timer_pin,LOW);
                current_cycle_number_ ++;
                //Serial.println("Current cycle is");
                //Serial.println(current_cycle_number_);
              }
    
              else
              {
                digitalWrite(buzzer_timer_pin,HIGH);  
              }
              
            last_time_note_playing_updated_ = micros();
              
            }
    
            if(current_cycle_number_ == numCycles)
            {
              Serial.println("Bien sorti dans le timer sound");
              state_ = TIMER_RUN;
              current_cycle_number_ = 0;
              last_time_note_playing_updated_ = 0;
              digitalWrite(buzzer_timer_pin,LOW);   //this is not necessary
            }
            
          }*/
           
    }
    

    int calcul_temps_restant(int tempsActuel) {
      int tempsRestantEnMinutesEtSecondes=0;
      int minutesRestantes = (temps_max_bomb - tempsActuel) / 60;
      int secondesRestantes = (temps_max_bomb - tempsActuel) % 60;
      return tempsRestantEnMinutesEtSecondes = minutesRestantes * 100 + secondesRestantes;
    }

  
    //Useful variables for NOTE_PLAYING state
    unsigned long last_time_note_playing_updated_;     
    int current_cycle_number_;
    
    int first_time_second_refreshed_;
    long last_time_elapsed_;

    long time_timer_launched_; //time when we launch timer

    State state_;
    
};

#endif
