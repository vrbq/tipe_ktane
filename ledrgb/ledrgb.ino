//on commence en spécifiant les broches vont être utilisées pour chacune des couleurs:
int redPin = 4;
int greenPin = 3;
int bluePin = 2;
//#define COMMON_ANODE
void setup()
{
// on fixe les sorties
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}
 
void loop()
{
//partie expliquée dans la vidéo
  setColor(255, 0, 0);  // rouge
  //pause d'1 seconde
  delay(1000);
  setColor(0, 255, 0);  // vert
  delay(1000);
  setColor(0, 0, 255);  // bleu
  delay(1000);
  setColor(255, 255, 0);  // jaune
  delay(1000);  
  setColor(80, 0, 80);  // rose /violet
  delay(1000);
  setColor(0, 255, 255);  // aqua
  delay(1000);
}
 
//Cette fonction prend trois arguments, l'un pour la luminosité des diodes rouges, vertes et bleues. Dans
//chaque cas, le nombre sera compris entre 0 et 255, ou 0 signifit off et 255 signifie une luminosité max. La fonction
//appelle ensuite analogWrite pour régler la luminosité de chaque led.
 
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
