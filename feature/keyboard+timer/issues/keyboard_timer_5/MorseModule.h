#ifndef Morse_h
#define Morse_h

  // CONSTANTES LED MORSE
const int led_morse = 9;  //pin de la led du morse //led
const int led_victory = 8; //led verte victoire    //led2

byte etat_led_morse; //etat
byte etat_led_victory; //etat_led_victory

  // CONSTANTES BOUTON MORSE
const int button_morse_pin = A8;            
const int nb_button_morse = 1;
const int button_morse_values[nb_button_morse] = {512};
const int buttonmorse1 = 0;

AnalogMultiButton button_morse(button_morse_pin, nb_button_morse, button_morse_values);


  //CONSTANTES TEMPS MORSE
const int temps = 250;   // Durée d'un point (durée de référence)
unsigned long previousMillis_led_morse = 0;
unsigned long previousMillis2 = 0;  //CAS OU IL FAUT GERER LES REBONDS

int compt_fin_point_tiret; //compt
int compt_fin_lettre; //compt2
int i; //i

int inter; //intervalle de temps où le message est transmis


  //CONSTANTES MORSE
int alea; //Aleatoire des mots choisis
int compteur = 0; //Compteur du nombre de fois où le bouton à été pressé
int error_count_morse = 0;
boolean module;

String message = "";  // Ne pas mettre d'accent dans le message



class Morse
{  

   public:

    Morse()
    {
      pinMode(led_morse, OUTPUT); 
      pinMode(led_victory, OUTPUT);
      
      reset();
  
    }
  
    void reset()
    {
        etat_led_morse = HIGH;
        error_count_morse = 0;

        alea = random(1,9);
        Serial.print(alea);
        Serial.print(" --> ");
        switch (alea) // les différents mots dans la fonciton switch case
        { 
          case 1:
            message = "TOTO";
            Serial.println(message);
            break;
          case 2:
            message = "CHIMIE";
            Serial.println(message);
            break;
          case 3:
            message = "TINTIN";
            Serial.println(message);
            break;
          case 4:
            message = "EPONGE";
            Serial.println(message);
            break;
          case 5:
            message = "MARTY";
            Serial.println(message);
            break;
          case 6:
            message = "MATHS";
            Serial.println(message);
            break;
          case 7:
            message = "PLAGE";
            Serial.println(message);
            break;
          case 8:
            message = "NEYMAR";
            Serial.println(message);
            break;
          case 9:
            message = "TIPE";
            Serial.println(message);
            break; 
        }

      message.toUpperCase();  // On transcrit tout le message en majuscule

      message.replace("A",".-;");
      message.replace("B","-...;");
      message.replace("C","-.-.;");
      message.replace("D","-..;");
      message.replace("E",".;");
      message.replace("F","..-.;");
      message.replace("G","--.;");
      message.replace("H","....;");
      message.replace("I","..;");
      message.replace("J",".---;");
      message.replace("K","-.-;");
      message.replace("L",".-..;");
      message.replace("M","--;");
      message.replace("N","-.;");
      message.replace("O","---;");
      message.replace("P",".--.;");
      message.replace("Q","--.-;");
      message.replace("R",".-.;");
      message.replace("S","...;");
      message.replace("T","-;");
      message.replace("U","..-;");
      message.replace("V","...-;");
      message.replace("W",".--;");
      message.replace("X","-..-;");
      message.replace("Y","-.--;");
      message.replace("Z","--..;");
      message.replace("1",".----;");
      message.replace("2","..---;");
      message.replace("3","...--;");
      message.replace("4","....-;");
      message.replace("5",".....;");
      message.replace("6","-....;");
      message.replace("7","--...;");
      message.replace("8","---..;");
      message.replace("9","----.;");
      message.replace("0","-----;");
      message.replace(" ","|");           // Ici le "|" indique la fin d'un mot et qu'il peut y en avoir un autre derrière car il y a un espace dans votre message  
      message.replace(":","---...;");
      message.replace(",","--..--;");
      message.replace("?","..--..;");
      message.replace("'",".----.;");
      message.replace("!","-.-.--;");
      message.replace("@",".--.-.;");
       
      message = message + "|";  // J'ajoute un "|" qui marquera la fin du mot ou du message et qui servira dans le sequencage morse plus bas dans le code

      // On remplace maintenant ";|" par "|" dans le message transformé car la fin de lettre ne sert à rien avant un autre mot
      message.replace(";|","|");

    }




    void update_morse()
    {
        
      digitalWrite(led_morse, etat_led_morse);
      digitalWrite(led_morse,etat_led_victory);
      button_morse.update();
      
      unsigned long currentMillis = millis();
      if (compt_fin_point_tiret == 0 and compt_fin_lettre ==0){
        if (message.substring(i, i+1) == "-" ) { // cas du "long"
          inter = 3*temps;
        }
        else if (message.substring(i, i+1) == "." ) { // cas du "court"
          inter = temps;
          }
        else if (message.substring(i, i+1) == ";" ) { //espace entre chaque lettre
          inter = 3*temps;
        }
        else if (message.substring(i, i+1) == "|" ) {//espacement de 7 temps entre chaque mots
          inter = 7*temps;
        }
      }
  
  
      
        if(currentMillis - previousMillis_led_morse >= inter and (message.substring(i,i+1) == "-" or message.substring(i, i+1) == ".") ) { // à chaque fois que le temps indique par inter est dépassé on change l'état de la led
          previousMillis_led_morse = currentMillis;
          if (message.substring(i,i+1) == "-"){// comme le tiret se fait en deux temps différents je change la longueur du temps a attendre pour la deuxieme partie
            inter = temps;
          }
          etat_led_morse = ! etat_led_morse; //Switch l'état
          ++compt_fin_point_tiret;
        }
  
        
        else if (currentMillis - previousMillis_led_morse >= inter and message.substring(i, i+1) == ";"){
          ++compt_fin_lettre;
          previousMillis_led_morse = currentMillis;
        }
  
        
        else if (currentMillis - previousMillis_led_morse >= inter and message.substring(i,i+1) == "|"){
          previousMillis_led_morse = currentMillis;
          ++i;
        }
  
  
  
        
      if (i == message.length()){ // je sais pas pourquoi il faut mettre -1 mais sinon ca boucle pas donc bon message length = 21 pour alea = 2 et ca s'arrete a 20
        i = 0; // on boucle
        etat_led_morse = HIGH;
      }
  
  
  
      
      if ((compt_fin_point_tiret == 2 or compt_fin_lettre == 1) and (message.substring(i+1,i+2) == ";" or message.substring(i+1, i+2) == "|")){ // un tiret ou un point se font toujous en deux temps d'où les intervalles 1 et 2 et le compteur
        ++i; 
        compt_fin_point_tiret=0;   //a chaque fois qu'un signal est transcrit on remet le compteur à 0 
        compt_fin_lettre =0;
        etat_led_morse = LOW; // comme le prochain caractère est un espacement avec la led éteinte je met l'état en low
      }
  
  
  
      
      else if ((compt_fin_point_tiret == 2 or compt_fin_lettre == 1) and (message.substring(i+1,i+2) == "-" or message.substring(i+1, i+2) == ".")){ 
        ++i;
        compt_fin_lettre =0;
        compt_fin_point_tiret = 0;
        etat_led_morse = HIGH; // comme le prochain caractère et un tiret ou un point il faut mettre l'état en high
      }
      
      if (button_morse.onPress(0) 
      //and currentMillis - previousMillis2 >=300
      ){  // le temps de 300 millis sert a éviter le rebond (j'ai pas réussi avec les condensateurs masi bon ca marche bien logiciellement) 
       ++ compteur;
        //previousMillis2 = currentMillis;
        Serial.println("Compteur is on : ");
        Serial.println(compteur);
      }
  
  
      
      if (compteur > 0 and currentMillis - previousMillis2 >= 5000){
        
        if (compteur == alea){
            module = true;
            Serial.println("Morse : Solved");
            etat_led_victory = HIGH;
            etat_led_morse = LOW;
          }
          
        else if (compteur != alea){ // si le joueur attend plus de 5 secondes apres avoir appuyé une première fois il a perdu
          error_count_morse = error_count_morse + 1;
          Serial.println("Morse : 1 error");
          /*module = false; // il faut changer ca dans le programme final et faire un compteur d'erreurs à la place
          i = 50; // c'est une valeur lambda superieure à la longueur des mots 
          etat_led_morse = HIGH;
          etat_led_victory = LOW;*/
          compteur = 0; 
        }
        
      }
   
    }

    //VARIABLES INTERNES A LA CLASSE MORSE
};

#endif
