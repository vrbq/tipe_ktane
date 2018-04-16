#ifndef Morse_h
#define Morse_h

const int led = 5;      // On attribue le pin sur lequel on a branché l'anode de la led  !!! IMPORTANT : On oublie pas de mettre une résistance !!!
const int led2 = 8;
const int temps = 250;   // Durée d'un point
int bouton = 7;
boolean erreur;
boolean module;
int buttonstate  = 0;
long alea;
int compteur;
String message = "";  // Ne pas mettre d'accent dans le message


