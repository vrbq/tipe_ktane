#include <AnalogMultiButton.h>
#include "KeyboardModule.h"
#include "CustomRandom.h"
#include "SevSeg.h"




//#define DEBUG

///////////// VARIABLES PROPRES AU JEU ///////////////
int bomb_explosed = 0;

/*unsigned long startMicros;
unsigned long currentMicros;*/





///////////////// KEYBOARD //////////////////

const int BUTTONS_PIN = A1;
const int SPEAKER_PIN = 53;

const int NUM_LEDS = 6;
const int LED_PINS[NUM_LEDS] = {19, 14, 15, 16, 17, 18}; // R, G, Y, W, Error, Victory

const int BUTTONS_TOTAL = 5;
const int BUTTONS_VALUES[BUTTONS_TOTAL] = {170, 370, 520, 840, 930};

int keyboard_toomanyerrors = 0;
int keyboard_solved = 0;

AnalogMultiButton button_keyboard(BUTTONS_PIN, BUTTONS_TOTAL, BUTTONS_VALUES);
Keyboard keyboard;



///////////////////// TIMER /////////////
//Connexions Ã©lectroniques et variables des boutons
const int BOUTON_START = 52;            // Le bouton START est reliÃ© Ã  la broche 21
int etatBoutonStart = 0;               // variable d'Ã©tat du bouton START

//Variables relatives au temps
unsigned long instantStart = 0;           // Instant ou l'on a appuyÃ© sur START
long tempsEcoule = 0;                     // Temps Ã©coulÃ© depuis que l'on a appuyÃ© sur START
long temps = 0;  

SevSeg sevseg; //7 segment du timer




//////////////////////////// SETUP /////////////////////////

void setup()
{

  unsigned long startMicros = micros();

  
  //KEYBOARD
  Serial.begin(9600);
  randomSeed(analogRead(0));  
  keyboard = Keyboard(BUTTONS_TOTAL, SPEAKER_PIN, NUM_LEDS, LED_PINS);
  

  //TIMER 
  pinMode(BOUTON_START, INPUT);

  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
}


//////////////////////////// LOOP /////////////////////////

void loop()
{

  etatBoutonStart = digitalRead(BOUTON_START);

  if (etatBoutonStart == LOW) {
    temps = 60;                                               // Temps du compteur en secondes
    instantStart = millis();                                  //On utilise la fonction millis qui renvoie le nombre de millisecondes depuis que le programme est lancÃ© pour garder en mÃ©moire l'instant ou l'on a appuyÃ© sur start. Plus d'infos sur Millis ici : https://www.arduino.cc/en/Reference/Millis
    
    while (tempsEcoule != temps && bomb_explosed == 0) {                            // Tant que le temps Ã©coulÃ© n'est pas celui que l'on a sÃ©lectionnÃ©
      tempsEcoule = 1 + (millis() - instantStart) / 1000;     //calcul du temps Ã©coulÃ© depuis l'appui sur start (+1 pour commencer chrono Ã  1)
      sevseg.setNumber(calcul_temps_restant(tempsEcoule), 2);// On calcule le temps qu'il reste Ã  dÃ©compter et on dÃ©finit ce temps l'afficheur 7 Segments
      sevseg.refreshDisplay();                                // On rafraichit l'afficheur 7 Segments

      /////////// KEYBOARD MODULE /////////

      //Serial.println(analogRead(BUTTONS_PIN));
      button_keyboard.update();

      for(int i=0; i<BUTTONS_TOTAL; ++i)
      {
        unsigned long currentMicros = micros();
        if(button_keyboard.onPress(i) && keyboard_toomanyerrors == 0 && keyboard_solved == 0)
        {
          Keyboard::Result result = keyboard.newInput(i);
          
            if(result == Keyboard::Result::CODE_FOUND)
            {
            Serial.println("Keyboard module solved");
              
            keyboard_solved = 1;
            
            }
        }  
     
      }

      ////// COMPTEUR D'ERREUR TOTAL /////

      if (keyboard.error_count_keyboard_ == 3) //Penser a ajouter les erreurs des autres modules quand ils seront faits
      {
        Serial.println("You loose, too many errors.");
        bomb_explosed = 1;
        sevseg.setNumber(0, 2);
        sevseg.refreshDisplay();
      }
    
    }                                                      
    tempsEcoule = 0;
  }

sevseg.refreshDisplay(); // Must run repeatedly

#ifdef DEBUG
  if(button_keyboard.onPressAfter(4, 1500))
  {
    Serial.println("Reset button manually pressed");
    keyboard.reset();
  }
#endif

}




//////////// FONCTIONS ANNEXES //////////////////

  //////// TIMER /////
int calcul_temps_restant(int tempsActuel) {
  int tempsRestantEnMinutesEtSecondes=0;
  int minutesRestantes = (temps - tempsActuel) / 60;
  int secondesRestantes = (temps - tempsActuel) % 60;
  return tempsRestantEnMinutesEtSecondes = minutesRestantes * 100 + secondesRestantes;
}

