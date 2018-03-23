
#include "SevSeg.h"

SevSeg sevseg;

//Connexions Ã©lectroniques et variables des boutons
const int BOUTON_START = 21;            // Le bouton START est reliÃ© Ã  la broche 21
int etatBoutonStart = 0;               // variable d'Ã©tat du bouton START

//Variables relatives au temps
unsigned long instantStart = 0;           // Instant ou l'on a appuyÃ© sur START
long tempsEcoule = 0;                     // Temps Ã©coulÃ© depuis que l'on a appuyÃ© sur START
long temps = 0;                           // Temps que l'on veut


void setup() {

pinMode(BOUTON_START, INPUT);

byte numDigits = 4;
byte digitPins[] = {22, 23, 24, 25};
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
      sevseg.setNumber(calcul_temps_restant(tempsEcoule), 2);// On calcule le temps qu'il reste Ã  dÃ©compter et on dÃ©finit ce temps l'afficheur 7 Segments
      sevseg.refreshDisplay();                                // On rafraichit l'afficheur 7 Segments
      
    }                                                        // Le temps Ã©coulÃ© est Ã©gal au temps sÃ©lectionnÃ© (La condition de la boucle while n'est plus vraie, donc on en sort)
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



