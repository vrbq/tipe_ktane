//https://forum.arduino.cc/index.php?topic=492308.0 morse
//https://www.carnetdumaker.net/articles/faire-plusieurs-choses-la-fois-avec-une-carte-arduino/ utilisation de la fontion millis
const int led = 51;  //led du morse
const int buzz = 6;
const int led2 = 49; //led verte qui indique si c'est réussi ou pas
const int temps = 250;   // Durée d'un point (durée de référence)
int bouton = 47; // bouton pour saisir le numéro du mot
byte etat;
byte etat2;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0; 
int intervalle;
int intervalle2;
int compt = 0;
int compt2 = 0;
int inter;
int i = 0;
boolean module;
int buttonstate  = 0;
int alea;
int compteur = 0;
String message = "";  // Ne pas mettre d'accent dans le message

void setup() {

  module = false; // etat du module
  etat = HIGH;
  pinMode(bouton, INPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
  Serial.println("test1");
  randomSeed(analogRead(0));
  pinMode(led, OUTPUT); 
  pinMode(led2, OUTPUT);
  alea = random(1,9);
  Serial.print(alea);
  Serial.print(" --> ");
  switch (alea) { // les différents mots dans la fonciton switch case
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

  // On remplaceme chaque lettre du message par le code morse qui lui est attribué
  // Notez que j'ajoute un ";" volontairement à la fin afin de marquer la fin de la lettre dans le sequencage morse plus bas dans le code
  // on commence en toute logique par les "." et "-" et ";" qui sont dans votre message afin de ne pas remplacer les . ou - d'une lettre déjà convertie donc on commence par ça
  
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

void loop() {    //message --> -.-.;....;..;--;..;.| message morse du mot chimie
digitalWrite(led, etat);
digitalWrite(led2,etat2);

buttonstate = digitalRead(bouton);
/*Serial.println("Button state :");
Serial.println(buttonstate);*/

unsigned long currentMillis = millis();
if (compt == 0 and compt2 ==0){
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
  if(currentMillis - previousMillis >= inter and (message.substring(i,i+1) == "-" or message.substring(i, i+1) == ".") ) { // à chaque fois que le temps indique par inter est dépassé on change l'état de la led
    previousMillis = currentMillis;
    if (message.substring(i,i+1) == "-"){// comme le tiret se fait en deux temps différents je change la longueur du temps a attendre pour la deuxieme partie
      inter = temps;
    }
    etat = ! etat;
    ++compt;
  }
  else if (currentMillis - previousMillis >= inter and message.substring(i, i+1) == ";"){
    ++compt2;
    previousMillis = currentMillis;
  }
  else if (currentMillis - previousMillis >= inter and message.substring(i,i+1) == "|"){
    previousMillis = currentMillis;
    ++i;
  }
if (i == message.length()){ // je sais pas pourquoi il faut mettre -1 mais sinon ca boucle pas donc bon message length = 21 pour alea = 2 et ca s'arrete a 20
  i = 0; // on boucle
  etat = HIGH;
}
if ((compt == 2 or compt2 == 1) and (message.substring(i+1,i+2) == ";" or message.substring(i+1, i+2) == "|")){ // un tiret ou un point se font toujous en deux temps d'où les intervalles 1 et 2 et le compteur
  ++i; 
  compt=0;   //a chaque fois qu'un signal est transcrit on remet le compteur à 0 
  compt2 =0;
  etat = LOW; // comme le prochain caractère est un espacement avec la led éteinte je met l'état en low
}
else if ((compt == 2 or compt2 == 1) and (message.substring(i+1,i+2) == "-" or message.substring(i+1, i+2) == ".")){ 
  ++i;
  compt2 =0;
  compt = 0;
  etat = HIGH; // comme le prochain caractère et un tiret ou un point il faut mettre l'état en high
}

if (buttonstate == HIGH and currentMillis - previousMillis2 >=300){  // le temps de 300 millis sert a éviter le rebond (j'ai pas réussi avec les condensateurs masi bon ca marche bien logiciellement) 
  ++ compteur;
  previousMillis2 = currentMillis;
  Serial.print("Compteur is on ");
  Serial.println(compteur);
}
if (compteur > 0 and currentMillis - previousMillis2 >= 5000){
  if (compteur == alea){
     Serial.println("Gagné");
      module = true;
      etat2 = HIGH;
      etat = LOW;
    }
  else if (compteur != alea){ // si le joueur attend plus de 5 secondes apres avoir appuyé une première fois il a perdu
    Serial.println("Perdu");
    module = false; // il faut changer ca dans le programme final et faire un compteur d'erreurs à la place
    i = 50; // c'est une valeur lambda superieure à la longueur des mots 
    etat = HIGH;
    etat2 = LOW;
    compteur = 10; 
  }
}
}


