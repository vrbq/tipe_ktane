int boutontemoin = 8;
int bouton = 7;
int compteur;
int compteur2;

void setup() {
  attachInterrupt(digitalPinToInterrupt(boutontemoin), bascule, RISING);
  attachInterrupt(digitalPinToInterrupt(bouton), bascule2, CHANGE);
  Serial.begin(9600);
}

void loop() {
  Serial.println("test");
  delay(1000000);

}
void bascule(){ // c'est la fonction qui est déclanchée quand on appui sur le bouton grace a la foncion attachinterrupt
  compteur = compteur + 1;
  Serial.print("bouton témoin ");
  Serial.println(compteur);
}
void bascule2(){ // c'est la fonction qui est déclanchée quand on appui sur le bouton grace a la foncion attachinterrupt
  compteur2 = compteur2 + 1;
  Serial.print("bouton test ");
  Serial.println(compteur2);  
}
