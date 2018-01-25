#include "SevSeg.h"
#define melodyPin 53

SevSeg sevseg;

//Connexions Ã©lectroniques et variables des boutons
const int BOUTON_START = 21;            // Le bouton START est reliÃ© Ã  la broche 21
int etatBoutonStart = 0;               // variable d'Ã©tat du bouton START
int buzzer = 53;

//Variables relatives au temps
unsigned long instantStart = 0;           // Instant ou l'on a appuyÃ© sur START
long tempsEcoule = 0;                     // Temps Ã©coulÃ© depuis que l'on a appuyÃ© sur START
long temps = 0;                           // Temps que l'on veut
long temps_test =0;


void setup() {
Serial.begin(9600);
pinMode(BOUTON_START, INPUT);
pinMode(buzzer, OUTPUT);

byte numDigits = 4;
byte digitPins[] = {2, 3, 4, 5};
byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
sevseg.setBrightness(90);

}


void loop() {

//on commence par lire l'etat des buttons et stocker les Ã©tats dans les variables d'Ã©tat
  etatBoutonStart = digitalRead(BOUTON_START);
  
  //traitement bouton START
  if (etatBoutonStart == LOW) {
    temps = 300;                  // On met Ã  jour la variable Temps en fonction de la nouvelle valeur du compteur
    instantStart = millis();                                  //On utilise la fonction millis qui renvoie le nombre de millisecondes depuis que le programme est lancÃ© pour garder en mÃ©moire l'instant ou l'on a appuyÃ© sur start. Plus d'infos sur Millis ici : https://www.arduino.cc/en/Reference/Millis
    
    while (tempsEcoule != temps) {                            // Tant que le temps Ã©coulÃ© n'est pas celui que l'on a sÃ©lectionnÃ©
      tempsEcoule = 1 + (millis() - instantStart) / 1000;     //calcul du temps Ã©coulÃ© depuis l'appui sur start (+1 pour commencer chrono Ã  1)
      Serial.print(tempsEcoule);
      Serial.println();
      sevseg.setNumber(calcul_temps_restant(tempsEcoule), 2);// On calcule le temps qu'il reste Ã  dÃ©compter et on dÃ©finit ce temps l'afficheur 7 Segments
      sevseg.refreshDisplay();                              // On rafraichit l'afficheur 7 Segments
    
      if (temps_test != tempsEcoule){
        buzz(melodyPin,3322,1);
      temps_test = tempsEcoule;
      }
    }                                                        // Le temps Ã©coulÃ© est Ã©gal au temps sÃ©lectionnÃ© (La condition de la boucle while n'est plus vraie, donc on en sort)
    temps_test = 0;
    tempsEcoule = 0;
  }
  sevseg.refreshDisplay(); // Must run repeatedly

}



//Fonctions Annexes

int calcul_temps_restant(int tempsActuel) {
  int tempsRestantEnMinutesEtSecondes=0;
  int minutesRestantes = (temps - tempsActuel) / 60;
  int secondesRestantes = (temps - tempsActuel) % 60;
  return tempsRestantEnMinutesEtSecondes = minutesRestantes * 100 + secondesRestantes;
}

void buzz(int targetPin, long frequency, long length) {
  digitalWrite(47, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(47, LOW);
 
}


