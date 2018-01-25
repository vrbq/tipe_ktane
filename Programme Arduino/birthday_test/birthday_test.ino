
#include "pitches.h"

#define melodyPin 53
//Birthday Theme
int birthdaymelody[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_D4,
  NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
  
};
//Birthday Theme
int birthdaytempo[] = {
  5, 10, 5, 5, 5, 2,
  5, 10, 5, 5, 5, 2,
  5, 10, 5, 5, 5, 5, 10, 2,
  5, 10, 5, 5, 5, 1,
};

int etatBoutonStart = 0;

//Pin indicator
int buzzer = 53;
int led = 47;
int button = 21;

void setup(void)
{
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
}

void loop()
{
  etatBoutonStart = digitalRead(button);
  
  if (etatBoutonStart == LOW) {
  sing(1);
  }
}

int song = 0;

void sing(int s) {
  // iterate over the notes of the melody:
  song = s;
  if (song == 1) {
    Serial.begin(9600);
    Serial.println(" 'Birthday Theme'");
    int size = sizeof(birthdaymelody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / birthdaytempo[thisNote];
 
      buzz(melodyPin, birthdaymelody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
 
    }
 
  } 
}
 
void buzz(int targetPin, long frequency, long length) {
  digitalWrite(47, LOW);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(47, HIGH);
 
}
