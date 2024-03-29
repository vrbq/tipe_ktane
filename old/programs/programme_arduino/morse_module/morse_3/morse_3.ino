const byte led = 9;      // On attribue le pin sur lequel on a branché l'anode de la led  !!! IMPORTANT : On oublie pas de mettre une résistance !!!
const int temps = 250;   // Durée d'un point
const byte bouton = 6;
boolean  buttonstate;
int alea =0;

String message = "";  // Ne pas mettre d'accent dans le message

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.print("hello world");
  pinMode(led, OUTPUT); // On définit le pin "led" en sortie
  pinMode(bouton, INPUT);
  

}

// the loop function runs over and over again forever
void loop() {
  buttonstate = digitalRead(bouton);
  if (buttonstate == LOW){
 // SequencageMorse(debut);     // On lance le séquencage morse du début de message
    SequencageMorse(message);   // On séquence notre message à la suite
 // SequencageMorse(fin);       // On indique la fin du message
    Serial.println("nique ta race");
  }
  else {
    alea = random(1,9);
    Serial.println(alea);
    switch (alea) {
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
  
    // Ne pas modifier le code ci-dessous si vous ne savez pas ce que vous faites.
    
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
    
}

// Fonctions

// Le séquencage morse
void SequencageMorse(String msg){
  // On crée une boucle FOR qui démarre à 0 jusqu'au nombre de lettre dans le message à séquencer en incrémentant de 1 à chaque tour
  for(int i = 0; i < msg.length(); i++) {
    // On vérifie à quoi correspond chaque caractère dans la boucle
    if (msg.substring(i, i+1) == "-") {
      tiret();
    }
    else if (msg.substring(i, i+1) == ".") {
      point();
    }
    else if (msg.substring(i, i+1) == ";") {
      delay(3*temps);  // Rapelez-vous, un espacement de la durée de 3 points entre chaque lettre
    }
    else if (msg.substring(i, i+1) == "|") {
      Serial.print("   ");
      delay(7*temps);  // Rapelez-vous, un espacement de la durée de 7 points entre chaque mots
    }
  }
}

// Fonctions pour l'activation-désactivation de la led selon si c'est un tiret ou un point avec les temps qui leur sont attribué et que vous pouvez règler tout en haut au début du code qui est la variable "temps"
void tiret(){
  analogWrite(led,25);   // HIGH = Allumé
  delay(3*temps);
  digitalWrite(led, LOW);    // LOW = Eteind
  delay(temps);
}

void point(){
  analogWrite(led, 25);   // HIGH = Allumé
  delay(temps);
  digitalWrite(led, LOW);    // LOW = Eteint
  delay(temps);
}


