/*
  Ce programme permet de crÃ©er un minuteur Ã  l'aide de trois boutons, un afficheur 7 Segments SH5461AS et un anneau de Leds Adafruit neopixel
  Ce programme a Ã©tÃ© Ã©crit par Matthieu CHATRY, Flavien, Yannick, MaÃ¿lis et David LE GALL et est publiÃ© dans le domaine public
  Retrouvez le tutoriel complet Ã  cette adresse : http://wikifab.org/wiki/Timer_:_Un_minuteur_%C3%A0_base_d%27Arduino
*/



#include "SevSeg.h"                   //BibliothÃ¨que permettant de piloter l'afficheur 7 segments Ã  tÃ©lÃ©charger ici https://github.com/DeanIsMe/SevSeg  

//Connexions Ã©lectroniques et variables des boutons
const int BOUTON_START = 2;            // Le bouton START est reliÃ© Ã  la broche 2
int etatBoutonStart = 0;               // variable d'Ã©tat du bouton START


//Afficheur 7 segments
byte numDigits = 4;                      // Nombre de digits de l'afficheur 7 segments, ici il y en a 4 ( on utilise un afficheur rÃ©fÃ©rencÃ© SH5461AS )
byte digitPins[] = {13, 10, 9, A5};      // Branchement des broches contrÃ´lant les chiffres, celles ou on mettra une rÃ©sistance de 220 Ohm
byte segmentPins[] = {12, 8, A3, A1, A0, 11, A4, A2}; // Branchements des broches controlant les segments
SevSeg sevseg;                                 // On dÃ©clare un objet sevseg qui reprÃ©sente l'afficheur 7 segments


//Variables relatives au temps
unsigned long instantStart = 0;           // Instant ou l'on a appuyÃ© sur START
long tempsEcoule = 0;                     // Temps Ã©coulÃ© depuis que l'on a appuyÃ© sur START
long temps = 0;                           // Temps que l'on veut
//int tempsEnSecondes[] = {60, 180, 300, 600, 900, 1200, 1800, 2700, 3600, 5400, 7200}; // les diffÃ©rents temps proposÃ©s dans le menu ( variable interne en secondes, n'est pas affichÃ©e)


void setup() {
  // On dÃ©clare chaque Bouton comme Ã©tant une entrÃ©e
  pinMode(BOUTON_START, INPUT);
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);

  //On initialise l'afficheur 7 Segments
  sevseg.setBrightness(90);      //On rÃ¨gle l'intensitÃ© lumineuse de l'afficheur 7 Segments
}

void loop() {

  //on commence par lire l'etat des buttons et stocker les Ã©tats dans les variables d'Ã©tat
  etatBoutonStart = digitalRead(BOUTON_START);
  
  //traitement bouton START
  if (etatBoutonStart == HIGH) {
    temps = 60;                  // On met Ã  jour la variable Temps en fonction de la nouvelle valeur du compteur
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

int calcul_temps_restant(int tempsActuel) {                  // Fonction permettant de transformer le temps en secondes en minutes et secondes.
  int tempsRestantEnMinutesEtSecondes=0;
  int minutesRestantes = (temps - tempsActuel) / 60;
  int secondesRestantes = (temps - tempsActuel) % 60; //ressource consultÃ©e pour le calcul https://www.arduino.cc/en/Reference/modulo
  return tempsRestantEnMinutesEtSecondes = minutesRestantes * 100 + secondesRestantes;
}



/* JOURNAL DES MODIFICATIONS

  MAJ David  01/09/17
  Passage du code tout en francais, commentaires et rÃ©fÃ©rences.

  MAJ David  01/01/16
  J'ai remplacÃ© l'Ã©cran par un afficheur 7 Segments

  MAJ MaÃ¿lis 29/12/16
  Ajout du changement des couleurs selon le temps Ã©coulÃ© -> il faudrait amÃ©liorer le dÃ©gradÃ© (qu'ils soit un peu moins "net"), qu'il soit plus progressif

  MAJ Flavien 22/12/16
  Modification de la fonction "calcul_temps". Utilisation de deux tableaux: l'un pour affecter le temps (en seconde), l'autre pour l'affichage dans le menu.
  -> Pour ajouter un temps au menu, ajouter son nombre de seconde dans le tableau "tempsEnSecondes" et le texte Ã©quivalent dans "tempsAffiche" Ã  la mÃªme position.
  -> Affichage des temps dynamiquement directement dans le menu.
  Ajout d'une fonction "affichage_menu" pour afficher le menu dans son ensemble.
  Lors de l'appui sur "+", dÃ©tection automatique (avec sizeof() ) de la taille du tableau "tempsEnSecondes" pour bloquer le compteur "selecteurTemps"
  ->Bug: la taille du tableau est doublÃ©, seule solution pour le moment, diviser par deux (et le -1 car le compteur commence Ã  0).
  Le temps affichÃ© est un dÃ©compte et fini par zÃ©ro.
  Lors du retour au menu, le temps par dÃ©faut est celui sÃ©lectionnÃ© auparavant.
  Ajout du texte "Temps restant:" lors du dÃ©compte du temps.
  Bugfix: Les LED ne clignotent plus, j'ai mis le "eteindreLeds()" en dehors de la boucle while.

  MAJ David 21/12/16
  intÃ©gration adafruit neopixel
  bugfix : jai changÃ© long en unsigned long pour temps et timer, sinon ca buggait au dessus de 10s car la variable Ã©tait pleine

  MAJ Yannick 16/12/16
  Temps affichÃ© en minutes mais set en secondes pour tests
  Utiliser timer Ã  la place de delay() cf: http://playground.arduino.cc/Code/AvoidDelay
  Pendant dÃ©compte si on appuie sur + et - cela reset
*/
