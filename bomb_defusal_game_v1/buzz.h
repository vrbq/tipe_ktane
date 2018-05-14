void buzz(int targetPin, long frequency, long length) {
  
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce

  
  unsigned long startMicros_buzz = 0; 

  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...

  unsigned long currentMicros_buzz = micros();
  
    digitalWrite(targetPin, HIGH);
    if (currentMicros_buzz - startMicros_buzz >= delayValue ) {
      digitalWrite(targetPin, LOW);
      startMicros_buzz = currentMicros_buzz;
    }
    
  }

}

 void beepend(){

   buzz(buzzer_timer_pin, 540, 10000);
    digitalWrite(buzzer_timer_pin, LOW);
    delay(100);
    buzz(buzzer_timer_pin, 540, 10000);
    digitalWrite(buzzer_timer_pin, LOW);
    delay(100);
    buzz(buzzer_timer_pin, 540, 10000);
    digitalWrite(buzzer_timer_pin, LOW);
    delay(100);
    buzz(buzzer_timer_pin, 540, 10000);
    digitalWrite(buzzer_timer_pin, LOW);
    delay(100);
    buzz(buzzer_timer_pin, 540, 10000);
    digitalWrite(buzzer_timer_pin, LOW);
    delay(100);
    buzz(buzzer_timer_pin, 540, 10000);
    digitalWrite(buzzer_timer_pin, LOW);
    delay(100);
    buzz(buzzer_timer_pin, 540, 10000);
    digitalWrite(buzzer_timer_pin, LOW);
    delay(100);
    buzz(buzzer_timer_pin, 540, 10000);
    digitalWrite(buzzer_timer_pin, LOW);
    delay(100);
  
 }

