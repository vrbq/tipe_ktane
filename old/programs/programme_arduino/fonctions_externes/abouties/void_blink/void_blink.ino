// Déclare les broches sur lesquelles sont câblées les LEDs
const int BROCHE_LED_1 = 13;

// Fonction setup(), appelée au démarrage de la carte Arduino
void setup() {

  // Configure les broches des LEDs en sortie
  pinMode(BROCHE_LED_1, OUTPUT);
  
  // Configure l'état initial des LEDs
  digitalWrite(BROCHE_LED_1, LOW);
}

// Fonction loop(), appelée continuellement en boucle tant que la carte Arduino est alimentée
void loop() {
  
  // Sous traite les différentes tâches
  blink_led(BROCHE_LED_1);
}





void blink_led(int led_pin) {
  static unsigned long previousMillisLedBlink = 0;
  static byte led_pin_state = LOW;
  
  unsigned long currentMillis = millis();
  
  // Si BLINK_INTERVAL_1 ou plus millisecondes se sont écoulés
  if(currentMillis - previousMillisLedBlink >= 1000) {
    
    // Garde en mémoire la valeur actuelle de millis()
    previousMillisLedBlink = currentMillis;
    
    // Inverse l'état de la LED 1
    led_pin_state = !led_pin_state;
    digitalWrite(led_pin, led_pin_state);
  }
}
