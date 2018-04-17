//https://forum.arduino.cc/index.php?topic=492308.0
const int led = 9;  //led du morse
const int led2 = 8; //led verte qui indique si c'est réussi ou pas
const int temps = 250;   // Durée d'un point (durée de référence)
int bouton = 7; // bouton pour saisir le numéro du mot
byte etatBrocheLed;
byte etatBrocheLed2;
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
long alea;
int compteur = 0;
String message = "";  // Ne pas mettre d'accent dans le message

void setup() {
  module = false; // etat du module
  etatBrocheLed = HIGH;
  pinMode(bouton, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(led, OUTPUT); 
  pinMode(led2, OUTPUT);
  alea = alea(1,9);
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
  
  message.replace(".",".-.-.-;");
  message.replace("-","-....-;");
  // message.replace(";","-.-.-;");  // non je ne remplace pas celui là car ca enlèverait la fin des deux premières conversions
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
buttonstate = digitalRead(bouton);
unsigned long currentMillis = millis();
  if (message.substring(i, i+1) == "-" ) { // cas du "long"
    intervalle = 3*temps;
    intervalle2 = temps;
    inter = intervalle;
  }
  else if (message.substring(i, i+1) == "." ) { // cas du "court"
    intervalle = temps;
    intervalle2 = temps;
    inter = intervalle;
    }
  else if (message.substring(i, i+1) == ";" ) { //espace entre chaque lettre
    intervalle = 3*temps;
    inter = intervalle;
  }
  else if (message.substring(i, i+1) == "|" ) {// Rappelez-vous, un espacement de la durée de 7 points entre chaque mots
    intervalle = 7*temps;
    inter = intervalle;
  }

  if(currentMillis - previousMillis >= inter and (message.substring(i,i+1) == "-" or message.substring(i, i+1) == ".") ) { // à chaque fois que le temps indique par inter est dépassé on change l'état de la led
    previousMillis = currentMillis;
    inter = intervalle2; // comme le tiret se fait en deux temps différents je change la longueur du temps a attendre pour la deuxieme partie
    etatBrocheLed = !etatBrocheLed;
    ++compt;
  }
  else if (currentMillis - previousMillis >= inter and (message.substring(i, i+1) == ";" or message.substring(i, i+1) == "|")){
    ++compt2;
    etatBrocheLed = !etatBrocheLed;
    previousMillis = currentMillis;
  }
if ((compt == 2 or compt2 == 1) and (message.substring(i+1,i+2) == ";" or message.substring(i+1, i+2) == "|")){ // un tiret ou un point se font toujous en deux temps d'où les intervalles 1 et 2 et le compteur
  ++i; 
  compt=0;   //a chaque fois qu'un signal est transcrit on remet le compteur à 0 
  compt2 =0;
  etatBrocheLed = LOW; // comme le prochain caractère est un espacement avec la led éteinte je met l'état en low
}
else if ((compt == 2 or compt2 == 1) and (message.substring(i+1,i+2) == "-" or message.substring(i+1, i+2) == ".")){ 
  ++i;
  compt2 =0;
  compt = 0;
  etatBrocheLed = HIGH; // comme le prochain caractère et un tiret ou un point il faut mettre l'état en high
}
if (i == message.length()-1){ // je sais pas pourquoi il faut mettre -1 mais sinon ca boucle pas donc bon
  i = 0; // on boucle
}
digitalWrite(led, etatBrocheLed);
digitalWrite(led2, etatBrocheLed2);

if (buttonstate == HIGH and currentMillis - previousMillis2 >=300){  // le temps de 300 millis sert a éviter le rebond (j'ai pas réussi avec les condensateurs masi bon ca marche bien logiciellement) 
  compteur = compteur + 1;
  previousMillis2 = currentMillis;
  Serial.println(compteur);
}
if (compteur == alea){
    module = true;
    etatBrocheLed2 = HIGH;
  }
else if (compteur > alea or currentMillis - previousMillis2 >= 5000){ // si le joueur attend plus de 5 secondes apres avoir appuyé une première fois il a perdu
  module = false; // il faut changer ca dans le programme final et faire un compteur d'erreurs à la place
  i = 500; // c'est une valeur lambda superieure à la longueur des mots 
  etatBrocheLed = HIGH;
  etatBrocheLed2 = LOW;
}
}


