
const int BUTTON_PIN = A3;

void setup() {
  // put your setup code here, to run once:
pinMode(BUTTON_PIN,INPUT);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
int val = analogRead(BUTTON_PIN);
Serial.println(val);
}
