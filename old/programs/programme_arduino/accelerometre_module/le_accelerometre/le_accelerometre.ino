#if defined(ARDUINO)
/* Mandatory includes for Arduino */
#include <SPI.h>
#include <Wire.h>
#endif
int = lcd;
int bouton = 7; //changer le pin
int buttonstate  = 0;
boolean acc_module;
int etape = 0;
int ep1 = 0;
#include <MMA_7455.h>


MMA_7455 accel = MMA_7455(i2c_protocol);


int16_t x, y, z;

void setup()
{
  acc_module = true;
  randomSeed(anlogRead(1));
  lcd = random (1,4);
  /* Set serial baud rate */
  Serial.begin(9600);
  /* Start accelerometer */
  accel.begin();
  /* Set accelerometer sensibility */
  accel.setSensitivity(2);
  /* Verify sensibility - optional */
  if(accel.getSensitivity() != 2)   Serial.println("Sensitivity failure");
  /* Set accelerometer mode */
  accel.setMode(measure);
  /* Verify accelerometer mode - optional */
  if(accel.getMode() != measure)    Serial.println("Set mode failure");
  /* Set axis offsets */
  /* Note: the offset is hardware specific
   * and defined thanks to the auto-calibration example. */
  accel.setAxisOffset(-8, 20, -33);

  pinMode(bouton, OUTPUT);
}

void loop(){
  buttonstate = digitalRead(bouton){
  if ( buttonstate == HIGH);
    x = accel.readAxis10('x'); // on obtient les valeurs sur 10 bits
    y = accel.readAxis10('y');
    z = accel.readAxis10('z');
  }
  if (lcd == 1){ //gauche
    if not ( x > 58 && x < 78 && y < 4 && y > -16 && z < 9 && z > -11){
      acc_module == false;
    }
  if (lcd == 2){ //avant
    if not(x > -7 && x < 13 && y < -55 && y > -75 && z < 20 && z > 0){
      acc_module == false;
    }
  }
  if (lcd == 3){ //droite
    if not(x > -75 && x < -45 && y < 11 && y > -9 && z < 10 && z > -10){
      acc_module == false;
    }
  }
  if (lcd ==4){ //arriere
    if not(x > -3 && x < 17 && y < 70 && y > 50 && z < 3 && z > -17){
      acc_module == false;
    }
  }   
}
else if (etape == 2){
    if (lcd == 1){
      
      }
    if (lcd == 2){
      
    }
    if (lcd == 3){
      
    }
    if (lcd ==4){
      
    }   
  }
 
  /* Display current axis values */
  Serial.print("X: ");    Serial.print(x, DEC);
  Serial.print("\tY: ");  Serial.print(y, DEC);
  Serial.print("\tZ: ");  Serial.print(z, DEC);

  /*pour la droite :*/
 if( x > -75 && x < -45 && y < 11 && y > -9 && z < 10 && z > -10) {
  Serial.print("\tdroite");
 }
   /*pour la gauche :*/
 else if( x > 58 && x < 78 && y < 4 && y > -16 && z < 9 && z > -11 ) {
  Serial.print("\tgauche");
 }  /*pour le devant :*/
 else if( x > -7 && x < 13 && y < -55 && y > -75 && z < 20 && z > 0) {
  Serial.print("\tdevant");
 }  /*pour le derriere :*/
 else if( x > -3 && x < 17 && y < 70 && y > 50 && z < 3 && z > -17) {
  Serial.print("\tderriere");
 }
 else {
  Serial.print("\tfalse");
 }
  Serial.println();
  delay(500);
}


