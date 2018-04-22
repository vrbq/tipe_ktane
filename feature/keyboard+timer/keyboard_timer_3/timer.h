#ifndef Timer_h
#define Timer_h

#include "SevSeg.h"


  // CONSTANTES TIMER BOUTONS
const int button_timer_pin = A2;            
const int nb_button_timer = 5;
const int button_timer_values[nb_button_timer] = {512};
const int buttontimer1 = 0;

AnalogMultiButton button_timer(button_timer_pin, nb_button_timer, button_timer_values);
int etat_button_timer_pin = 0;               // variable d'Ã©tat du bouton START



  // VARIABLES RELATIVES AU TEMPS
unsigned long instantStart_timer = 0;           // Instant ou l'on a appuyÃ© sur START
long tempsEcoule = 0;                     // Temps Ã©coulÃ© depuis que l'on a appuyÃ© sur START
long temps = 0;  




SevSeg sevseg; //7 segment du timer


class Timer
{

  public:

   
   enum Result
    {
      TIMER_RUN, TIMER_STOP
    };


  Timer(){

    pinMode(button_timer_pin, INPUT);

    byte numDigits = 4;
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
    sevseg.setBrightness(90);

    reset();

  }


  void reset()
    {

      intern_state_timer_ = 1; //RUNING
      compteur_launched_ = 0;
      
    }


   Result update_timer()
    {


      if (intern_state_timer_ == 1){

         button_timer.update();

         if (button_timer.onPress(buttontimer1)) {
          
            temps = 60;                                              
            instantStart_timer = millis();
            compteur_launched_ = 1;
         }
            

          if (tempsEcoule != temps){

                tempsEcoule = 1 + (millis() - instantStart_timer) / 1000;    
                sevseg.setNumber(calcul_temps_restant(tempsEcoule), 2);
                sevseg.refreshDisplay();
                return TIMER_RUN;
              
          }

          if (tempsEcoule == temps && compteur_launched_ == 1){
              
               tempsEcoule = 0;
               temps = 0;        

               intern_state_timer_ = 2; //Bomb explosed
                
               sevseg.refreshDisplay(); // Must run repeatedly
               return TIMER_STOP;
               
          }     
      } 
           
    }


    int calcul_temps_restant(int tempsActuel) {
      int tempsRestantEnMinutesEtSecondes=0;
      int minutesRestantes = (temps - tempsActuel) / 60;
      int secondesRestantes = (temps - tempsActuel) % 60;
      return tempsRestantEnMinutesEtSecondes = minutesRestantes * 100 + secondesRestantes;
    }



  int intern_state_timer_;
  int compteur_launched_;

};

#endif
