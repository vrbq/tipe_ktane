
////////// LEDS /////////
const int led1 = 19;
const int led2 = 14;

//////// VARIABLES DE TEMPS //////////
unsigned long currentMillis = 0;


int start_led1 = 0;
int blinkled1 = 1000;
int etatled1 = LOW;


int start_led2 = 0;
int blinkled2 = 2000;
int etatled2 = LOW;


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);


}

void loop() {


  currentMillis = millis();
  
  fct_blinkled1();
  fct_blinkled2();

}


void fct_blinkled1() {
  if (etatled1 == LOW)
  {
    if (currentMillis - start_led1 >= blinkled1)
    {
      etatled1 = HIGH;
      start_led1 = currentMillis;
      digitalWrite(led1, etatled1);
    }
  }
   
  else
    {
      if (currentMillis - start_led1 >= blinkled1)
      {
        etatled1 = LOW;
        start_led1 = currentMillis;
        digitalWrite(led1, etatled1);
      }
    }

}


void fct_blinkled2() {
  if (etatled2 == LOW)
  {
    if (currentMillis - start_led2 >= blinkled2)
    {
      etatled2 = HIGH;
      start_led2 = currentMillis;
      digitalWrite(led2, etatled2);
    }
  }
   
  else
    {
      if (currentMillis - start_led2 >= blinkled2)
      {
        etatled2 = LOW;
        start_led2 = currentMillis;
        digitalWrite(led2, etatled2);
      }
    }

}

