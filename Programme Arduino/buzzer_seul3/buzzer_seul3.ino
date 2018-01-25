void setup() {
// declare pin 9 to be an output:
pinMode(53, OUTPUT);
}

void loop()
{
beep(1);
delay(1000);
}

void beep(unsigned char delayMS)
{
//write a value between 1 and 254 out
//delay, switch off and delay again
analogWrite(53, 255);
delay(delayMS);
analogWrite(53, 0);
delay(delayMS);
}
